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

extern int main_stop;
extern void pc802_kni_print_stats(void);

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
    pc802_kni_print_stats();
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
    pc802_vec_read(0, res->file_id, res->offset, res->pc802_address, res->length);
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
    pc802_vec_dump(0, res->file_id, res->pc802_address, res->length);
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
    NULL,
};

