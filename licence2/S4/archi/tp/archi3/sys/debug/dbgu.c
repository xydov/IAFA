#include <stdint.h>

union dbgu_cr_t {
	struct {
		unsigned :2;
		unsigned rstrx:1;
		unsigned rsttx:1;
		unsigned rxen:1;
		unsigned rxdis:1;
		unsigned txen:1;
		unsigned txdis:1;
		unsigned rststa:1;
	} bits;
	uint32_t reg;
} dbgu_cr;

union dbgu_mr_t {
	struct {
		unsigned :9;
		unsigned par:3;
		unsigned :2;
		unsigned chmode:2;
	} bits;
	uint32_t reg;
} dbgu_mr;

union dbgu_ier_t {
	struct {
		unsigned rxrdy:1;
		unsigned txrdy:1;
		unsigned :1;
		unsigned endrx:1;
		unsigned endtx:1;
		unsigned ovre:1;
		unsigned frame:1;
		unsigned pare:1;
		unsigned :1;
		unsigned txempty:1;
		unsigned :1;
		unsigned txbufe:1;
		unsigned rxbuff:1;
		unsigned :17;
		unsigned commrx:1;
		unsigned commtx:1;
	} bits;
	uint32_t reg;
} dbgu_ier;

typedef union dbgu_ier_t dbgu_idr;
typedef union dbgu_ier_t dbgu_imr;
typedef union dbgu_ier_t dbgu_sr;

union dbgu_rhr_t {
	struct {
		unsigned rxchr:8;
	} bits;
	uint32_t reg;
} dbgu_rhr;

union dbgu_thr_t {
	struct {
		unsigned txchr:8;
	} bits;
	uint32_t reg;
} dbgu_thr;

union dbgu_brgr_t {
	struct {
		unsigned cd:16;
	} bits;
	uint32_t reg;
} dbgu_brgr;

union dbgu_cidr_t {
	struct {
		unsigned version:5;
		unsigned eproc:3;
		unsigned nvpsiz:4;
		unsigned nvpsiz2:4;
		unsigned sramsiz:4;
		unsigned arch:8;
		unsigned nvptyp:3;
		unsigned ext:1;
	} bits;
	uint32_t reg;
} dbgu_cidr;

typedef uint32_t dbgu_exid;

union dbgu_fnr_t {
	struct {
		unsigned fnrst:1;
	} bits;
	uint32_t reg;
} dbgu_fnr;




















