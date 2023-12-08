#include "console.h"
#include "utils.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr, htons
#include <unistd.h> // close()

extern int MY_ID;
// #define LOG_MSG_MAX_SIZE 256

/* ==================================================================== */
/* ========================= LOG FUNCTIONS ============================ */
/* ==================================================================== */

// Log message to file log/Ri.txt
// Format: DATE [TAG]: MESSAGE
void logger(const char *tag, const char *message, ...) {

    time_t now;
    char buf[256], file_name[32];
    va_list params;

    time(&now);
    strncpy(buf, ctime(&now), sizeof(buf));
    buf[strlen(buf)-1]='\0'; // remove new line from ctime function

    sprintf(file_name, "%s%d%s", "log/R", MY_ID, ".txt");
    FILE *f = fopen(file_name, "at");

    fprintf(f, "%s [%s]: ", buf, tag);
    va_start(params, message);
    vfprintf(f, message, params);
    fprintf(f, ".\n");
    va_end(params);
    fclose(f);
}

// Log Distance Vector (DV) included in packet *p
// if output then the DV is sent to neigh, else it is received from neigh
void log_dv(packet_ctrl_t *p, node_id_t neigh, int output) {

    char buf_dv[256];
    char buf_dve[32];
    strcpy(buf_dv, "\t DEST | METRIC \n");
    for (int i=0; i<p->dv_size; i++) {
        sprintf(buf_dve, "\t   %d  |  %d\n", p->dv[i].dest, p->dv[i].metric);
        strcat(buf_dv, buf_dve);
    }
    if (output)
        logger("HELLO TH", "DV sent to R%d :\n %s", neigh, buf_dv);
    else
        logger("SERVER TH", "DV received from R%d :\n %s", neigh, buf_dv);
}

/* ==================================================================== */
/* ========================== SEND PACKET  ============================ */
/* ==================================================================== */
void send_packet(void *packet, int psize, char *ipv4, unsigned short int port) {

    int sock;
    struct sockaddr_in sockaddr_dst;

    // create new datagram socket
    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    // set destination
    memset(&sockaddr_dst, 0, sizeof(struct sockaddr_in));
    sockaddr_dst.sin_family = AF_INET;
    sockaddr_dst.sin_port = htons(port);
    sockaddr_dst.sin_addr.s_addr = inet_addr(ipv4);
    // send packet
    if ( sendto(
            sock, packet, psize, 0,
            (struct sockaddr *) &sockaddr_dst,
            sizeof(sockaddr_dst)) < 0 ) {
        perror("sendto error");
        exit(EXIT_FAILURE);
    }
    close(sock);
}


/* ==================================================================== */
/* =============== INIT NEIGHBORS AND ROUTING TABLE =================== */
/* ==================================================================== */

// Init node's overlay address
void init_node(overlay_addr_t *addr, node_id_t id, char *ip) {

    addr->id = id;
    addr->port = PORT(id);
    strcpy(addr->ipv4, ip);
}

// Add node to neighbor's table
void add_neighbor(neighbors_table_t *nt, const overlay_addr_t *node) {

    assert(nt->size < MAX_NEIGHBORS);
    nt->tab[nt->size] = *node;
    nt->size++;
}

// Read topo from conf file
void read_neighbors(char *file, int rid, neighbors_table_t *nt) {

    FILE *fichier = NULL;
    char ligne[80];
    int id = 0;
    overlay_addr_t node;
    char *token;

   	fichier = fopen(file, "rt");
   	if (fichier == NULL) {
   		perror("[Config] Error opening configuration file.\n");
   		exit(EXIT_FAILURE);
   	}

    while (!feof(fichier)) {
        // read line
        fgets(ligne, sizeof(ligne), fichier);
        ligne[strlen(ligne)-1]='\0'; // remove '\n'
        // printf("%s\n", ligne);
        if (ligne[0]!='#') {
            sscanf(ligne, "%d", &id);
            if (id == rid) {
                // read neighbors
                token = strtok(ligne, " ");
                token = strtok(NULL, " "); // discard first number (rid)
                while (token != NULL) {
                    // printf( "|%s|", token );
                    id = atoi(token);
                    init_node(&node, id, "127.0.0.1");
                    add_neighbor(nt, &node);
                    token = strtok(NULL, " ");
                }
                fclose(fichier);
                return ;
            }
        }
    }
    fclose(fichier);
}

