#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <rte_debug.h>
#include <cmdline_parse.h>
#include <cmdline_parse_string.h>
#include <cmdline_parse_num.h>
#include <cmdline.h>

#include <rte_pmd_pc802.h>

#include <pc802_oam_lib.h>
#include <semaphore.h>
#include <cmdline_parse_etheraddr.h>
#include <rte_ether.h>


extern int main_stop;
extern int pc802_test_pcie( int len, int time, int ch, int type );

struct cmd_quit_result {
    cmdline_fixed_string_t quit;
};

static void cmd_quit_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    main_stop = 1;
    cmdline_quit(cl);
}

cmdline_parse_token_string_t cmd_quit_quit =
    TOKEN_STRING_INITIALIZER(struct cmd_quit_result, quit, "quit");

cmdline_parse_inst_t cmd_quit = {
    .f = cmd_quit_parsed,
    .data = NULL,
    .help_str = "quit: Exit application",
    .tokens = {
        (void *)&cmd_quit_quit,
        NULL,
    },
};

extern int test_case_No;

struct cmd_run_test_case_result {
    cmdline_fixed_string_t test;
    cmdline_fixed_string_t caze;
    int                    caseNo;
};

cmdline_parse_token_string_t cmd_run_test_case_result_test =
    TOKEN_STRING_INITIALIZER(struct cmd_run_test_case_result, test, "test");
cmdline_parse_token_string_t cmd_run_test_case_result_case =
    TOKEN_STRING_INITIALIZER(struct cmd_run_test_case_result, caze, "case");
cmdline_parse_token_num_t cmd_run_test_case_result_caseNo =
    TOKEN_NUM_INITIALIZER(struct cmd_run_test_case_result, caseNo, RTE_INT32);

static void cmd_run_test_case_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_run_test_case_result *res = parsed_result;
    test_case_No = res->caseNo;
}

cmdline_parse_inst_t run_test_case = {
    .f = cmd_run_test_case_parsed,
    .data = NULL,
    .help_str = "test case <case_number>",
    .tokens = {
        (void *)&cmd_run_test_case_result_test,
        (void *)&cmd_run_test_case_result_case,
        (void *)&cmd_run_test_case_result_caseNo,
        NULL,
        },
};

static void read_pc802_memory(uint32_t startAddr, uint32_t bytesNum)
{
    pc802_access_ep_mem(0, startAddr, bytesNum, DIR_PCIE_DMA_UPLINK);
    uint8_t *p = (uint8_t *)pc802_get_debug_mem(0);
    uint32_t k, r;
    for (k = 0; k < bytesNum; k++) {
        r = k & 0xF;
        if (0 == r) {
            printf("PC802-%08X : ", startAddr);
            startAddr += 16;
        }
        printf("%02X ", *p++);
        if (15 == r)
            printf("\n");
    }
}

#if 1
static void read_npu_memory(uint64_t startAddr, uint32_t bytesNum)
{
    uint8_t *p = (uint8_t *)startAddr;
    uint32_t k, r;
    for (k = 0; k < bytesNum; k++) {
        r = k & 0xF;
        if (0 == r) {
            printf("NPU-%016lX : ", startAddr);
            startAddr += 16;
        }
        printf("%02X ", *p++);
        if (15 == r)
            printf("\n");
    }
}
#endif

struct cmd_read_memory_result {
    cmdline_fixed_string_t read;
    cmdline_fixed_string_t who;
    uint64_t               startAddr;
    uint32_t               bytesNum;
};

cmdline_parse_token_string_t cmd_read_memory_result_read =
    TOKEN_STRING_INITIALIZER(struct cmd_read_memory_result, read, "read");
cmdline_parse_token_string_t cmd_read_memory_result_who =
    TOKEN_STRING_INITIALIZER(struct cmd_read_memory_result, who, "pc802#npu");
cmdline_parse_token_num_t cmd_read_memory_result_startPhyAddr =
    TOKEN_NUM_INITIALIZER(struct cmd_read_memory_result, startAddr, RTE_UINT64);
cmdline_parse_token_num_t cmd_read_memory_result_bytesNum =
    TOKEN_NUM_INITIALIZER(struct cmd_read_memory_result, bytesNum, RTE_UINT32);

static void cmd_read_memory_result_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_read_memory_result *res = parsed_result;
    uint64_t startAddr;
    uint32_t bytesNum;
    uint32_t offset;
    offset = (uint32_t)(res->startAddr & 0xF);
    startAddr = res->startAddr - offset;
    bytesNum = res->bytesNum + offset;
    bytesNum = (bytesNum + 15) & 0xFFFFFFF0;
#if 1
    if (!strcmp(res->who, "npu")) {
        read_npu_memory(startAddr, bytesNum);
    } else
#endif
    if (!strcmp(res->who, "pc802")) {
        uint32_t pc802Addr = (uint32_t)startAddr;
        read_pc802_memory(pc802Addr, bytesNum);
    } else
        return;

    return;
}

cmdline_parse_inst_t read_memory = {
    .f = cmd_read_memory_result_parsed,
    .data = NULL,
    .help_str = "read PC802 startPhyAddr bytesNum",
    .tokens = {
        (void *)&cmd_read_memory_result_read,
        (void *)&cmd_read_memory_result_who,
        (void *)&cmd_read_memory_result_startPhyAddr,
        (void *)&cmd_read_memory_result_bytesNum,
        NULL,
        },
};

struct cmd_show_pcie_counter_result {
    cmdline_fixed_string_t show;
    cmdline_fixed_string_t pcie;
    cmdline_fixed_string_t counter;
};

cmdline_parse_token_string_t cmd_show_pcie_counter_result_show =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pcie_counter_result, show, "show");
cmdline_parse_token_string_t cmd_show_pcie_counter_result_pcie =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pcie_counter_result, pcie, "pcie");
cmdline_parse_token_string_t cmd_show_pcie_counter_result_counter =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pcie_counter_result, counter, "counter");

static void cmd_show_pcie_counter_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_show_pcie_counter_result *res = parsed_result;
    RTE_ASSERT(!strcmp(res->show, "show"));
    RTE_ASSERT(!strcmp(res->pcie, "pcie"));
    RTE_ASSERT(!strcmp(res->counter, "counter"));
    pc802_show_pcie_counter(0);
}

cmdline_parse_inst_t show_pcie_counter = {
    .f = cmd_show_pcie_counter_parsed,
    .data = NULL,
    .help_str = "show PCIE counters of EP and RC",
    .tokens = {
        (void *)&cmd_show_pcie_counter_result_show,
        (void *)&cmd_show_pcie_counter_result_pcie,
        (void *)&cmd_show_pcie_counter_result_counter,
        NULL,
        },
};

struct cmd_show_pc802_info_result {
    cmdline_fixed_string_t show;
    cmdline_fixed_string_t dir;
    cmdline_fixed_string_t type;
    cmdline_fixed_string_t info;
    uint16_t               idx;
};

cmdline_parse_token_string_t cmd_show_pc802_info_result_show =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_info_result, show, "show");
cmdline_parse_token_string_t cmd_show_pc802_info_result_dir =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_info_result, dir, "dl#ul");
cmdline_parse_token_string_t cmd_show_pc802_info_result_type =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_info_result, type, "data#ctrl");
cmdline_parse_token_string_t cmd_show_pc802_info_result_info =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_info_result, info, "info");
cmdline_parse_token_num_t cmd_show_pc802_info_result_idx =
    TOKEN_NUM_INITIALIZER(struct cmd_show_pc802_info_result, idx, RTE_UINT16);

