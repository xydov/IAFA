#ifndef __ROUTER_H__
#define __ROUTER_H__

#include <time.h>
#include "packet.h"

// #define MAX_DATA 251
#define MAX_NEIGHBORS 5
#define MAX_ROUTES 20
#define IPV4_ADR_STRLEN 16  // == INET_ADDRSTRLEN
#define LOCALHOST "127.0.0.1"


// Small unsigned integer as node ID
typedef unsigned char node_id_t;

// Overlay address
// ===============
typedef struct {
    node_id_t id;
    char ipv4[IPV4_ADR_STRLEN]; // string (e.g., "127.0.0.1")
    unsigned short int port;
} overlay_addr_t;

// Neighbors Table
// ===============
typedef struct {
    unsigned short int  size;
    overlay_addr_t      tab[MAX_NEIGHBORS];
} neighbors_table_t;

// Routing Table
// ===============
typedef struct {
    node_id_t       dest;
    overlay_addr_t  nexthop;
    unsigned char   metric;
    time_t          time;
} routing_table_entry_t;

typedef struct {
    unsigned short int     size;
    routing_table_entry_t  tab[MAX_ROUTES];
} routing_table_t;

/* ==================================================================== */
// Thread parameters
struct th_args {
    routing_table_t *rt;
    neighbors_table_t *nt;
};

/* ==================================================================== */

int forward_packet(packet_data_t *packet, int psize, routing_table_t *rt);

#endif
