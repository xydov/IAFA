#ifndef __PACKET_H__
#define __PACKET_H__

// Packet types
#define CTRL 1
#define DATA 0

// Data types
#define ECHO_REQUEST 1
#define ECHO_REPLY 2
#define TR_REQUEST 10
#define TR_TIME_EXCEEDED 11
#define TR_ARRIVED 12

#define MAX_DV_SIZE 20
#define DEFAULT_TTL 32

// Distance vector entry
typedef struct {
    unsigned char dest;
    unsigned char metric;
} dv_entry_t;

// Control packet
typedef struct {
    unsigned char type; // CTRL
    unsigned char src_id;
    unsigned char dv_size;
    dv_entry_t dv[MAX_DV_SIZE];
} packet_ctrl_t;

// Data packet
typedef struct {
    unsigned char type; // DATA
    unsigned char subtype; // ECHO REQUEST, ECHO REPLY, TRACEROUTE...
    unsigned char src_id;
    unsigned char dst_id;
    unsigned char ttl;
    unsigned char msg_seq;
    unsigned long time_sec;
    unsigned long time_nsec;
} packet_data_t;

#endif