static void cmd_show_pc802_info_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_show_pc802_info_result *res = parsed_result;
    uint16_t dir;
    if (!strcmp(res->dir, "dl")) {
        dir = 0;
    } else if (!strcmp(res->dir, "ul")) {
        dir = 1;
    } else {
        printf("dir should be dl or ul\n");
        return;
    }

    int queue_id;
    if (!strcmp(res->type, "data")) {
        queue_id = 1;
    } else if (!strcmp(res->type, "ctrl")) {
        queue_id = 2;
    } else {
        printf("type should be ctrl or data\n");
        return;
    }

    if (dir) { // UL
        pc802_show_rx_info(0, queue_id, res->idx);
    } else { // DL
        pc802_show_tx_info(0, queue_id, res->idx);
    }
}

cmdline_parse_inst_t show_pc802_info = {
    .f = cmd_show_pc802_info_parsed,
    .data = NULL,
    .help_str = "show PC802 Tx/Rx Desc, MBlk header, first 64 bytes of data",
    .tokens = {
        (void *)&cmd_show_pc802_info_result_show,
        (void *)&cmd_show_pc802_info_result_dir,
        (void *)&cmd_show_pc802_info_result_type,
        (void *)&cmd_show_pc802_info_result_info,
        (void *)&cmd_show_pc802_info_result_idx,
        NULL,
        },
};

struct cmd_show_pc802_data_result {
    cmdline_fixed_string_t show;
    cmdline_fixed_string_t dir;
    cmdline_fixed_string_t type;
    cmdline_fixed_string_t data;
    uint16_t               idx;
};

cmdline_parse_token_string_t cmd_show_pc802_data_result_show =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_data_result, show, "show");
cmdline_parse_token_string_t cmd_show_pc802_data_result_dir =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_data_result, dir, "dl#ul");
cmdline_parse_token_string_t cmd_show_pc802_data_result_type =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_data_result, type, "data#ctrl");
cmdline_parse_token_string_t cmd_show_pc802_data_result_data =
    TOKEN_STRING_INITIALIZER(struct cmd_show_pc802_data_result, data, "data");
cmdline_parse_token_num_t cmd_show_pc802_data_result_idx =
    TOKEN_NUM_INITIALIZER(struct cmd_show_pc802_data_result, idx, RTE_UINT16);

static void cmd_show_pc802_data_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_show_pc802_data_result *res = parsed_result;
    uint16_t dir;
    if (!strcmp(res->dir, "dl")) {
        dir = 0;
    } else if (!strcmp(res->dir, "ul")) {
        dir = 1;
    } else {
        printf("dir should be dl or ul\n");
        return;
    }

    int queue_id;
    if (!strcmp(res->type, "data")) {
        queue_id = 1;
    } else if (!strcmp(res->type, "ctrl")) {
        queue_id = 2;
    } else {
        printf("type should be ctrl or data\n");
        return;
    }

    if (dir) { // UL
        pc802_show_rx_data(0, queue_id, res->idx);
    } else { // DL
        pc802_show_tx_data(0, queue_id, res->idx);
    }
}

cmdline_parse_inst_t show_pc802_data = {
    .f = cmd_show_pc802_data_parsed,
    .data = NULL,
    .help_str = "show PC802 Tx/Rx Desc, MBlk header, all message data",
    .tokens = {
        (void *)&cmd_show_pc802_data_result_show,
        (void *)&cmd_show_pc802_data_result_dir,
        (void *)&cmd_show_pc802_data_result_type,
        (void *)&cmd_show_pc802_data_result_data,
        (void *)&cmd_show_pc802_data_result_idx,
        NULL,
        },
};

struct cmd_download_test_vector_result {
    cmdline_fixed_string_t download;
    uint32_t               pc802_mem;
    uint32_t               byte_num;
};

cmdline_parse_token_string_t cmd_download_test_vector_result_download =
    TOKEN_STRING_INITIALIZER(struct cmd_download_test_vector_result, download, "download");
cmdline_parse_token_num_t cmd_download_test_vector_result_pc802_mem =
    TOKEN_NUM_INITIALIZER(struct cmd_download_test_vector_result, pc802_mem, RTE_UINT32);
cmdline_parse_token_num_t cmd_download_test_vector_result_byte_num =
    TOKEN_NUM_INITIALIZER(struct cmd_download_test_vector_result, byte_num, RTE_UINT32);

static void cmd_download_test_vector_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_download_test_vector_result *res = parsed_result;
    FILE *fp = fopen("DL_test_vector.dat", "wb");
    RTE_ASSERT(NULL != fp);
    uint64_t *p0 = pc802_get_debug_mem(0);
    uint32_t k;

    uint32_t *p = (uint32_t *)p0;
    for (k = 0; k < res->byte_num; k += sizeof(uint32_t))
        *p++ = rand();

    uint64_t s, ns;
    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_start);

    pc802_access_ep_mem(0, res->pc802_mem, res->byte_num, DIR_PCIE_DMA_DOWNLINK);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
    ns = ((t_end.tv_sec - t_start.tv_sec) * 1E9);
    ns += (t_end.tv_nsec - t_start.tv_nsec);
    s = (t_end.tv_sec - t_start.tv_sec);

    printf("Download Test Vector: NPU --->>> PC802\n");
    printf("\tbyte_num = %9u  took  %lu (0x%lX) ns\n", res->byte_num, ns, ns);
    printf("\t\t about %lu second \n", s);

    fwrite(p0, 1, res->byte_num, fp);
    fclose(fp);
}

cmdline_parse_inst_t download_test_vector = {
    .f = cmd_download_test_vector_parsed,
    .data = NULL,
    .help_str = "Test time used to download test vector",
    .tokens = {
        (void *)&cmd_download_test_vector_result_download,
        (void *)&cmd_download_test_vector_result_pc802_mem,
        (void *)&cmd_download_test_vector_result_byte_num,
        NULL,
        },
};

static unsigned long get_file_size(const char *filename)
{
    unsigned long size;
    FILE* fp = fopen( filename, "rb" );
    if(fp==NULL)
    {
        printf("ERROR: Open file %s failed.\n", filename);
        return 0;
    }
    fseek( fp, SEEK_SET, SEEK_END );
    size=ftell(fp);
    fclose(fp);
    return size;
}

static void check_down_up(void)
{
    unsigned long sz1, sz2;
    sz1 = get_file_size("DL_test_vector.dat");
    sz2 = get_file_size("UL_test_vector.dat");
    if (sz1 != sz2) {
        printf("Download and UPload File Size Not Equal !!!\n");
        return;
    }
    uint8_t d1, d2;
    unsigned long k;
    FILE *fp1, *fp2;
    RTE_ASSERT(NULL != (fp1 = fopen("DL_test_vector.dat", "rb")));
    RTE_ASSERT(NULL != (fp2 = fopen("UL_test_vector.dat", "rb")));
    int flag = 1;
    for (k = 0; flag && (k < sz1); k++) {
        RTE_ASSERT(1 == fread(&d1, 1, 1, fp1));
        RTE_ASSERT(1 == fread(&d2, 1, 1, fp2));
        flag = (d1 == d2);
    }
    fclose(fp1);
    fclose(fp2);
    if (flag) {
        printf("Download File == Upload File !\n");
    } else {
        printf("Download File != Upload File at k = %lu!\n", k);
    }
}

struct cmd_upload_test_vector_result {
    cmdline_fixed_string_t upload;
    uint32_t               pc802_mem;
    uint32_t               byte_num;
};

cmdline_parse_token_string_t cmd_upload_test_vector_result_download =
    TOKEN_STRING_INITIALIZER(struct cmd_upload_test_vector_result, upload, "upload");
cmdline_parse_token_num_t cmd_upload_test_vector_result_pc802_mem =
    TOKEN_NUM_INITIALIZER(struct cmd_upload_test_vector_result, pc802_mem, RTE_UINT32);
