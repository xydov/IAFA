#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "router.h"
#include "packet.h"

// CONSOLE COMMANDS
#define CLEAR "clear"
#define HELP "help"
#define PING "ping"
#define PINGFORCE "pingforce"
#define SH_IP_ROUTE "show ip route"
#define SH_IP_ROUTE_2 "ipr"
#define SH_IP_NEIGH "show ip neigh"
#define SH_IP_NEIGH_2 "ipn"
#define TRACEROUTE "traceroute"

#define MAX_PING 1

// Ping and Traceroute thread parameters
struct ping_traceroute_args {
    int dest;
    routing_table_t *rt;
};

/* ==================================================================== */
void clear_screen();
void print_prompt();
void print_unknown_command();
void print_help();
void print_rt(routing_table_t *rt);
void print_neighbors(neighbors_table_t *nt);

void *ping(void *args);
void *pingforce(void *args);
void send_ping_reply(packet_data_t *pdata, routing_table_t *rt);
void print_ping_reply(packet_data_t *packet);

void *traceroute(void *args);
void send_time_exceeded(packet_data_t *pdata, routing_table_t *rt);
void send_traceroute_reply(packet_data_t *pdata, routing_table_t *rt);
void print_traceroute_path(packet_data_t *packet);
void print_traceroute_last(packet_data_t *packet);

#endif
