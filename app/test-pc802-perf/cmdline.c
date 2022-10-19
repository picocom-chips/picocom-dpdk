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

extern int pc802_test_pcie( int len, int time, int ch, int type );

struct cmd_quit_result {
    cmdline_fixed_string_t quit;
};

static void cmd_quit_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
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

cmdline_parse_ctx_t main_ctx[] = {
    (cmdline_parse_inst_t *)&cmd_quit,
    (cmdline_parse_inst_t *)&test_pcie,
    NULL,
};