cmdline_parse_token_num_t cmd_upload_test_vector_result_byte_num =
    TOKEN_NUM_INITIALIZER(struct cmd_upload_test_vector_result, byte_num, RTE_UINT32);

static void cmd_upload_test_vector_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_upload_test_vector_result *res = parsed_result;
    FILE *fp = fopen("UL_test_vector.dat", "wb");
    RTE_ASSERT(NULL != fp);
    uint64_t *p0 = pc802_get_debug_mem(0);
    memset(p0, 0, res->byte_num);

    uint64_t s, ns;
    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_start);

    pc802_access_ep_mem(0, res->pc802_mem, res->byte_num, DIR_PCIE_DMA_UPLINK);

    clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
    ns = ((t_end.tv_sec - t_start.tv_sec) * 1E9);
    ns += (t_end.tv_nsec - t_start.tv_nsec);
    s = (t_end.tv_sec - t_start.tv_sec);

    printf("Upload Test Vector: NPU <<<--- PC802\n");
    printf("\tbyte_num = %9u  took  %lu (0x%lX) ns\n", res->byte_num, ns, ns);
    printf("\t\t about %lu second \n", s);

    fwrite(p0, 1, res->byte_num, fp);
    fclose(fp);

    check_down_up();
}

cmdline_parse_inst_t upload_test_vector = {
    .f = cmd_upload_test_vector_parsed,
    .data = NULL,
    .help_str = "Test time used to download test vector",
    .tokens = {
        (void *)&cmd_upload_test_vector_result_download,
        (void *)&cmd_upload_test_vector_result_pc802_mem,
        (void *)&cmd_upload_test_vector_result_byte_num,
        NULL,
        },
};

struct cmd_test_memdump_result {
    cmdline_fixed_string_t test;
    cmdline_fixed_string_t memdump;
    uint32_t               pc802_mem;
    uint32_t               byte_num;
};

cmdline_parse_token_string_t cmd_test_memdump_result_test =
    TOKEN_STRING_INITIALIZER(struct cmd_test_memdump_result, test, "test");
cmdline_parse_token_string_t cmd_test_memdump_result_memdump =
    TOKEN_STRING_INITIALIZER(struct cmd_test_memdump_result, memdump, "memdump");
cmdline_parse_token_num_t cmd_test_memdump_result_pc802_mem =
    TOKEN_NUM_INITIALIZER(struct cmd_test_memdump_result, pc802_mem, RTE_UINT32);
cmdline_parse_token_num_t cmd_test_memdump_result_byte_num =
    TOKEN_NUM_INITIALIZER(struct cmd_test_memdump_result, byte_num, RTE_UINT32);

void test_pc802_mem_dump(uint32_t          pc802_mem, uint32_t byte_num);

static void cmd_test_memdump_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_test_memdump_result *res = parsed_result;
    test_pc802_mem_dump(res->pc802_mem, res->byte_num);
}

cmdline_parse_inst_t test_memdump = {
    .f = cmd_test_memdump_parsed,
    .data = NULL,
    .help_str = "Test memdump from PC802",
    .tokens = {
        (void *)&cmd_test_memdump_result_test,
        (void *)&cmd_test_memdump_result_memdump,
        (void *)&cmd_test_memdump_result_pc802_mem,
        (void *)&cmd_test_memdump_result_byte_num,
        NULL,
        },
};

struct cmd_set_test_data_mode_result {
    cmdline_fixed_string_t set;
    cmdline_fixed_string_t data;
    int                    mode;
};

cmdline_parse_token_string_t cmd_set_test_data_mode_result_set =
    TOKEN_STRING_INITIALIZER(struct cmd_set_test_data_mode_result, set, "set");
cmdline_parse_token_string_t cmd_set_test_data_mode_result_data =
    TOKEN_STRING_INITIALIZER(struct cmd_set_test_data_mode_result, data, "data");
cmdline_parse_token_num_t cmd_set_test_data_mode_result_mode =
    TOKEN_NUM_INITIALIZER(struct cmd_set_test_data_mode_result, mode, RTE_INT32);

extern int testpc802_data_mode;
static void cmd_set_test_data_mode_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_set_test_data_mode_result *res = parsed_result;
    printf("PC802 Test Data Mode : %d -->> %d\n", testpc802_data_mode, res->mode);
    testpc802_data_mode = res->mode;
}

cmdline_parse_inst_t set_test_data_mode = {
    .f = cmd_set_test_data_mode_parsed,
    .data = NULL,
    .help_str = "set data <mode>",
    .tokens = {
        (void *)&cmd_set_test_data_mode_result_set,
        (void *)&cmd_set_test_data_mode_result_data,
        (void *)&cmd_set_test_data_mode_result_mode,
        NULL,
        },
};

struct cmd_exit_test_loop_result {
    cmdline_fixed_string_t exit;
    cmdline_fixed_string_t loop;
};

cmdline_parse_token_string_t cmd_exit_test_loop_result_exit =
    TOKEN_STRING_INITIALIZER(struct cmd_exit_test_loop_result, exit, "exit");
cmdline_parse_token_string_t cmd_exit_test_loop_result_loop =
    TOKEN_STRING_INITIALIZER(struct cmd_exit_test_loop_result, loop, "loop");

extern int testpc802_exit_loop;
static void cmd_exit_test_loop_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_exit_test_loop_result *res = parsed_result;
    res = res;
    testpc802_exit_loop = 1;
}

cmdline_parse_inst_t exit_test_loop = {
    .f = cmd_exit_test_loop_parsed,
    .data = NULL,
    .help_str = "exit loop",
    .tokens = {
        (void *)&cmd_exit_test_loop_result_exit,
        (void *)&cmd_exit_test_loop_result_loop,
        NULL,
        },
};

struct cmd_set_ul_dma_count_result {
    cmdline_fixed_string_t set;
    cmdline_fixed_string_t ul;
    cmdline_fixed_string_t dma;
    uint32_t               cnt;
};

cmdline_parse_token_string_t cmd_set_ul_dma_count_result_set =
    TOKEN_STRING_INITIALIZER(struct cmd_set_ul_dma_count_result, set, "set");
cmdline_parse_token_string_t cmd_set_ul_dma_count_result_ul =
    TOKEN_STRING_INITIALIZER(struct cmd_set_ul_dma_count_result, ul, "ul");
cmdline_parse_token_string_t cmd_set_ul_dma_count_result_dma =
    TOKEN_STRING_INITIALIZER(struct cmd_set_ul_dma_count_result, dma, "dma");
cmdline_parse_token_num_t cmd_set_ul_dma_count_result_cnt =
    TOKEN_NUM_INITIALIZER(struct cmd_set_ul_dma_count_result, cnt, RTE_UINT32);

static void cmd_set_ul_dma_count_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_set_ul_dma_count_result *res = parsed_result;
    pc802_set_ul_dma_count(0, res->cnt);
}

cmdline_parse_inst_t set_ul_dma_count = {
    .f = cmd_set_ul_dma_count_parsed,
    .data = NULL,
    .help_str = "set ul dma <counter>",
    .tokens = {
        (void *)&cmd_set_ul_dma_count_result_set,
        (void *)&cmd_set_ul_dma_count_result_ul,
        (void *)&cmd_set_ul_dma_count_result_dma,
        (void *)&cmd_set_ul_dma_count_result_cnt,
        NULL,
        },
};

struct cmd_vec_read_result {
    cmdline_fixed_string_t vec;
    cmdline_fixed_string_t read;
    uint32_t               file_id;
    uint32_t               offset;
    uint32_t               pc802_address;
    uint32_t               length;
};

