#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#include <rte_debug.h>
#include <cmdline_parse.h>
#include <cmdline_parse_string.h>
#include <cmdline_parse_num.h>
#include <cmdline_socket.h>
#include <cmdline.h>
#include <cmdline_parse_etheraddr.h>
#include <rte_ether.h>

#include <rte_pmd_bha.h>
#include <test_bha.h>


static struct cmdline *ctx_cmdline;


//test bha pcap mode, testing dfltq pkts cmd
struct test_bha_pcap_mode_dfltq_params {
    cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t bha_pcap_mode_dfltq_token_cmd = TOKEN_STRING_INITIALIZER(struct test_bha_pcap_mode_dfltq_params, cmd, "pcap default");

static void cmd_test_bha_pcap_mode_dfltq_cb(__rte_unused void *ptr_params, __rte_unused struct cmdline *ctx, __rte_unused void *ptr_data)
{
    test_bha_pcap_mode_dfltq_pkts();
}

cmdline_parse_inst_t test_bha_pcap_mode_dfltq_cmd = {
    .f = cmd_test_bha_pcap_mode_dfltq_cb,
    .data = NULL,
    .help_str = "pcap default\n     bha pcap mode. testing default queue pkts cmd",
    .tokens = {
        (void *)&bha_pcap_mode_dfltq_token_cmd,
        NULL
    },
};

//test bha pcap mode, testing ecpri jumbo pkts cmd
struct test_bha_pcap_mode_jumbo_params {
    cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t bha_pcap_mode_jumbo_token_cmd = TOKEN_STRING_INITIALIZER(struct test_bha_pcap_mode_jumbo_params, cmd, "pcap jumbo");

static void cmd_test_bha_pcap_mode_jumbo_cb(__rte_unused void *ptr_params, __rte_unused struct cmdline *ctx, __rte_unused void *ptr_data)
{
    test_bha_pcap_mode_ecpri_jumbo_pkts();
}

cmdline_parse_inst_t test_bha_pcap_mode_jumbo_cmd = {
    .f = cmd_test_bha_pcap_mode_jumbo_cb,
    .data = NULL,
    .help_str = "pcap jumbo\n     bha pcap mode. testing ecpri jumbo pkts cmd",
    .tokens = {
        (void *)&bha_pcap_mode_jumbo_token_cmd,
        NULL
    },
};

//test bha pcap mode, testing ecpri pkts cmd
struct test_bha_pcap_mode_ecpri_params {
    cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t bha_pcap_mode_ecpri_token_cmd = TOKEN_STRING_INITIALIZER(struct test_bha_pcap_mode_ecpri_params, cmd, "pcap ecpri");

static void cmd_test_bha_pcap_mode_ecpri_cb(__rte_unused void *ptr_params, __rte_unused struct cmdline *ctx, __rte_unused void *ptr_data)
{
    test_bha_pcap_mode_ecpri_20pkts();
}

cmdline_parse_inst_t test_bha_pcap_mode_ecpri_cmd = {
    .f = cmd_test_bha_pcap_mode_ecpri_cb,
    .data = NULL,
    .help_str = "pcap ecpri\n     bha pcap mode. testing ecpri pkts cmd",
    .tokens = {
        (void *)&bha_pcap_mode_ecpri_token_cmd,
        NULL
    },
};


//quit test bha cmd
struct test_bha_quit_params {
    cmdline_fixed_string_t cmd;
};

cmdline_parse_token_string_t bha_quit_token_cmd = TOKEN_STRING_INITIALIZER(struct test_bha_quit_params, cmd, "quit");

static void cmd_test_bha_quit_cb(__rte_unused void *ptr_params, __rte_unused struct cmdline *ctx, __rte_unused void *ptr_data)
{
    test_bha_exit();
    if (ctx_cmdline != NULL) {
        cmdline_quit(ctx_cmdline);
        cmdline_stdin_exit(ctx_cmdline);
    }
}

cmdline_parse_inst_t test_bha_quit_cmd = {
    .f = cmd_test_bha_quit_cb,
    .data = NULL,
    .help_str = "quit\n     Quit test bha",
    .tokens = {
        (void *)&bha_quit_token_cmd,
        NULL
    },
};


//test bha cmdline
cmdline_parse_ctx_t bha_prompt_commands[] = {
    (cmdline_parse_inst_t *)&test_bha_pcap_mode_ecpri_cmd,
    (cmdline_parse_inst_t *)&test_bha_pcap_mode_dfltq_cmd,
    (cmdline_parse_inst_t *)&test_bha_pcap_mode_jumbo_cmd,
    (cmdline_parse_inst_t *)&test_bha_quit_cmd,
    NULL
};

static void test_bha_cmdline_proc(void)
{
    ctx_cmdline = cmdline_stdin_new(bha_prompt_commands, "BHA>> ");
    cmdline_interact(ctx_cmdline);
    //cmdline_stdin_exit(ctx_cmdline);
}

void test_bha_cmdline(void)
{
    test_bha_cmdline_proc();
}
