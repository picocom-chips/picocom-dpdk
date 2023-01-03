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

extern int quit_flag;
extern void pc802_kni_print_stats(void);

struct cmd_quit_result {
    cmdline_fixed_string_t quit;
};

static void cmd_quit_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    quit_flag = 1;
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

extern int start_flag;

struct cmd_start_result {
    cmdline_fixed_string_t start;
};

static void cmd_start_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    start_flag = 1;
}

cmdline_parse_token_string_t cmd_start_start =
    TOKEN_STRING_INITIALIZER(struct cmd_start_result, start, "start");

cmdline_parse_inst_t cmd_start = {
    .f = cmd_start_parsed,
    .data = NULL,
    .help_str = "start: Start to send DL msg per slot",
    .tokens = {
        (void *)&cmd_start_start,
        NULL,
    },
};

////////////////////////////////////////////////////////////////////////
struct cmd_stop_result {
    cmdline_fixed_string_t stop;
};

static void cmd_stop_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    start_flag = 0;
}

cmdline_parse_token_string_t cmd_stop_stop =
    TOKEN_STRING_INITIALIZER(struct cmd_stop_result, stop, "stop");

cmdline_parse_inst_t cmd_stop = {
    .f = cmd_stop_parsed,
    .data = NULL,
    .help_str = "start: Stop to send DL msg per slot",
    .tokens = {
        (void *)&cmd_stop_stop,
        NULL,
    },
};

//////////////////////////////////////////////////////////////////////////
extern int burst_flag;
extern uint32_t burst_cnt;

struct cmd_send_result {
    cmdline_fixed_string_t send;
    uint32_t slots;
};

static void cmd_send_parsed(__attribute__((unused)) void *parsed_result,
                struct cmdline *cl,
                __attribute__((unused)) void *data)
{
    struct cmd_send_result *res = parsed_result;
    burst_cnt = res->slots;
    burst_flag = 1;
    start_flag = 1;
}

cmdline_parse_token_string_t cmd_send_send =
    TOKEN_STRING_INITIALIZER(struct cmd_send_result, send, "send");
cmdline_parse_token_num_t cmd_send_slots =
    TOKEN_NUM_INITIALIZER(struct cmd_send_result, slots, RTE_UINT32);

cmdline_parse_inst_t cmd_send = {
    .f = cmd_send_parsed,
    .data = NULL,
    .help_str = "send #slots: send #slots DL slots and then stop",
    .tokens = {
        (void *)&cmd_send_send,
        (void *)&cmd_send_slots,
        NULL,
    },
};

cmdline_parse_ctx_t main_ctx[] = {
    (cmdline_parse_inst_t *)&cmd_quit,
    (cmdline_parse_inst_t *)&cmd_start,
    (cmdline_parse_inst_t *)&cmd_stop,
    (cmdline_parse_inst_t *)&cmd_send,
    NULL,
};