// Add route to routing table
void add_route(routing_table_t *rt, node_id_t dest, const overlay_addr_t *next, short metric) {

    assert(rt->size < MAX_ROUTES);
    rt->tab[rt->size].dest    = dest;
    rt->tab[rt->size].nexthop = *next;
    rt->tab[rt->size].metric  = metric;
    rt->tab[rt->size].time    = time(NULL);
    rt->size++;
}

// Init routing table with one entry (myself)
void init_routing_table(routing_table_t *rt) {

    overlay_addr_t me;
    init_node(&me, MY_ID, LOCALHOST);
    add_route(rt, MY_ID, &me, 0);
}

/* Init full routing table according to topology t3.txt
 #     R3
 #   /    \
 #  R1     R2
 #   \    /
 #     R4
 */
void init_full_routing_table(routing_table_t *rt) {

    overlay_addr_t r1, r2, r3, r4;
    init_node(&r1, 1, LOCALHOST);
    init_node(&r2, 2, LOCALHOST);
    init_node(&r3, 3, LOCALHOST);
    init_node(&r4, 4, LOCALHOST);

    switch (MY_ID) {
        case 1:
            init_routing_table(rt);
            add_route(rt, 3, &r3, 1);
            add_route(rt, 4, &r4, 1);
            add_route(rt, 2, &r3, 2);
            break;

        case 2:
            init_routing_table(rt);
            add_route(rt, 3, &r3, 1);
            add_route(rt, 4, &r4, 1);
            add_route(rt, 1, &r3, 2);
            break;

        case 3:
            init_routing_table(rt);
            add_route(rt, 1, &r1, 1);
            add_route(rt, 2, &r2, 1);
            add_route(rt, 4, &r1, 2);
            break;

        case 4:
            init_routing_table(rt);
            add_route(rt, 1, &r1, 1);
            add_route(rt, 2, &r2, 1);
            add_route(rt, 3, &r1, 2);
            break;
    }
}

/* ==================================================================== */
/* ======================== PROCESS COMMAND =========================== */
/* ==================================================================== */

void process_command(char *cmd, routing_table_t *rt, neighbors_table_t *nt) {

    pthread_t th_id;

    if (!strcmp(cmd, HELP)) {
        print_help();
        return;
    }
    if (!strcmp(cmd, CLEAR)) {
        clear_screen();
        return;
    }
    if (!strcmp(cmd, SH_IP_ROUTE) || !strcmp(cmd, SH_IP_ROUTE_2)) {
        print_rt(rt);
        return;
    }
    if (!strcmp(cmd, SH_IP_NEIGH) || !strcmp(cmd, SH_IP_NEIGH_2)) {
        print_neighbors(nt);
        return;
    }
    if (!strncmp(cmd, PING, strlen(PING)) && cmd[strlen(PING)]==' ') {
        char temp[16];
        int did;
        sscanf(cmd, "%s%d", temp, &did);
        struct ping_traceroute_args args = {did, rt};
        pthread_create(&th_id, NULL, &ping, &args);
        pthread_join(th_id, NULL);
        return;
    }
    if (!strncmp(cmd, PINGFORCE, strlen(PINGFORCE))) {
        char temp[16];
        int did;
        sscanf(cmd, "%s%d", temp, &did);
        struct ping_traceroute_args args = {did, rt};
        pthread_create(&th_id, NULL, &pingforce, &args);
        pthread_join(th_id, NULL);
        return;
    }
    if (!strncmp(cmd, TRACEROUTE, strlen(TRACEROUTE))) {
        char temp[16];
        int did;
        sscanf(cmd, "%s%d", temp, &did);
        struct ping_traceroute_args args = {did, rt};
        pthread_create(&th_id, NULL, &traceroute, &args);
        pthread_join(th_id, NULL);
        return;
    }
    if (strlen(cmd)!=0)
        print_unknown_command();
}
