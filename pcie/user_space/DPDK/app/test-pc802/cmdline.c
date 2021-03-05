#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <rte_debug.h>
#include <cmdline_parse.h>
#include <cmdline_parse_string.h>
#include <cmdline_parse_num.h>
#include <cmdline.h>

#include <pc802_ethdev.h>

extern int main_stop;

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
    TOKEN_NUM_INITIALIZER(struct cmd_run_test_case_result, caseNo, INT32);

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
    pc802_read_mem(0, startAddr, bytesNum);
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
    TOKEN_NUM_INITIALIZER(struct cmd_read_memory_result, startAddr, UINT64);
cmdline_parse_token_num_t cmd_read_memory_result_bytesNum =
    TOKEN_NUM_INITIALIZER(struct cmd_read_memory_result, bytesNum, UINT32);

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
    TOKEN_NUM_INITIALIZER(struct cmd_show_pc802_info_result, idx, UINT16);

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
    TOKEN_NUM_INITIALIZER(struct cmd_show_pc802_data_result, idx, UINT16);

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

cmdline_parse_ctx_t main_ctx[] = {
    (cmdline_parse_inst_t *)&cmd_quit,
    (cmdline_parse_inst_t *)&run_test_case,
    (cmdline_parse_inst_t *)&read_memory,
    (cmdline_parse_inst_t *)&show_pcie_counter,
    (cmdline_parse_inst_t *)&show_pc802_info,
    (cmdline_parse_inst_t *)&show_pc802_data,
    NULL,
};

