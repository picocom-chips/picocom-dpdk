#include <stdint.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>

#include <rte_malloc.h>

#include "rte_pmd_pc802.h"
#include "pc802_mailbox.h"

#define ELF_MAGIC_SIZE 4
#define ELF_MAGIC      "\x7f""ELF"

typedef union {
    uint32_t _ed[16];
    struct {
        uint32_t git_commit;
        uint32_t entry;
        uint32_t phdr_num;
    };
} SSBL_Ehdr_t;

typedef union {
    uint32_t _pd[8];
    struct {
        uint32_t offset;
        uint32_t dst_addr;
        uint32_t file_size;
        uint32_t mem_size;
        uint32_t flags;
    };
} SSBL_Phdr_t;

struct ssbl_info{
    uint32_t size;
    char *ssbl_img;
    uint32_t refcnt;
};

struct img_info{
    const char * (*get_mb_string)(const struct img_info *img, uint32_t addr, uint32_t core);

    uint32_t size;
    char *pc802_img;

    char *dsp_img[3];

    union {
        struct {
            SSBL_Phdr_t *phdr_pfi[2];

            SSBL_Phdr_t *phdr_ecpri[2];

            char *n_local_mem;

            uint32_t n_global;
            SSBL_Phdr_t **phdr_global;
        };

        struct {
            uint32_t e_num_pfi;
            Elf32_Phdr **e_phdr_pfi;

            uint32_t e_num_pfi_local;
            Elf32_Phdr **e_phdr_pfi_local;

            uint32_t e_num_ecpri;
            Elf32_Phdr **e_phdr_ecpri;

            uint32_t e_num_ecpri_local;
            Elf32_Phdr **e_phdr_ecpri_local;

            uint32_t e_num_global;
            Elf32_Phdr **e_phdr_global;
        };
    };
};

struct fw_info{
    uint32_t ssbl_end;
    struct ssbl_info *ssbl;
    struct img_info  *img;
};

#define LM_LOAD_TYPE    0x70000000

#define PC802_IMAGE_NAME "pc802.img"
#define PC802_SSBL_NAME  "pc802.ssbl"

const char IMAGE_PATH[][32] ={".", "/lib/firmware/pico"};

struct ssbl_info g_common_ssbl = {0};
struct ssbl_info g_pc802_ssbl[PC802_INDEX_MAX] = {0};

struct img_info  g_common_img  = {0};
struct img_info  g_pc802_img[PC802_INDEX_MAX]  = {0};

static struct fw_info g_fw_info[PC802_INDEX_MAX] = {0};

static const char * mb_get_string_N(const struct img_info *img, uint32_t addr, uint32_t core);
static const char * mb_get_string_d(const struct img_info *img, uint32_t addr, uint32_t core);

