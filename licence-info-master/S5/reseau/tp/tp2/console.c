#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#include "console.h"

// Sleep time (in ms) between 2 traceroute packets
#define TRACEROUTE_SLEEP 200
#define PING_SLEEP 200

extern int MY_ID;

/* ============================= */
/*  Shared data between threads  */
int end_traceroute = 0;
int end_pingforce  = 0;
pthread_mutex_t lock;
/* ============================= */

/* ==================================================================== */
void print_prompt() {
    printf("R%d> ", MY_ID);
}

/* ==================================================================== */
void print_unknown_command() {
    printf("Error: command not found\n");
}

/* ==================================================================== */
void print_help() {

    printf("Commands:\n");
    printf("  clear\t\t\t Clear the terminal screen.\n");
    printf("  ping <id>\t\t Send echo request to node <id>.\n");
    printf("  pingforce <id>\t Send echo request until response or timeout (1min).\n");
    printf("  show ip neigh\t\t Show neighbors table.\n");
    printf("  show ip route\t\t Show IP routing table.\n");
    printf("  traceroute <id>\t Print the path to destination <id>.\n");
    printf("  help \t\t\t Show help for commands.\n");
    printf("\n");
}

/* ==================================================================== */
void clear_screen() {
    system("clear");
}

/* ==================================================================== */
void print_rt(routing_table_t *rt) {

    printf("========== Routing Table ==========\n" );
    printf("Dest.\t | Next Hop\t | Metric | LifeTime\n" );
    printf("-----------------------------------\n" );
    for (int i=0; i<rt->size; i++) {
        printf("%d \t | %d \t\t | %d \t | %.1f\n",
        rt->tab[i].dest, rt->tab[i].nexthop.id, rt->tab[i].metric,
        difftime(time(NULL), rt->tab[i].time));
    }
    printf("===================================\n" );
}

/* ==================================================================== */
void print_neighbors(neighbors_table_t *nt) {

    printf("============ Neighbors Table ============\n" );
    printf("Id.\t | Host \t | Port \n" );
    printf("-----------------------------------------\n" );
    for (int i=0; i<nt->size; i++) {
        printf("%d\t | %s\t | %d \n", nt->tab[i].id, nt->tab[i].ipv4, nt->tab[i].port);
    }
    printf("=========================================\n" );
}

/* ==================================================================== */
double difftime_nano(struct timespec *tstart) {

    struct timespec tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tend);
    double diff =
        ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
        ((double)tstart->tv_sec + 1.0e-9*tstart->tv_nsec);
    return diff;
}

/* ==================================================================== */
void print_no_route() {
    printf("--> No route to destination.\n");
}

/* ==================================================================== */
void print_ping_reply(packet_data_t *packet) {

    pthread_mutex_lock(&lock);
    end_pingforce=1;
    pthread_mutex_unlock(&lock);

    struct timespec tstart = {packet->time_sec, packet->time_nsec};
    double delta = difftime_nano(&tstart);
    printf("--> Response from R%d: msg_seq=%d ttl=%d time=%.3fs\n",
            packet->src_id, packet->msg_seq, packet->ttl, delta);
}

/* ==================================================================== */
void send_ping_reply(packet_data_t *pdata, routing_table_t *rt) {

    packet_data_t packet;
    packet.type = DATA;
    packet.subtype = ECHO_REPLY;
    packet.src_id = MY_ID;
    packet.dst_id = pdata->src_id;
    packet.ttl = DEFAULT_TTL;
    packet.msg_seq = pdata->msg_seq;
    packet.time_sec = pdata->time_sec; // htonl() ?
    packet.time_nsec = pdata->time_nsec;
    forward_packet(&packet, sizeof(packet_data_t), rt);
}

/* ==================================================================== */
void print_traceroute_path(packet_data_t *packet) {

    struct timespec tstart = {packet->time_sec, packet->time_nsec};
    double delta = difftime_nano(&tstart);
    printf("  %d\t R%d\t %.3fs\n", packet->msg_seq, packet->src_id, delta);
}

/* ==================================================================== */
void print_traceroute_last(packet_data_t *packet) {

    pthread_mutex_lock(&lock);
    end_traceroute=1;
    pthread_mutex_unlock(&lock);
    print_traceroute_path(packet);
}

