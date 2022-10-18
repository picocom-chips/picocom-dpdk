#include <stdint.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>

#include <rte_malloc.h>

#include "pico_mb.h"

#define ELF_MAGIC_SIZE 4
#define ELF_MAGIC      "\x7f""ELF"

static const char * (*get_mb_string)(uint32_t addr, uint32_t core);
static const char * mb_get_string_N(uint32_t addr, uint32_t core);
static const char * mb_get_string_d(uint32_t addr, uint32_t core);

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

static char *pc802_img;
static char *dsp_img[3];

static uint32_t phdr_num;
static SSBL_Phdr_t *phdr;
static SSBL_Phdr_t *phdr_pfi[2];
static SSBL_Phdr_t *phdr_ecpri[2];
static char *n_local_mem;
static SSBL_Phdr_t **phdr_global;
static uint32_t n_global;

static uint32_t e_phnum;
static Elf32_Phdr *e_phdr;
static Elf32_Phdr **e_phdr_pfi;
static Elf32_Phdr **e_phdr_ecpri;
static uint32_t e_num_pfi;
static uint32_t e_num_ecpri;
static Elf32_Phdr **e_phdr_pfi_local;
static uint32_t e_num_pfi_local;
static Elf32_Phdr **e_phdr_ecpri_local;
static uint32_t e_num_ecpri_local;
static Elf32_Phdr **e_phdr_global;
static uint32_t e_num_global;

#define LM_LOAD_TYPE    0x70000000

static int mb_string_common(void)
{
    int fd = open("/lib/firmware/pico/pc802.img", O_RDONLY);
    assert(fd > 0);
    struct stat statbuf;
    fstat(fd, &statbuf);
    pc802_img = rte_zmalloc("PC802_STR_IMG", statbuf.st_size, RTE_CACHE_LINE_MIN_SIZE);
    assert(NULL != pc802_img);
    printf("PC802_STR_IMG: fd = %d Size = %lu\n", fd, statbuf.st_size);
    assert(statbuf.st_size == read(fd, pc802_img, statbuf.st_size));
    close(fd);
    if (memcmp(ELF_MAGIC, pc802_img, ELF_MAGIC_SIZE)) {
        printf("pc802.img is format of NR_DU_Release !\n");
        return 0;
    } else {
        printf("pc802.img is format of develop !\n");
        return 1;
    }
}

