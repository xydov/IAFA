#include <stdint.h>

union ssc_cr_t {
	struct {
		unsigned rxen:1;
		unsigned rxdis:1;
		unsigned :6;
		unsigned txen:1;
		unsigned txdis:1;
		unsigned :5;
		unsigned swrst:1;
	} bits;
	uint32_t reg;
} ssc_cr;

union ssc_cmr_t {
	struct {
		unsigned div:12;
	} bits;
	uint32_t reg;
} ssc_cmr;

union ssc_rcmr_t {
	struct {
		unsigned cks:2;
		unsigned cko:3;
		unsigned cki:1;
		unsigned ckg:2;
		unsigned start:4;
		unsigned stop:1;
		unsigned :3;
		unsigned stddly:8;
		unsigned period:8;
	} bits;
	uint32_t reg;
} ssc_rcmr;

union ssc_rfmr_t {
	struct {
		unsigned datlen:5;
		unsigned loop:1;
		unsigned :1;
		unsigned msbf:1;
		unsigned datnb:4;
		unsigned :4;
		unsigned fslen:4;
		unsigned fsos:3;
		unsigned :1;
		unsigned fsedge:1;
	} bits;
	uint32_t reg;
} ssc_rfmr;


union ssc_tcmr_t {
	struct {
		unsigned cks:2;
		unsigned cko:3;
		unsigned cki:1;
		unsigned ckg:3;
		unsigned start:4;
		unsigned :4;
		unsigned sttdly:8;
		unsigned period:8;
	} data;
	uint32_t reg;
} ssc_tcmr;


union ssc_tfmr_t {
	struct {
		unsigned datlen:5;
		unsigned datdef:1;
		unsigned :1;
		unsigned msbf:1;
		unsigned datnb:4;
		unsigned :4;
		unsigned fslen:4;
		unsigned fsos:3;
		unsigned fsden:1;
		unsigned fsedge:1;
	} bits;
	uint32_t reg;
} ssc_tfmr_t;

typedef uint32_t ssc_rhr;
typedef uint32_t ssc_thr;

union ssc_rshr_t {
	struct {
		unsigned rsdat:16;
	} bits;
	uint32_t reg;
} ssc_rshr;

union ssc_tshr_t {
	struct {
		unsigned tsdat:16;
	} bits;
	uint32_t reg;
} ssc_tshr;

union ssc_rc0r_t {
	struct {
		unsigned cp0:16;
	} bits;
	uint32_t reg;
} ssc_rc0r;

union ssc_rc1r_t {
	struct {
		unsigned cp1:16;
	} bits;
	uint32_t reg;
} ssc_rc1r;

union ssc_sr_t {
	struct {
		unsigned txrdy:1;
		unsigned txempty:1;
		unsigned endtx:1;
		unsigned txbufe:1;
		unsigned rxrdy:1;
		unsigned ovrun:1;
		unsigned endrx:1;
		unsigned rxbuff:1;
		unsigned cp0:1;
		unsigned cp1:1;
		unsigned rxsyn:1;
		unsigned txsyn:1;
		unsigned :4;
		unsigned txen:1;
		unsigned rxen:1;
	} bits;
	uint32_t reg;
} ssc_sr;

typedef union ssc_sr_t ssc_ier;
typedef union ssc_sr_t ssc_idr;
typedef union ssc_sr_t ssc_imr;