/* ==================================================================== */
void send_time_exceeded(packet_data_t *pdata, routing_table_t *rt) {

    packet_data_t packet;
    packet.type = DATA;
    packet.subtype = TR_TIME_EXCEEDED;
    packet.src_id = MY_ID;
    packet.dst_id = pdata->src_id;
    packet.ttl = DEFAULT_TTL;
    packet.msg_seq = pdata->msg_seq;
    packet.time_sec = pdata->time_sec;
    packet.time_nsec = pdata->time_nsec;
    forward_packet(&packet, sizeof(packet_data_t), rt);
}

/* ==================================================================== */
void send_traceroute_reply(packet_data_t *pdata, routing_table_t *rt) {

    packet_data_t packet;
    packet.type = DATA;
    packet.subtype = TR_ARRIVED;
    packet.src_id = MY_ID;
    packet.dst_id = pdata->src_id;
    packet.ttl = DEFAULT_TTL;
    packet.msg_seq = pdata->msg_seq;
    packet.time_sec = pdata->time_sec;
    packet.time_nsec = pdata->time_nsec;
    forward_packet(&packet, sizeof(packet_data_t), rt);
}

/* ==================================================================== */
/* ========================== PING THREAD ============================= */
/* ==================================================================== */

void *ping(void *args) {

    packet_data_t packet;
    struct ping_traceroute_args *pargs = (struct ping_traceroute_args *) args;
    struct timespec tstart={0,0};

    packet.type = DATA;
    packet.subtype = ECHO_REQUEST;
    packet.src_id = MY_ID;
    packet.dst_id = pargs->dest;
    packet.ttl = DEFAULT_TTL;
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    packet.time_sec = tstart.tv_sec; // htonl() ?
    packet.time_nsec = tstart.tv_nsec; // htonl() ?
    printf("Ping to R%d.\n", pargs->dest);
    for (int i=0; i<MAX_PING; i++) {
        packet.msg_seq = i;
        if (!forward_packet(&packet, sizeof(packet_data_t), pargs->rt)) {
            print_no_route();
            pthread_exit(NULL);
        }
    }
    usleep(PING_SLEEP * 1000); // wait to be sure you have a response
    pthread_exit(NULL);
}

/* ==================================================================== */
/* ===================== REPEAT PING THREAD =========================== */
/* ==================================================================== */

void *pingforce(void *args) {

    packet_data_t packet;
    struct ping_traceroute_args *pargs = (struct ping_traceroute_args *) args;
    struct timespec tstart={0,0};

    packet.type = DATA;
    packet.subtype = ECHO_REQUEST;
    packet.src_id = MY_ID;
    packet.dst_id = pargs->dest;
    packet.ttl = DEFAULT_TTL;
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    packet.time_sec = tstart.tv_sec; // htonl() ?
    packet.time_nsec = tstart.tv_nsec; // htonl() ?
    printf("Force Ping to R%d. (1min max)\n", pargs->dest);
    pthread_mutex_lock(&lock);
    end_pingforce=0;
    pthread_mutex_unlock(&lock);
    int i=1;
    while (i<60 && !end_pingforce) {
        packet.msg_seq = i++;
        forward_packet(&packet, sizeof(packet_data_t), pargs->rt);
        printf("."); fflush(stdout);
        sleep(1); // 1sec
    }
    printf("\n");
    // usleep(PING_SLEEP * 1000); // wait to be sure you have a response
    pthread_exit(NULL);
}

/* ==================================================================== */
/* ======================= TRACEROUTE THREAD ========================== */
/* ==================================================================== */

void *traceroute(void *args) {

    packet_data_t packet;
    struct ping_traceroute_args *pargs = (struct ping_traceroute_args *) args;
    struct timespec tstart={0,0};

    packet.type = DATA;
    packet.subtype = TR_REQUEST;
    packet.src_id = MY_ID;
    packet.dst_id = pargs->dest;
    printf("Traceroute to R%d, 64 hops max.\n", pargs->dest);
    pthread_mutex_lock(&lock);
    end_traceroute=0;
    pthread_mutex_unlock(&lock);
    int i=1;
    while (i<64 && !end_traceroute) {
        packet.msg_seq = i;
        packet.ttl = i++;
        clock_gettime(CLOCK_MONOTONIC, &tstart);
        packet.time_sec = tstart.tv_sec;
        packet.time_nsec = tstart.tv_nsec;
        if (!forward_packet(&packet, sizeof(packet_data_t), pargs->rt)) {
            print_no_route();
            pthread_exit(NULL);
        }
        // printf("sent pack %d src %d dst %d ttl %d \n", packet.msg_seq, packet.src_id, packet.dst_id, packet.ttl);
        usleep(TRACEROUTE_SLEEP * 1000);
    }
    pthread_exit(NULL);
}