cmdline_parse_token_string_t cmd_vec_read_result_vec =
    TOKEN_STRING_INITIALIZER(struct cmd_vec_read_result, vec, "vec");
cmdline_parse_token_string_t cmd_vec_read_result_read =
    TOKEN_STRING_INITIALIZER(struct cmd_vec_read_result, read, "read");
cmdline_parse_token_num_t cmd_vec_read_result_file_id =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_read_result, file_id, RTE_UINT32);
cmdline_parse_token_num_t cmd_vec_read_result_offset =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_read_result, offset, RTE_UINT32);
cmdline_parse_token_num_t cmd_vec_read_result_pc802_address =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_read_result, pc802_address, RTE_UINT32);
cmdline_parse_token_num_t cmd_vec_read_result_length =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_read_result, length, RTE_UINT32);

static void cmd_vec_read_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_vec_read_result *res = parsed_result;
    pc802_vec_read(res->file_id, res->offset, res->pc802_address, res->length);
}

cmdline_parse_inst_t vec_read = {
    .f = cmd_vec_read_parsed,
    .data = NULL,
    .help_str = "vec read <file_id> <offset> <pc802_address> <length>",
    .tokens = {
        (void *)&cmd_vec_read_result_vec,
        (void *)&cmd_vec_read_result_read,
        (void *)&cmd_vec_read_result_file_id,
        (void *)&cmd_vec_read_result_offset,
        (void *)&cmd_vec_read_result_pc802_address,
        (void *)&cmd_vec_read_result_length,
        NULL,
        },
};

struct cmd_vec_dump_result {
    cmdline_fixed_string_t vec;
    cmdline_fixed_string_t dump;
    uint32_t               file_id;
    uint32_t               pc802_address;
    uint32_t               length;
};

cmdline_parse_token_string_t cmd_vec_dump_result_vec =
    TOKEN_STRING_INITIALIZER(struct cmd_vec_dump_result, vec, "vec");
cmdline_parse_token_string_t cmd_vec_dump_result_dump =
    TOKEN_STRING_INITIALIZER(struct cmd_vec_dump_result, dump, "dump");
cmdline_parse_token_num_t cmd_vec_dump_result_file_id =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_dump_result, file_id, RTE_UINT32);
cmdline_parse_token_num_t cmd_vec_dump_result_pc802_address =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_dump_result, pc802_address, RTE_UINT32);
cmdline_parse_token_num_t cmd_vec_dump_result_length =
    TOKEN_NUM_INITIALIZER(struct cmd_vec_dump_result, length, RTE_UINT32);

static void cmd_vec_dump_parsed(void *parsed_result,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_vec_dump_result *res = parsed_result;
    pc802_vec_dump(res->file_id, res->pc802_address, res->length);
}

cmdline_parse_inst_t vec_dump = {
    .f = cmd_vec_dump_parsed,
    .data = NULL,
    .help_str = "vec dump <file_id> <pc802_address> <length>",
    .tokens = {
        (void *)&cmd_vec_dump_result_vec,
        (void *)&cmd_vec_dump_result_dump,
        (void *)&cmd_vec_dump_result_file_id,
        (void *)&cmd_vec_dump_result_pc802_address,
        (void *)&cmd_vec_dump_result_length,
        NULL,
        },
};

struct cmd_test_pcie {
    cmdline_fixed_string_t test;
    cmdline_fixed_string_t pcie;
    uint32_t               len;
    uint32_t               time;
    uint32_t               channel;
    uint32_t               mode;
};

cmdline_parse_token_string_t cmd_test_pcie_test =
    TOKEN_STRING_INITIALIZER(struct cmd_test_pcie, test, "test");
cmdline_parse_token_string_t cmd_test_pcie_pcie =
    TOKEN_STRING_INITIALIZER(struct cmd_test_pcie, pcie, "pcie");
cmdline_parse_token_num_t cmd_test_pcie_len =
    TOKEN_NUM_INITIALIZER(struct cmd_test_pcie, len, RTE_UINT32);
cmdline_parse_token_num_t cmd_test_pcie_time =
    TOKEN_NUM_INITIALIZER(struct cmd_test_pcie, time, RTE_UINT32);
cmdline_parse_token_num_t cmd_test_pcie_channel =
    TOKEN_NUM_INITIALIZER(struct cmd_test_pcie, channel, RTE_UINT32);
cmdline_parse_token_num_t cmd_test_pcie_mode =
    TOKEN_NUM_INITIALIZER(struct cmd_test_pcie, mode, RTE_UINT32);

static void cmd_test_pcie_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_test_pcie *res = parsed;
    pc802_test_pcie( res->len, res->time, res->channel, res->mode );
}

cmdline_parse_inst_t test_pcie = {
    .f = cmd_test_pcie_parsed,
    .data = NULL,
    .help_str = "test pcie <pkt_len> <time> <channel> <mode>",
    .tokens = {
        (void *)&cmd_test_pcie_test,
        (void *)&cmd_test_pcie_pcie,
        (void *)&cmd_test_pcie_len,
        (void *)&cmd_test_pcie_time,
        (void *)&cmd_test_pcie_channel,
        (void *)&cmd_test_pcie_mode,
        NULL,
        },
};





#define SEND_TEST_MSG 1

#if SEND_TEST_MSG

static int send_test_msg(const OamSubMessage_t *sub_msg)
{
    typedef enum{
        PICO_OAM_MSG=0x00,
        PICO_P19_MSG=0x01,
        PICO_DEBUG_MSG=0x02,
    }OamMessageType_e;

    #define OAM_START_FLAG      0xd1c2b3a4
    #define OAM_END_FLAG        0xa4b3c2d1

    typedef struct{
        uint32_t StartFlag;         //0xd1c2b3a4
        uint32_t MsgType;
        uint32_t SubMsgNum;                 //Message burst
    }OamMessageHeader_t;

    typedef struct{
        OamMessageHeader_t Head;
        OamSubMessage_t SubMsg[0];
        uint32_t EndFlag;           //0xa4b3c2d1
    }OamMessage_t;

    PC802_Mem_Block_t *mbuf;
    OamMessage_t *msg = NULL;
    uint32_t *end = NULL;


    mbuf = pc802_alloc_tx_mem_block(0, PC802_TRAFFIC_OAM);
    msg = (OamMessage_t *)&mbuf[1];

    msg->Head.StartFlag = OAM_START_FLAG;
    msg->Head.MsgType = PICO_OAM_MSG;
    msg->Head.SubMsgNum = 1;

    memcpy(msg->SubMsg, sub_msg, sub_msg->Head.MsgSize);

    end = (uint32_t *)((char *)msg->SubMsg + sub_msg->Head.MsgSize);
    *end = OAM_END_FLAG;

    mbuf->pkt_length = sub_msg->Head.MsgSize + sizeof(OamMessage_t);
    mbuf->pkt_type = 0xa5;
    mbuf->eop = 1;
    pc802_tx_mblk_burst(0, PC802_TRAFFIC_OAM, &mbuf, 1);

    return 0;
}

static void rsp_msg_test(uint16_t MsgId)
{
    OamSubMessage_t rsp_msg = {0};
    rsp_msg.Head.MsgId = MsgId;
    rsp_msg.Head.MsgSize = sizeof(OamErrorInd_t)+sizeof(OamSubMessageHeader_t);
    rsp_msg.u.result.err_code = 0;
    send_test_msg(&rsp_msg);    //for test
}
#endif


#if 1

typedef struct {
    sem_t sem;
    OamSubMessage_t msg;
}oam_decode_data;