static int mb_string_init_N(void)
{
    SSBL_Ehdr_t *ehdr = (SSBL_Ehdr_t *)pc802_img;
    phdr_num = ehdr->phdr_num;
    phdr = (SSBL_Phdr_t *)&ehdr[1];
    uint32_t k;
    uint32_t pidx = 0;
    uint32_t eidx = 0;
    uint32_t addr;
    phdr_global = (SSBL_Phdr_t **)calloc(phdr_num, sizeof(SSBL_Phdr_t *));
    assert(phdr_global != NULL);
    n_global = 0;
    for (k = 0; k < phdr_num; k++) {
        addr = phdr[k].dst_addr;
        if (addr == 0x1A000000) {
            dsp_img[0] = pc802_img + phdr[k].offset;
            printf("dsp[0].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else if (addr == 0x1A800000) {
            dsp_img[1] = pc802_img + phdr[k].offset;
            printf("dsp[1].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else if (addr == 0x1B000000) {
            dsp_img[2] = pc802_img + phdr[k].offset;
            printf("dsp[2].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else if ((addr & 0xFF000000) == 0x03000000) { //PFI CIM+CDM
            printf("PFI CLM[%u] = %u @ 0x%08X -> 0x%08X # 0x%08X\n", pidx,
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
            phdr_pfi[pidx++] = &phdr[k];
        } else if ((addr & 0xFF000000) == 0x07000000) { //eCPRI CIM+CDM
            printf("eCPRI CLM[%u] = %u @ 0x%08X -> 0x%08X # 0x%08X\n", eidx,
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
            phdr_ecpri[eidx++] = &phdr[k];
        } else if (addr == 0x13800000) { //local memory
            n_local_mem = pc802_img + phdr[k].offset;
            printf("Andes Local Memory = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
        } else {
            printf("Global Memroy[%u] = %u @ 0x%08X -> 0x%08X # 0x%08X\n", n_global,
                k, phdr[k].offset, phdr[k].dst_addr, phdr[k].file_size);
            phdr_global[n_global++] = &phdr[k];
        }
    }
    return 0;
}

static int mb_string_init_d(void)
{
    Elf32_Ehdr *e_hdr = (Elf32_Ehdr *)pc802_img;
    e_phdr = (Elf32_Phdr *)(pc802_img + e_hdr->e_phoff);
    assert(e_hdr->e_phnum > 3);
    e_phnum = e_hdr->e_phnum;
    e_phdr_pfi   = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != e_phdr_pfi);
    e_num_pfi = 0;
    e_phdr_ecpri = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != e_phdr_ecpri);
    e_num_ecpri = 0;
    e_phdr_pfi_local = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != e_phdr_pfi_local);
    e_num_pfi_local = 0;
    e_phdr_ecpri_local = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != e_phdr_ecpri_local);
    e_num_ecpri_local = 0;
    e_phdr_global = (Elf32_Phdr **)calloc(e_phnum, sizeof(Elf32_Phdr *));
    assert(NULL != e_phdr_global);
    e_num_global = 0;
    uint32_t k;
    uint32_t addr;

    for (k = 0; k < e_phnum; k++) {
        addr = e_phdr[k].p_paddr;
        if (addr == 0x1A000000) {
            dsp_img[0] = pc802_img + e_phdr[k].p_offset;
            printf("dsp[0].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1A200000) {
            printf("Discard dsp[0].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1A800000) {
            dsp_img[1] = pc802_img + e_phdr[k].p_offset;
            printf("dsp[1].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1AA00000) {
            printf("Discard dsp[1].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1B000000) {
            dsp_img[2] = pc802_img + e_phdr[k].p_offset;
            printf("dsp[2].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if (addr == 0x1B200000) {
            printf("Discard dsp[2].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n",
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
        } else if ((addr & 0xFF000000) == 0x02000000) { //PFI CIM+CDM
            printf("PFI CLM [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", e_num_pfi,
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            e_phdr[k].p_paddr |= 0x03000000; // 0x02******-> 0x03******
            e_phdr_pfi[e_num_pfi++] = &e_phdr[k];
        } else if ((addr & 0xFF000000) == 0x03000000) { //PFI CIM+CDM
            printf("PFI CLM [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", e_num_pfi,
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            e_phdr_pfi[e_num_pfi++] = &e_phdr[k];
        } else if ((addr & 0xFF000000) == 0x05000000) { //eCPRI CIM+CDM
            printf("eCPRI CLM [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", e_num_ecpri, k,
                e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            e_phdr[k].p_paddr |= 0x07000000; // 0x05******-> 0x07******
            e_phdr_ecpri[e_num_ecpri++] = &e_phdr[k];
        } else if ((e_phdr[k].p_type & 0xFFFF0000) == LM_LOAD_TYPE) {
            uint32_t first_core = e_phdr[k].p_type & 0xFF;
            uint32_t last_core = (e_phdr[k].p_type >> 8) & 0xFF;
            if ((first_core < 16) && (last_core < 16)) {
                printf("PFI [%u : %u] Local[%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", first_core, last_core, e_num_pfi_local,
                    k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
                e_phdr_pfi_local[e_num_pfi_local++] = &e_phdr[k];
            }
            if ((first_core >= 16) && (last_core >= 16)) {
                printf("eCPRI [%u : %u] Local [%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", first_core, last_core, e_num_ecpri_local,
                    k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
                e_phdr_ecpri_local[e_num_ecpri_local++] = &e_phdr[k];
            }
        } else {
            printf("Golbal[%u].offset = %u @ 0x%08X -> 0x%08X # 0x%08X\n", e_num_global,
                k, e_phdr[k].p_offset, e_phdr[k].p_paddr, e_phdr[k].p_filesz);
            e_phdr_global[e_num_global++] = &e_phdr[k];
        }
    }
    return 0;
}

int pico_mb_init(void)
{
    int re;
    if (0 == mb_string_common()) {
        re = mb_string_init_N();
        get_mb_string = mb_get_string_N;
    } else {
        re = mb_string_init_d();
        get_mb_string = mb_get_string_d;
    }
    return re;
}

static const char * mb_get_string_N(uint32_t addr, uint32_t core)
{
    uint32_t k;
    uint32_t offset;
    uint32_t prefix;
    static const char *unknown = "Unknown String ";

    if (core >= 32) // DSP
        return dsp_img[core - 32] + addr;

    prefix = addr >> 25;
    if (core < 16) { // PFI
        if (prefix == 1) { // 0x02 or 0x03
            addr |= 0x03000000; // 0x02->0x03, 0x03->0x03
            for (k = 1; k < 2 ; k--) {
                if (phdr_pfi[k]->dst_addr <= addr) {
                    offset = addr - phdr_pfi[k]->dst_addr;
                    if (offset < phdr_pfi[k]->file_size) {
                        return pc802_img + phdr_pfi[k]->offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            return n_local_mem + core * 0x2000 + addr;
        }
     } else { //eCPRI
        if (prefix == 1) {
            addr |= 0x07000000; // 0x02 -> 0x07, 0x03->0x07
            for (k = 1; k < 2 ; k--) {
                if (phdr_ecpri[k]->dst_addr <= addr) {
                    offset = addr - phdr_ecpri[k]->dst_addr;
                    if (offset < phdr_ecpri[k]->file_size) {
                        return pc802_img + phdr_ecpri[k]->offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            return n_local_mem + core * 0x2000 + addr;
        }
    }

    for (k = 0; k < n_global; k++) {
        if (phdr_global[k]->dst_addr <= addr) {
            offset = addr - phdr_global[k]->dst_addr;
            if (offset < phdr_global[k]->file_size) {
                return pc802_img + phdr_global[k]->offset + offset;
            }
        }
    }

    return unknown;
}

static const char * mb_get_string_d(uint32_t addr, uint32_t core)
{
    uint32_t k;
    uint32_t offset;
    uint32_t prefix;
    static const char *unknown = "Unknown String ";

    if (core >= 32) // DSP
        return dsp_img[core - 32] + addr;

    prefix = addr >> 25;
    if (core < 16) { // PFI
        if (prefix == 1) { // 0x02 or 0x03
            addr |= 0x03000000; // 0x02->0x03, 0x03->0x03
            for (k = e_num_pfi - 1; k < e_num_pfi ; k--) {
                if (e_phdr_pfi[k]->p_paddr <= addr) {
                    offset = addr - e_phdr_pfi[k]->p_paddr;
                    if (offset < e_phdr_pfi[k]->p_filesz) {
                        return pc802_img + e_phdr_pfi[k]->p_offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            for (k = 0; k < e_num_pfi_local; k++) {
                uint32_t first_core = e_phdr_pfi_local[k]->p_type & 0xFF;
                uint32_t last_core = (e_phdr_pfi_local[k]->p_type  >> 8) & 0xFF;
                if ((first_core <= core) && (core <= last_core)) {
                    offset = addr - e_phdr_pfi_local[k]->p_paddr;
                    if (offset < e_phdr_pfi_local[k]->p_filesz) {
                        return pc802_img + e_phdr_pfi_local[k]->p_offset + offset;
                    }
                }
            }
        }
    } else { //eCPRI
        if (prefix == 1) { // 0x02 or 0x03
            addr |= 0x07000000; // 0x02 -> 0x07, 0x03->0x07
            for (k = e_num_ecpri - 1; k < e_num_ecpri ; k--) {
                if (e_phdr_ecpri[k]->p_paddr <= addr) {
                    offset = addr - e_phdr_ecpri[k]->p_paddr;
                    if (offset < e_phdr_ecpri[k]->p_filesz) {
                        return pc802_img + e_phdr_ecpri[k]->p_offset + offset;
                    }
                }
            }
        } else if (addr < 0x2000) { // local memory
            for (k = 0; k < e_num_ecpri_local; k++) {
                uint32_t first_core = e_phdr_ecpri_local[k]->p_type & 0xFF;
                uint32_t last_core = (e_phdr_ecpri_local[k]->p_type  >> 8) & 0xFF;
                if ((first_core <= core) && (core <= last_core)) {
                    offset = addr - e_phdr_ecpri_local[k]->p_paddr;
                    if (offset < e_phdr_ecpri_local[k]->p_filesz) {
                        return pc802_img + e_phdr_ecpri_local[k]->p_offset + offset;
                    }
                }
            }
        }
    }

    for (k = 0; k < e_num_global; k++) {
        if (e_phdr_global[k]->p_paddr <= addr) {
            offset = addr - e_phdr_global[k]->p_paddr;
            if (offset < e_phdr_global[k]->p_filesz) {
                return pc802_img + e_phdr_global[k]->p_offset + offset;
            }
        }
    }

    return unknown;
}

const char *pico_mb_get(uint32_t addr, uint32_t core)
{
    return (*get_mb_string)(addr, core);
}
