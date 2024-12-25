#ifndef __UTILS_H__
#define __UTILS_H__

#include "router.h"

#define RTR_BASE_PORT 5555
#define PORT(x) (x+RTR_BASE_PORT)


/* ==================================================================== */
/* ========================= LOG FUNCTIONS ============================ */
/* ==================================================================== */

// Log message to file log/Ri.txt
// Format: DATE [TAG]: MESSAGE
void logger(const char *tag, const char *message, ...);

// Log Distance Vector (DV) included in packet *p
// if output then the DV is sent to neigh, else it is received from neigh
void log_dv(packet_ctrl_t *p, node_id_t neigh, int output);

/* ==================================================================== */
/* ========================== SEND PACKET  ============================ */
/* ==================================================================== */

void send_packet(void *packet, int psize, char *ipv4, unsigned short int port);

/* ==================================================================== */
/* =============== INIT NEIGHBORS AND ROUTING TABLE =================== */
/* ==================================================================== */

// Read topo from conf file
void read_neighbors(char *file, int rid, neighbors_table_t *nt);

// Add route to routing table
void add_route(routing_table_t *rt, node_id_t dest, const overlay_addr_t *next, short metric);

// Init routing table with one entry (myself)
void init_routing_table(routing_table_t *rt);

/* Init full routing table according to topology t3.txt */
void init_full_routing_table(routing_table_t *rt);

/* ==================================================================== */
/* ======================== PROCESS COMMAND =========================== */
/* ==================================================================== */

void process_command(char *cmd, routing_table_t *rt, neighbors_table_t *nt);

#endif