/*oam get ecpri comp method cfg*/
static int32_t oam_get_ecpri_comp_method_cfg_rsp(void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num)
{
    printf( "Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_comp_method_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(COMP_METH_GET_RSP, oam_get_ecpri_comp_method_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = COMP_METH_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {
#if SEND_TEST_MSG
	rsp_msg_test(COMP_METH_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "COMP_METH_GET_REQ ok.\n" );
            else
                printf( "COMP_METH_SET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "COMP_METH_SET_RSP recv timeout!\n" );
    }
    else
        printf( "COMP_METH_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(COMP_METH_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_comp_method_cfg {
    cmdline_fixed_string_t comp_method_cfg;
};

static void cmd_get_ecpri_comp_method_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_comp_method_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_comp_method_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_comp_method_cfg, comp_method_cfg, "get comp cfg");

cmdline_parse_inst_t get_comp_method_cfg = {
    .f = cmd_get_ecpri_comp_method_cfg_parsed,
    .data = NULL,
    .help_str = "get ecpri method cfg <isStaticComp> <method> <comIqWidth> <decomIqWidth>",
    .tokens = {
        (void *)&cmd_get_comp_method_cfg,
        NULL,
        },
};


/*oam ecpri comp method cfg*/
static int32_t oam_set_ecpri_comp_method_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf( "Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_comp_method_cfg_handler(uint8_t isStaticComp, uint8_t method, uint8_t comIqWidth, uint8_t decomIqWidth)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(COMP_METH_SET_RSP, oam_set_ecpri_comp_method_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = COMP_METH_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriCompMethodCfg_t);
    sub_msg.u.comp_method_cfg.isStaticComp = isStaticComp;
    sub_msg.u.comp_method_cfg.method = method;
    sub_msg.u.comp_method_cfg.comIqWidth = comIqWidth;
    sub_msg.u.comp_method_cfg.decomIqWidth = decomIqWidth;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
	rsp_msg_test(COMP_METH_SET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "COMP_METH_SET_REQ ok.\n" );
            else
                printf( "COMP_METH_SET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "COMP_METH_SET_RSP recv timeout!\n" );
    }
    else
        printf( "COMP_METH_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(COMP_METH_SET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_comp_method_cfg {
    cmdline_fixed_string_t comp_method_cfg;
    uint8_t isStaticComp;
    uint8_t method;
    uint8_t comIqWidth;
    uint8_t decomIqWidth;
};

static void cmd_set_ecpri_comp_method_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_comp_method_cfg *cfg = (struct cmd_ecpri_comp_method_cfg *)parsed;
    set_ecpri_comp_method_cfg_handler(cfg->isStaticComp, cfg->method, cfg->comIqWidth, cfg->decomIqWidth);
}

cmdline_parse_token_string_t cmd_set_comp_method_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_comp_method_cfg, comp_method_cfg, "set comp cfg");
cmdline_parse_token_num_t cmd_set_comp_method_cfg_isStaticComp =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, isStaticComp, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_comp_method_cfg_method =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, method, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_comp_method_cfg_comIqWidth =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, comIqWidth, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_comp_method_cfg_decomIqWidth =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_comp_method_cfg, decomIqWidth, RTE_UINT8);

cmdline_parse_inst_t set_comp_method_cfg = {
    .f = cmd_set_ecpri_comp_method_cfg_parsed,
    .data = NULL,
    .help_str = "set ecpri method cfg <isStaticComp> <method> <comIqWidth> <decomIqWidth>",
    .tokens = {
        (void *)&cmd_set_comp_method_cfg,
        (void *)&cmd_set_comp_method_cfg_isStaticComp,
        (void *)&cmd_set_comp_method_cfg_method,
        (void *)&cmd_set_comp_method_cfg_comIqWidth,
        (void *)&cmd_set_comp_method_cfg_decomIqWidth,
        NULL,
        },
};


/*oam ecpri basic cfg*/
static int32_t oam_get_ecpri_basic_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf( "Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );
    return 0;
}

static int get_ecpri_basic_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(BASIC_CFG_GET_RSP, oam_get_ecpri_basic_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = BASIC_CFG_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(BASIC_CFG_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "BASIC_CFG_GET_REQ ok.\n" );
            else
                printf( "BASIC_CFG_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "BASIC_CFG_GET_RSP recv timeout!\n" );
    }
    else
        printf( "BASIC_CFG_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(BASIC_CFG_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;

}

struct cmd_ecpri_basic_cfg {
    cmdline_fixed_string_t basic_cfg;
    uint8_t pcie_enable;// 1: enable 0: disable
    uint8_t eth_type;// 0: 25Gbps 1: 10Gpbs
    uint8_t max_antenna_cnt;
    uint8_t max_section_cnt;
    uint8_t max_symbol_cnt_per_slot;
    uint8_t cur_antenna_cnt;
    uint8_t cur_section_cnt;
    uint8_t cur_symbol_cnt_per_slot;
    uint32_t pEcpriNtfyBuf;
    uint32_t pEcpriReqBuf;
    uint32_t om_msg_id;
};

static void cmd_get_ecpri_basic_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_basic_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_basic_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_basic_cfg, basic_cfg, "get basic cfg");

cmdline_parse_inst_t get_ecpri_basic_cfg = {
    .f = cmd_get_ecpri_basic_cfg_parsed,
    .data = NULL,
    .help_str = "get ecpri basic cfg <pcie_enable> <eth_type> <max_antenna_cnt> <max_section_cnt> <max_symbol_cnt_per_slot> <cur_antenna_cnt> <cur_section_cnt> <cur_symbol_cnt_per_slot> <pEcpriNtfyBuf> <pEcpriReqBuf> <om_msg_id>",
    .tokens = {
        (void *)&cmd_get_ecpri_basic_cfg,
        NULL,
        },
};

/*oam set ecpri perf kpis */
static int32_t oam_set_ecpri_perf_kpis_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf( "Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_perf_kpis_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_KPIS_GET_RSP, oam_set_ecpri_perf_kpis_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_DU_KPIS_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(BASIC_CFG_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "ECPRI_DU_KPIS_GET_REQ ok.\n" );
            else
                printf( "ECPRI_DU_KPIS_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "ECPRI_DU_KPIS_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_KPIS_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_KPIS_GET_REQ);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_perf_kpis {
    cmdline_fixed_string_t ecpri_perf_kpis;
};

static void cmd_get_ecpri_perf_kpis_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_perf_kpis_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_perf_kpis =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_perf_kpis, ecpri_perf_kpis, "get ecpri perf kpis");

cmdline_parse_inst_t get_ecpri_perf_kpis = {
    .f = cmd_get_ecpri_perf_kpis_parsed,
    .data = NULL,
    .help_str = NULL,
    .tokens = {
        (void *)&cmd_get_ecpri_perf_kpis,
        NULL,
        },
};

/*oam get ecpri du cfg*/
static int32_t oam_get_ecpri_du_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_du_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_GET_RSP, oam_get_ecpri_du_cfg_rsp, &obj);

    memset(&sub_msg, 0, sizeof(sub_msg));
    sub_msg.Head.MsgId = ECPRI_DU_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(ECPRI_DU_GET_RSP);
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "ECPRI_DU_GET_REQ ok.\n" );
            else
                printf( "ECPRI_DU_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "ECPRI_DU_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_du_cfg {
    cmdline_fixed_string_t ecpri_du_cfg;
};

static void cmd_get_ecpri_du_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_du_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_du_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_du_cfg, ecpri_du_cfg, "get ecpri du cfg");

cmdline_parse_inst_t get_ecpri_du_cfg = {
    .f = cmd_get_ecpri_du_cfg_parsed,
    .data = NULL,
    .help_str = "get ecpri du cfg <ru_cnt> <mac addr> <vlan_id>",
    .tokens = {
        (void *)&cmd_get_ecpri_du_cfg,
        NULL,
        },
};