static int mb_string_init_N(struct img_info *img)
{
    SSBL_Ehdr_t *ehdr = (SSBL_Ehdr_t *)img->pc802_img;
    SSBL_Phdr_t *phdr = (SSBL_Phdr_t *)&ehdr[1];
    uint32_t k;
    uint32_t pidx = 0;
    uint32_t eidx = 0;
    uint32_t addr;

    img->phdr_global = (SSBL_Phdr_t **)calloc(ehdr->phdr_num, sizeof(SSBL_Phdr_t *));
    assert(img->phdr_global != NULL);
    img->n_global = 0;

    for (k = 0; k < ehdr->phdr_num; k++) {
        addr = phdr[k].dst_addr;
        if (addr == 0x1A000000) {
            img->dsp_img[0] = img->pc802_img + phdr[k].offset;
            DBLOG("dsp[0].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else if (addr == 0x1A800000) {
            img->dsp_img[1] = img->pc802_img + phdr[k].offset;
            DBLOG("dsp[1].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else if (addr == 0x1B000000) {
            img->dsp_img[2] = img->pc802_img + phdr[k].offset;
            DBLOG("dsp[2].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else if ((addr & 0xFF000000) == 0x03000000) { //PFI CIM+CDM
            DBLOG("PFI CLM[%u] = %u @ 0x%08X -> 0x%08X # 0x%08X\n", pidx,
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
            img->phdr_pfi[pidx++] = &phdr[k];
        } else if ((addr & 0xFF000000) == 0x07000000) { //eCPRI CIM+CDM
            DBLOG("eCPRI CLM[%u] = %u @ 0x%08X -> 0x%08X # 0x%08X\n", eidx,
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
            img->phdr_ecpri[eidx++] = &phdr[k];
        } else if (addr == 0x13800000) { //local memory
            img->n_local_mem = img->pc802_img + phdr[k].offset;
            DBLOG("Andes Local Memory = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else {
            DBLOG("Global Memroy[%u] = %u @ 0x%08X -> 0x%08X # 0x%08X\n", img->n_global,
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
            img->phdr_global[img->n_global++] = &phdr[k];
        }
    }
    return 0;
}

static int mb_string_init_d(struct img_info *img)
{
    Elf32_Ehdr *e_hdr = (Elf32_Ehdr *)img->pc802_img;
    Elf32_Phdr *e_phdr = (Elf32_Phdr *)(img->pc802_img + e_hdr->e_phoff);
    assert(e_hdr->e_phnum > 3);
    uint32_t e_phnum = e_hdr->e_phnum;

    img->e_phdr_pfi   = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != img->e_phdr_pfi);
    img->e_num_pfi = 0;

    img->e_phdr_ecpri = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != img->e_phdr_ecpri);
    img->e_num_ecpri = 0;

    img->e_phdr_pfi_local = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != img->e_phdr_pfi_local);
    img->e_num_pfi_local = 0;

    img->e_phdr_ecpri_local = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != img->e_phdr_ecpri_local);
    img->e_num_ecpri_local = 0;

    img->e_phdr_global = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != img->e_phdr_global);
    img->e_num_global = 0;

    uint32_t k;
    uint32_t addr;

    for (k = 0; k < e_phnum; k++) {
        addr = e_phdr[k].p_paddr;
        if (addr == 0x1A000000) {
            img->dsp_img[0] = img->pc802_img + e_phdr[k].p_offset;
            DBLOG("dsp[0].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1A200000) {
            DBLOG("Discard dsp[0].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1A800000) {
            img->dsp_img[1] = img->pc802_img + e_phdr[k].p_offset;
            DBLOG("dsp[1].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1AA00000) {
            DBLOG("Discard dsp[1].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1B000000) {
            img->dsp_img[2] = img->pc802_img + e_phdr[k].p_offset;
            DBLOG("dsp[2].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1B200000) {
            DBLOG("Discard dsp[2].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if ((addr & 0xFF000000) == 0x02000000) { //PFI CIM+CDM
            DBLOG("PFI CLM [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", img->e_num_pfi,
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            e_phdr[k].p_paddr |= 0x03000000; // 0x02******-> 0x03******
            img->e_phdr_pfi[img->e_num_pfi++] = &e_phdr[k];
        } else if ((addr & 0xFF000000) == 0x03000000) { //PFI CIM+CDM
            DBLOG("PFI CLM [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", img->e_num_pfi,
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            img->e_phdr_pfi[img->e_num_pfi++] = &e_phdr[k];
        } else if ((addr & 0xFF000000) == 0x05000000) { //eCPRI CIM+CDM
            DBLOG("eCPRI CLM [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", img->e_num_ecpri, k,
                e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            e_phdr[k].p_paddr |= 0x07000000; // 0x05******-> 0x07******
            img->e_phdr_ecpri[img->e_num_ecpri++] = &e_phdr[k];
        } else if ((e_phdr[k].p_type & 0xFFFF0000) == LM_LOAD_TYPE) {
            uint32_t first_core = e_phdr[k].p_type & 0xFF;
            uint32_t last_core = (e_phdr[k].p_type >> 8) & 0xFF;
            if ((first_core < 16) && (last_core < 16)) {
                DBLOG("PFI [%u : %u] Local[%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", first_core, last_core, img->e_num_pfi_local,
                    k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
                img->e_phdr_pfi_local[img->e_num_pfi_local++] = &e_phdr[k];
            }
            if ((first_core >= 16) && (last_core >= 16)) {
                DBLOG("eCPRI [%u : %u] Local [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", first_core, last_core, img->e_num_ecpri_local,
                    k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
                img->e_phdr_ecpri_local[img->e_num_ecpri_local++] = &e_phdr[k];
            }
        } else {
            DBLOG("Golbal[%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", img->e_num_global,
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            img->e_phdr_global[img->e_num_global++] = &e_phdr[k];
        }
    }
    return 0;
}

static uint32_t load_file(const char *file_name, char **buf)
{
    int fp;
    struct stat statbuf;

    DBLOG_INFO("try load file:%s ...\n", file_name);

    if (-1 == (fp = open(file_name, O_RDONLY)))
        return 0;

    fstat(fp, &statbuf);
    *buf = (char *)rte_zmalloc(file_name, statbuf.st_size, RTE_CACHE_LINE_MIN_SIZE);
    if (NULL == *buf){
        close(fp);
        return 0;
    }
    if(statbuf.st_size != read(fp, *buf, statbuf.st_size)){
        rte_free(*buf);
        *buf = NULL;
        close(fp);
        return 0;
    }
    close(fp);
    DBLOG("Load file:%s size=%lu ok.\n", file_name, statbuf.st_size);
    return statbuf.st_size;
}

static struct ssbl_info* get_ssbl_info(uint16_t index)
{
    uint32_t i;
    char file_name[PATH_MAX];

    for (i = 0; i < RTE_DIM(IMAGE_PATH); i++) {
        sprintf(file_name, "%s/pc802_%d/%s", IMAGE_PATH[i], index, PC802_SSBL_NAME);
        if (0 != (g_pc802_ssbl[index].size = load_file(file_name, &g_pc802_ssbl[index].ssbl_img)) )
            return &g_pc802_ssbl[index];
    }

    if (NULL != g_common_ssbl.ssbl_img)
        return &g_common_ssbl;

    for (i = 0; i < RTE_DIM(IMAGE_PATH); i++) {
        sprintf(file_name, "%s/%s", IMAGE_PATH[i], PC802_SSBL_NAME);
        if (0 != (g_common_ssbl.size = load_file(file_name, &g_common_ssbl.ssbl_img)) )
            return &g_common_ssbl;
    }

    return NULL;
}

static struct img_info * load_img(const char *file_name, struct img_info *img)
{
    if (0 == (img->size = load_file(file_name, &img->pc802_img)) )
        return NULL;

    if (memcmp(ELF_MAGIC, img->pc802_img, ELF_MAGIC_SIZE)) {
        DBLOG("%s is format of NR_DU_Release !\n", file_name);
        mb_string_init_N(img);
        img->get_mb_string = mb_get_string_N;
    } else {
        DBLOG("%s is format of develop !\n", file_name);
        mb_string_init_d(img);
        img->get_mb_string = mb_get_string_d;
    }

    return img;
}

static struct img_info* get_image_info(uint16_t index)
{
    char file_name[PATH_MAX];
    uint32_t i;

    for (i = 0; i < RTE_DIM(IMAGE_PATH); i++) {
        sprintf(file_name, "%s/pc802_%d/%s", IMAGE_PATH[i], index, PC802_IMAGE_NAME);
        if (NULL != load_img(file_name, &g_pc802_img[index]))
            return &g_pc802_img[index];
    }

    if ( NULL != g_common_img.pc802_img )
        return &g_common_img;

    for (i = 0; i < RTE_DIM(IMAGE_PATH); i++) {
        sprintf(file_name, "%s/%s", IMAGE_PATH[i], PC802_IMAGE_NAME);
        if (NULL != load_img(file_name, &g_common_img))
            return &g_common_img;
    }

    return NULL;
}

int mb_string_init(uint16_t pc802_index)
{
    if( NULL == g_fw_info[pc802_index].ssbl ) {
        g_fw_info[pc802_index].ssbl = get_ssbl_info(pc802_index);
        assert(NULL != g_fw_info[pc802_index].ssbl);
    }
    g_fw_info[pc802_index].ssbl_end = 0;

    if( NULL == g_fw_info[pc802_index].img ) {
        g_fw_info[pc802_index].img = get_image_info(pc802_index);
        assert(NULL != g_fw_info[pc802_index].img);
    }
    return 0;
}

static const char * mb_get_string_N(const struct img_info *img, uint32_t addr, uint32_t core)
{
    uint32_t k;
    uint32_t offset;
    uint32_t prefix;
    static const char *unknown = "Unknown String ";

    if (core >= 32) // DSP
        return img->dsp_img[core - 32] + addr;

    prefix = addr >> 25;
    if (core < 16) { // PFI
        if (prefix == 1) { // 0x02 or 0x03
            addr |= 0x03000000; // 0x02->0x03, 0x03->0x03
            for (k = 1; k < 2 ; k--) {
                if (img->phdr_pfi[k]->dst_addr <= addr) {
                    offset = addr - img->phdr_pfi[k]->dst_addr;
                    if (offset < img->phdr_pfi[k]->file_size) {
                        return img->pc802_img + img->phdr_pfi[k]->offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            return img->n_local_mem + core * 0x2000 + addr;
        }
     } else { //eCPRI
        if (prefix == 1) {
            addr |= 0x07000000; // 0x02 -> 0x07, 0x03->0x07
            for (k = 1; k < 2 ; k--) {
                if (img->phdr_ecpri[k]->dst_addr <= addr) {
                    offset = addr - img->phdr_ecpri[k]->dst_addr;
                    if (offset < img->phdr_ecpri[k]->file_size) {
                        return img->pc802_img + img->phdr_ecpri[k]->offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            return img->n_local_mem + core * 0x2000 + addr;
        }
    }

    for (k = 0; k < img->n_global; k++) {
        if (img->phdr_global[k]->dst_addr <= addr) {
            offset = addr - img->phdr_global[k]->dst_addr;
            if (offset < img->phdr_global[k]->file_size) {
                return img->pc802_img + img->phdr_global[k]->offset + offset;
            }
        }
    }

    return unknown;
}

static const char * mb_get_string_d(const struct img_info *img, uint32_t addr, uint32_t core)
{
    uint32_t k;
    uint32_t offset;
    uint32_t prefix;
    static const char *unknown = "Unknown String ";

    if (core >= 32) // DSP
        return img->dsp_img[core - 32] + addr;

    prefix = addr >> 25;
    if (core < 16) { // PFI
        if (prefix == 1) { // 0x02 or 0x03
            addr |= 0x03000000; // 0x02->0x03, 0x03->0x03
            for (k = img->e_num_pfi - 1; k < img->e_num_pfi ; k--) {
                if (img->e_phdr_pfi[k]->p_paddr <= addr) {
                    offset = addr - img->e_phdr_pfi[k]->p_paddr;
                    if (offset < img->e_phdr_pfi[k]->p_filesz) {
                        return img->pc802_img + img->e_phdr_pfi[k]->p_offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            for (k = 0; k < img->e_num_pfi_local; k++) {
                uint32_t first_core = img->e_phdr_pfi_local[k]->p_type & 0xFF;
                uint32_t last_core = (img->e_phdr_pfi_local[k]->p_type  >> 8) & 0xFF;
                if ((first_core <= core) && (core <= last_core)) {
                    offset = addr - img->e_phdr_pfi_local[k]->p_paddr;
                    if (offset < img->e_phdr_pfi_local[k]->p_filesz) {
                        return img->pc802_img + img->e_phdr_pfi_local[k]->p_offset + offset;
                    }
                }
            }
        }
    } else { //eCPRI
        if (prefix == 1) { // 0x02 or 0x03
            addr |= 0x07000000; // 0x02 -> 0x07, 0x03->0x07
            for (k = img->e_num_ecpri - 1; k < img->e_num_ecpri ; k--) {
                if (img->e_phdr_ecpri[k]->p_paddr <= addr) {
                    offset = addr - img->e_phdr_ecpri[k]->p_paddr;
                    if (offset < img->e_phdr_ecpri[k]->p_filesz) {
                        return img->pc802_img + img->e_phdr_ecpri[k]->p_offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            for (k = 0; k < img->e_num_ecpri_local; k++) {
                uint32_t first_core = img->e_phdr_ecpri_local[k]->p_type & 0xFF;
                uint32_t last_core = (img->e_phdr_ecpri_local[k]->p_type  >> 8) & 0xFF;
                if ((first_core <= core) && (core <= last_core)) {
                    offset = addr - img->e_phdr_ecpri_local[k]->p_paddr;
                    if (offset < img->e_phdr_ecpri_local[k]->p_filesz) {
                        return img->pc802_img + img->e_phdr_ecpri_local[k]->p_offset + offset;
                    }
                }
            }
        }
    }

    for (k = 0; k < img->e_num_global; k++) {
        if (img->e_phdr_global[k]->p_paddr <= addr) {
            offset = addr - img->e_phdr_global[k]->p_paddr;
            if (offset < img->e_phdr_global[k]->p_filesz) {
                return img->pc802_img + img->e_phdr_global[k]->p_offset + offset;
            }
        }
    }

    return unknown;
}

int32_t mb_get_ssbl(uint16_t pc802_index, uint8_t **ssbl_buf)
{
    if (g_fw_info[pc802_index].ssbl) {
        *ssbl_buf = (uint8_t *)g_fw_info[pc802_index].ssbl->ssbl_img;
        return g_fw_info[pc802_index].ssbl->size;
    }
    return 0;
}

int32_t mb_get_img(uint16_t pc802_index, uint8_t **img_buf)
{
    if (g_fw_info[pc802_index].img) {
        *img_buf = (uint8_t *)g_fw_info[pc802_index].img->pc802_img;
        return g_fw_info[pc802_index].img->size;
    }
    return 0;
}

void mb_set_ssbl_end(uint16_t pc802_index)
{
    g_fw_info[pc802_index].ssbl_end = 1;
}

const char * mb_get_string(uint16_t pc802_index, uint32_t addr, uint32_t core)
{
    if (0 == g_fw_info[pc802_index].ssbl_end) {
        assert(core == 0);
        return (const char *)(g_fw_info[pc802_index].ssbl->ssbl_img + (addr - 0x03080000));
    }
    return g_fw_info[pc802_index].img->get_mb_string(g_fw_info[pc802_index].img, addr, core);
}
