/* Two Wire Interface */
#include <stdint.h>

union twi_cr_t {
	struct {
		unsigned start:1;
		unsigned stop:1;
		unsigned msen:1;
		unsigned msdis:1;
		unsigned :3;
		unsigned swrst:1;
	} bits;
	uint32_t reg;
} twi_cr;

union twi_mmr_t {
	struct {
		unsigned :8;
		unsigned iadrsz:2;
		unsigned :2;
		unsigned mread:1;
		unsigned :3;
		unsigned dadr:7;
	} bits;
	uint32_t reg;
} twi_mmr;

union twi_iadr_t {
	struct {
		unsigned iadr:24;
	} bits;
	uint32_t reg;
} twi_iadr_t;

union twi_cwgr_t {
	struct {
		unsigned cldiv:16;
		unsigned ckdiv:2;
	} bits;
	uint32_t reg;
} twi_cwgr;

union twi_sr_t {
	struct {
		unsigned txcomp:1;
		unsigned rxrdy:1;
		unsigned txrdy:1;
		unsigned :5;
		unsigned nack:1;
	} bits;
	uint32_t reg;
} twi_sr;

typedef union twi_sr_t twi_ier;
typedef union twi_idr_t twi_idr;
typedef union twi_imr_t twi_imr;

union twi_rhr_t {
	struct {
		unsigned rxdata:8;
	} bits;
	uint32_t reg;
} twi_rhr;

union twi_thr_t {
	struct {
		unsigned txdata:8;
	} bits;
	uint32_t reg;
} twi_thr;