/*oam set ecpri du cfg*/
static int32_t oam_set_ecpri_du_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_du_cfg_handler(uint8_t ru_cnt, uint16_t vlan_id, uint8_t *addr_bytes)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_SET_RSP, oam_set_ecpri_du_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_DU_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriDuCfg_t);
    sub_msg.u.du_cfg.ru_cnt = ru_cnt;
    sub_msg.u.du_cfg.vlan_id = vlan_id;
    memcpy(sub_msg.u.du_cfg.du_mac, addr_bytes, ETH_MAC_ADDR_LEN);

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(ECPRI_DU_SET_RSP);
#endif
        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "ECPRI_DU_SET_REQ ok.\n" );
            else
                printf( "ECPRI_DU_SET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "ECPRI_DU_SET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_SET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_du_cfg {
    cmdline_fixed_string_t ecpri_du_cfg;
    uint8_t ru_cnt;
    struct rte_ether_addr mac_addr;
    uint16_t vlan_id;
};

static void cmd_set_ecpri_du_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_du_cfg *cfg = (struct cmd_ecpri_du_cfg *)parsed;
    set_ecpri_du_cfg_handler(cfg->ru_cnt, cfg->vlan_id, cfg->mac_addr.addr_bytes);
}

cmdline_parse_token_string_t cmd_set_ecpri_du_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_du_cfg, ecpri_du_cfg, "set ecpri du cfg");
cmdline_parse_token_num_t cmd_set_ecpri_du_cfg_ru_cnt =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_du_cfg, ru_cnt, RTE_UINT8);
cmdline_parse_token_etheraddr_t cmd_set_ecpri_du_cfg_mac_addr =
                TOKEN_ETHERADDR_INITIALIZER(struct cmd_ecpri_du_cfg, mac_addr);
cmdline_parse_token_num_t cmd_set_ecpri_du_cfg_vlan_id =
   TOKEN_NUM_INITIALIZER(struct cmd_ecpri_du_cfg, vlan_id, RTE_UINT16);

cmdline_parse_inst_t set_ecpri_du_cfg = {
    .f = cmd_set_ecpri_du_cfg_parsed,
    .data = NULL,
    .help_str = "set ecpri du cfg <ru_cnt> <mac addr> <vlan_id>",
    .tokens = {
        (void *)&cmd_set_ecpri_du_cfg,
        (void *)&cmd_set_ecpri_du_cfg_ru_cnt,
        (void *)&cmd_set_ecpri_du_cfg_mac_addr,
        (void *)&cmd_set_ecpri_du_cfg_vlan_id,
        NULL,
        },
};

/*oam set ecpri du inernal cfg*/
static int32_t oam_get_ecpri_du_internal_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_du_internal_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_DU_LOCAL_GET_RSP, oam_get_ecpri_du_internal_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_DU_LOCAL_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(ECPRI_DU_LOCAL_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "ECPRI_DU_LOCAL_GET_REQ ok.\n" );
            else
                printf( "ECPRI_DU_LOCAL_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "ECPRI_DU_LOCAL_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_DU_LOCAL_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_DU_LOCAL_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_du_internal_cfg {
    cmdline_fixed_string_t cmd_ecpri_du_internal_cfg;
};

static void cmd_get_ecpri_du_internal_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_du_internal_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_du_internal_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_du_internal_cfg, cmd_ecpri_du_internal_cfg, "get ecpri du internal cfg");

cmdline_parse_inst_t get_ecpri_du_internal_cfg = {
    .f = cmd_get_ecpri_du_internal_cfg_parsed,
    .data = NULL,
    .help_str = "get ecpri du internal cfg <pipeline_mode> <m_role> <outgoing_core_cnt> <ingoing_core_cnt>",
    .tokens = {
        (void *)&cmd_get_ecpri_du_internal_cfg,
        NULL,
        },
};

/* oam get ecpri ru cfg*/
static int32_t oam_get_ecpri_ru_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam ru %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_ru_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_RU_GET_RSP, oam_get_ecpri_ru_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_RU_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(ECPRI_RU_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "ECPRI_RU_GET_REQ ok.\n" );
            else
                printf( "ECPRI_RU_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "ECPRI_RU_GET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_RU_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_RU_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;

}

struct cmd_read_ecpri_ru_cfg {
    cmdline_fixed_string_t ecpri_ru_cfg;
};

static void cmd_get_ecpri_ru_cfg_parsed(__attribute__((unused))void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_ru_cfg_handler();
}


cmdline_parse_token_string_t cmd_get_ecpri_ru_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_ru_cfg, ecpri_ru_cfg, "get ecpri ru cfg");

cmdline_parse_inst_t get_ecpri_ru_cfg = {
    .f = cmd_get_ecpri_ru_cfg_parsed,
    .data = NULL,
    .help_str = "get ecpri ru cfg <ru_id> <s_interval> <Ta4min> <Ta4max> <T1amin_cp_ul> <T1amax_cp_ul> <T1amin_cp_dl> <T1amax_cp_dl> <T1amin_up> <T1amax_up> <ru_mac>",
    .tokens = {
        (void *)&cmd_get_ecpri_ru_cfg,
        NULL,
        },
};



/* oam set ecpri ru cfg*/
static int32_t oam_set_ecpri_ru_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam ru %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_ru_cfg_handler(EcpriRuCfg_t *cfg)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(ECPRI_RU_SET_RSP, oam_set_ecpri_ru_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = ECPRI_RU_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriRuCfg_t);
    sub_msg.u.ru_cfg.ru_id = cfg->ru_id;
    sub_msg.u.ru_cfg.s_interval = cfg->s_interval;
    sub_msg.u.ru_cfg.Ta4min = cfg->Ta4min;
    sub_msg.u.ru_cfg.Ta4max = cfg->Ta4max;
    sub_msg.u.ru_cfg.T1amin_cp_ul = cfg->T1amin_cp_ul;
    sub_msg.u.ru_cfg.T1amax_cp_ul = cfg->T1amax_cp_ul;
    sub_msg.u.ru_cfg.T1amin_cp_dl = cfg->T1amin_cp_dl;
    sub_msg.u.ru_cfg.T1amax_cp_dl = cfg->T1amax_cp_dl;
    sub_msg.u.ru_cfg.T1amin_up = cfg->T1amin_up;
    sub_msg.u.ru_cfg.T1amax_up = cfg->T1amax_up;
    memcpy(sub_msg.u.ru_cfg.ru_mac, cfg->ru_mac, ETH_MAC_ADDR_LEN);

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(ECPRI_RU_SET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "ECPRI_RU_SET_REQ ok.\n" );
            else
                printf( "ECPRI_RU_SET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "ECPRI_RU_SET_RSP recv timeout!\n" );
    }
    else
        printf( "ECPRI_RU_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(ECPRI_RU_SET_RSP);
    sem_destroy(&obj.sem);

    return 0;

}

struct cmd_ecpri_ru_cfg {
    cmdline_fixed_string_t ecpri_ru_cfg;
    uint8_t ru_id;
    uint16_t s_interval;
    uint32_t Ta4min;
    uint32_t Ta4max;
    uint32_t T1amin_cp_ul;
    uint32_t T1amax_cp_ul;
    uint32_t T1amin_cp_dl;
    uint32_t T1amax_cp_dl;
    uint32_t T1amin_up;
    uint32_t T1amax_up;
    struct rte_ether_addr mac_addr;
};

static void cmd_set_ecpri_ru_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_ru_cfg *cfg = (struct cmd_ecpri_ru_cfg *)parsed;
    EcpriRuCfg_t ru_cfg;

    ru_cfg.ru_id = cfg->ru_id;
    ru_cfg.s_interval = cfg->s_interval;
    ru_cfg.Ta4min = cfg->Ta4min;
    ru_cfg.Ta4max = cfg->Ta4max;
    ru_cfg.T1amin_cp_ul = cfg->T1amin_cp_ul;
    ru_cfg.T1amax_cp_ul = cfg->T1amax_cp_ul;
    ru_cfg.T1amin_cp_dl = cfg->T1amin_cp_dl;
    ru_cfg.T1amax_cp_dl = cfg->T1amax_cp_dl;
    ru_cfg.T1amin_up = cfg->T1amin_up;
    ru_cfg.T1amax_up = cfg->T1amax_up;
    memcpy(ru_cfg.ru_mac, cfg->mac_addr.addr_bytes, ETH_MAC_ADDR_LEN);

    set_ecpri_ru_cfg_handler(&ru_cfg);
}


cmdline_parse_token_string_t cmd_set_ecpri_ru_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_ru_cfg, ecpri_ru_cfg, "set ecpri ru cfg");
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_ru_id =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, ru_id, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_s_interval =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, s_interval, RTE_UINT16);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_Ta4min =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, Ta4min, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_Ta4max =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, Ta4max, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amin_cp_ul =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg,T1amin_cp_ul, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cf_T1amax_cp_ul =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amax_cp_ul, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amin_cp_dl =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amin_cp_dl, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amax_cp_dl =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amax_cp_dl, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amin_up =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amin_up, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_ru_cfg_T1amax_up =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ru_cfg, T1amax_up, RTE_UINT32);
cmdline_parse_token_etheraddr_t cmd_set_ecpri_ru_cfg_mac_addr =
                TOKEN_ETHERADDR_INITIALIZER(struct cmd_ecpri_ru_cfg, mac_addr);

cmdline_parse_inst_t set_ecpri_ru_cfg = {
    .f = cmd_set_ecpri_ru_cfg_parsed,
    .data = NULL,
    .help_str = "set ecpri ru cfg <ru_id> <s_interval> <Ta4min> <Ta4max> <T1amin_cp_ul> <T1amax_cp_ul> <T1amin_cp_dl> <T1amax_cp_dl> <T1amin_up> <T1amax_up> <ru_mac>",
    .tokens = {
        (void *)&cmd_set_ecpri_ru_cfg,
        (void *)&cmd_set_ecpri_ru_cfg_ru_id,
        (void *)&cmd_set_ecpri_ru_cfg_s_interval,
        (void *)&cmd_set_ecpri_ru_cfg_Ta4min,
        (void *)&cmd_set_ecpri_ru_cfg_Ta4max,
        (void *)&cmd_set_ecpri_ru_cfg_T1amin_cp_ul,
        (void *)&cmd_set_ecpri_ru_cf_T1amax_cp_ul,
        (void *)&cmd_set_ecpri_ru_cfg_T1amin_cp_dl,
        (void *)&cmd_set_ecpri_ru_cfg_T1amax_cp_dl,
        (void *)&cmd_set_ecpri_ru_cfg_T1amin_up,
        (void *)&cmd_set_ecpri_ru_cfg_T1amax_up,
        (void *)&cmd_set_ecpri_ru_cfg_mac_addr,
        NULL,
        },
};

/* oam get ecpri tx rx cfg*/
static int32_t oam_get_ecpri_tx_rx_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf( "Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_tx_rx_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(TX_RX_GET_RSP, oam_get_ecpri_tx_rx_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = TX_RX_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(TX_RX_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "TX_RX_GET_REQ ok.\n" );
            else
                printf( "TX_RX_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "TX_RX_GET_RSP recv timeout!\n" );
    }
    else
        printf( "TX_RX_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(TX_RX_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_tx_rx_cfg {
    cmdline_fixed_string_t ecpri_tx_rx_cfg;
};

static void cmd_get_ecpri_tx_rx_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_tx_rx_cfg_handler();
}

cmdline_parse_token_string_t cmd_get_ecpri_tx_rx_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_tx_rx_cfg, ecpri_tx_rx_cfg, "get ecpri tx rx cfg");

cmdline_parse_inst_t get_ecpri_tx_rx_cfg = {
    .f = cmd_get_ecpri_tx_rx_cfg_parsed,
    .data = NULL,
    .help_str = "get ecpri tx rx cfg <eth_pkt_size> <maxTxPacketSize> <maxTxLateThreshold>",
    .tokens = {
	(void*) &cmd_get_ecpri_tx_rx_cfg,
        NULL,
        },
};



/* oam set ecpri tx rx cfg*/
static int32_t oam_set_ecpri_tx_rx_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf( "Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_tx_rx_cfg_handler(uint32_t eth_pkt_size, uint16_t maxTxPacketSize, uint32_t maxTxLateThreshold)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);

    printf("set ecpri tx rx cfg: %d %d %d\n", eth_pkt_size, maxTxPacketSize, maxTxLateThreshold);
    pc802_oam_sub_msg_register(TX_RX_SET_RSP, oam_set_ecpri_tx_rx_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = TX_RX_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriTxRxCfg_t);
    sub_msg.u.tx_rx_cfg.eth_pkt_size = eth_pkt_size;
    sub_msg.u.tx_rx_cfg.maxTxPacketSize = maxTxPacketSize;
    sub_msg.u.tx_rx_cfg.maxTxLateThreshold = maxTxLateThreshold;

    if ( 0== pc802_oam_send_msg( 0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(TX_RX_SET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "TX_RX_SET_REQ ok.\n" );
            else
                printf( "TX_RX_SET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "TX_RX_SET_RSP recv timeout!\n" );
    }
    else
        printf( "TX_RX_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(TX_RX_SET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_tx_rx_cfg {
    cmdline_fixed_string_t ecpri_tx_rx_cfg;
    uint32_t eth_pkt_size;
    uint16_t maxTxPacketSize;
    uint32_t maxTxLateThreshold;
};

static void cmd_set_ecpri_tx_rx_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_tx_rx_cfg *cfg = (struct cmd_ecpri_tx_rx_cfg *)parsed;
    set_ecpri_tx_rx_cfg_handler(cfg->eth_pkt_size, cfg->maxTxPacketSize, cfg->maxTxLateThreshold);
}

cmdline_parse_token_string_t cmd_set_ecpri_tx_rx_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_tx_rx_cfg, ecpri_tx_rx_cfg, "set ecpri tx rx cfg");
cmdline_parse_token_num_t cmd_set_ecpri_tx_rx_cfg_eth_pkt_size =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_tx_rx_cfg, eth_pkt_size, RTE_UINT32);
cmdline_parse_token_num_t cmd_set_ecpri_tx_rx_cfg_maxTxPacketSize =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_tx_rx_cfg, maxTxPacketSize, RTE_UINT16);
cmdline_parse_token_num_t cmd_set_ecpri_tx_rx_cfg_maxTxLateThreshold =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_tx_rx_cfg, maxTxLateThreshold, RTE_UINT32);

cmdline_parse_inst_t set_ecpri_tx_rx_cfg = {
    .f = cmd_set_ecpri_tx_rx_cfg_parsed,
    .data = NULL,
    .help_str = "set ecpri tx rx cfg <eth_pkt_size> <maxTxPacketSize> <maxTxLateThreshold>",
    .tokens = {
	(void*) &cmd_set_ecpri_tx_rx_cfg,
        (void *)&cmd_set_ecpri_tx_rx_cfg_eth_pkt_size,
        (void *)&cmd_set_ecpri_tx_rx_cfg_maxTxPacketSize,
        (void *)&cmd_set_ecpri_tx_rx_cfg_maxTxLateThreshold,
        NULL,
        },
};

/* oam set ecpri ptp cfg*/
static int32_t oam_set_ecpri_ptp_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int set_ecpri_ptp_cfg_handler(uint8_t ptp_enable, uint8_t ptp_step_mode,  uint8_t ecpri_step_mode, uint8_t ptp_domain)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    printf("ptp: %d %d %d %d\n", ptp_enable, ptp_step_mode, ecpri_step_mode, ptp_domain);
    pc802_oam_sub_msg_register(PTP_SET_RSP, oam_set_ecpri_ptp_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = PTP_SET_REQ;
    sub_msg.Head.MsgSize = sizeof(EcpriPtpCfg_t);
    sub_msg.u.ptp_cfg.ptp_domain = ptp_domain;

    if ( 0== pc802_oam_send_msg(0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(TX_RX_SET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "PTP_SET_REQ ok.\n" );
            else
                printf( "PTP_SET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "PTP_SET_RSP recv timeout!\n" );
    }
    else
        printf( "PTP_SET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(PTP_SET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_ecpri_ptp_cfg {
    cmdline_fixed_string_t ptp_cfg;
    uint8_t ptp_enable;// 1: enable 0: disable
    uint8_t ptp_step_mode;// 1: 1step 0: 2 step
    uint8_t ecpri_step_mode;// 1: 1step 0: 2 step
    uint8_t ptp_domain;
};

cmdline_parse_token_string_t cmd_set_ecpri_ptp_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_cfg, "set ptp cfg");
cmdline_parse_token_num_t cmd_set_ecpri_ptp_enable =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_enable, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ptp_step_mode =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_step_mode, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ecpri_step_mode =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ecpri_step_mode, RTE_UINT8);
cmdline_parse_token_num_t cmd_set_ptp_domain =
    TOKEN_NUM_INITIALIZER(struct cmd_ecpri_ptp_cfg, ptp_domain, RTE_UINT8);

static void cmd_set_ecpri_ptp_cfg_parsed(void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_ecpri_ptp_cfg *ptp = (struct cmd_ecpri_ptp_cfg *)parsed;
    set_ecpri_ptp_cfg_handler(ptp->ptp_enable, ptp->ptp_step_mode, ptp->ecpri_step_mode, ptp->ptp_domain); 
}

cmdline_parse_inst_t set_ecpri_ptp_cfg = {
    .f = cmd_set_ecpri_ptp_cfg_parsed,
    .data = NULL,
    .help_str = "set ptp cfg <ptp_enable> <ptp_step_mode> <ecpri_step_mode> <ptp_domain>",
    .tokens = {
        (void *)&cmd_set_ecpri_ptp_cfg,
        (void *)&cmd_set_ecpri_ptp_enable,
        (void *)&cmd_set_ptp_step_mode,
        (void *)&cmd_set_ecpri_step_mode,
        (void *)&cmd_set_ptp_domain,
        NULL,
        },
};



/* oam get ecpri ptp cfg*/
static int32_t oam_get_ecpri_ptp_cfg_rsp( void *arg, uint16_t port_id, const OamSubMessage_t **sub_msg, uint32_t msg_num )
{
    printf("Oam %d call back %d sub mesg %d\n", port_id, msg_num, sub_msg[0]->Head.MsgSize);
    sem_post( &((oam_decode_data *)arg)->sem );

    return 0;
}

static int get_ecpri_ptp_cfg_handler(void)
{
    oam_decode_data obj;
    OamSubMessage_t sub_msg;
    const OamSubMessage_t *list = &sub_msg;
    struct timespec ts;

    sem_init(&obj.sem, 0, 0);
    pc802_oam_sub_msg_register(PTP_GET_RSP, oam_get_ecpri_ptp_cfg_rsp, &obj);

    memset( &sub_msg, 0, sizeof(sub_msg) );
    sub_msg.Head.MsgId = PTP_GET_REQ;
    sub_msg.Head.MsgSize = 0;

    if ( 0== pc802_oam_send_msg(0, &list, 1 ) ) {

#if SEND_TEST_MSG
        rsp_msg_test(PTP_GET_RSP);
#endif

        clock_gettime( CLOCK_REALTIME, &ts );
        ts.tv_sec += 1;
        if ( 0 == sem_timedwait(&obj.sem, &ts) ){
            if ( 0 == sub_msg.u.result.err_code )
                printf( "PTP_GET_REQ ok.\n" );
            else
                printf( "PTP_GET_RSP err(%d)!\n", sub_msg.u.result.err_code );
        }
        else
            printf( "PTP_SET_RSP recv timeout!\n" );
    }
    else
        printf("PTP_GET_REQ send err!\n" );

    pc802_oam_sub_msg_unregister(PTP_GET_RSP);
    sem_destroy(&obj.sem);

    return 0;
}

struct cmd_read_ecpri_ptp_cfg {
    cmdline_fixed_string_t ptp_cfg;
};

cmdline_parse_token_string_t cmd_get_ecpri_ptp_cfg =
    TOKEN_STRING_INITIALIZER(struct cmd_read_ecpri_ptp_cfg, ptp_cfg, "get ptp cfg");

static void cmd_get_ecpri_ptp_cfg_parsed(__attribute__((unused)) void *parsed,
                __attribute__((unused)) struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    get_ecpri_ptp_cfg_handler(); 
}

cmdline_parse_inst_t get_ecpri_ptp_cfg = {
    .f = cmd_get_ecpri_ptp_cfg_parsed,
    .data = NULL,
    .help_str = "get ptp cfg <ptp_enable> <ptp_step_mode> <ecpri_step_mode> <ptp_domain>",
    .tokens = {
        (void *)&cmd_get_ecpri_ptp_cfg,
        NULL,
        },
};

#endif

cmdline_parse_ctx_t main_ctx[] = {
    (cmdline_parse_inst_t *)&cmd_quit,
    (cmdline_parse_inst_t *)&run_test_case,
    (cmdline_parse_inst_t *)&read_memory,
    (cmdline_parse_inst_t *)&show_pcie_counter,
    (cmdline_parse_inst_t *)&show_pc802_info,
    (cmdline_parse_inst_t *)&show_pc802_data,
    (cmdline_parse_inst_t *)&download_test_vector,
    (cmdline_parse_inst_t *)&upload_test_vector,
    (cmdline_parse_inst_t *)&test_memdump,
    (cmdline_parse_inst_t *)&set_test_data_mode,
    (cmdline_parse_inst_t *)&exit_test_loop,
    (cmdline_parse_inst_t *)&set_ul_dma_count,
    (cmdline_parse_inst_t *)&vec_read,
    (cmdline_parse_inst_t *)&vec_dump,
    (cmdline_parse_inst_t *)&test_pcie,
    (cmdline_parse_inst_t *)&set_ecpri_ptp_cfg,
    (cmdline_parse_inst_t *)&set_comp_method_cfg,
    (cmdline_parse_inst_t *)&set_ecpri_tx_rx_cfg,
    (cmdline_parse_inst_t *)&set_ecpri_ru_cfg,
    (cmdline_parse_inst_t *)&set_ecpri_du_cfg,
    (cmdline_parse_inst_t *)&get_ecpri_perf_kpis,
    (cmdline_parse_inst_t *)&get_ecpri_du_internal_cfg, 
    (cmdline_parse_inst_t *)&get_ecpri_basic_cfg,      
    (cmdline_parse_inst_t *)&get_ecpri_ptp_cfg,      
    (cmdline_parse_inst_t *)&get_comp_method_cfg,
    (cmdline_parse_inst_t *)&get_ecpri_tx_rx_cfg,
    (cmdline_parse_inst_t *)&get_ecpri_ru_cfg,
    (cmdline_parse_inst_t *)&get_ecpri_du_cfg,
    NULL,
};


