#include <stdint.h>

union us_cr_t {
	struct {
		unsigned :2;
		unsigned rstrx:1;
		unsigned rsttx:1;
		unsigned rxen:1;
		unsigned rxdis:1;
		unsigned txen:1;
		unsigned txdis:1;
		unsigned rststa:1;
		unsigned sttbrk:1;
		unsigned stpbrk:1;
		unsigned sttto:1;
		unsigned senda:1;
		unsigned rstit:1;
		unsigned rstnack:1;
		unsigned retto:1;
		unsigned dtren:1;
		unsigned drdis:1;
		unsigned rsten:1;
		unsigned rtsdis:1;
	} bits;
	uint32_t reg;
} us_cr;

union us_mr_t {
	struct {
		unsigned usart_mode:4;
		unsigned usclks:2;
		unsigned chrl:2;
		unsigned sync:1;
		unsigned par:3;
		unsigned nbstop:2;
		unsigned chmode:2;
		unsigned msbf:1;
		unsigned mode9:1;
		unsigned clko:1;
		unsigned over:1;
		unsigned inack:1;
		unsigned dsnack:1;
		unsigned max_iteration:3;
		unsigned :1;
		unsigned filter:1;
	} bits;
	uint32_t reg;
} us_mr;

union us_ier_t {
	struct {
		unsigned rxrdy:1;
		unsigned txrdy:1;
		unsigned rxbrk:1;
		unsigned endrx:1;
		unsigned endtx:1;
		unsigned ovre:1;
		unsigned frame:1;
		unsigned pare:1;
		unsigned timeout:1;
		unsigned txempty:1;
		unsigned iteration:1;
		unsigned txbufe:1;
		unsigned rxbuff:1;
		unsigned nack:1;
		unsigned :2;
		unsigned riic:1;
		unsigned dsric:1;
		unsigned dcdic:1;
		unsigned ctsic:1;
	} bits;
	uint32_t reg;
} us_ier;

typedef union us_ier_t us_idr;
typedef union us_ier_t us_imr;

union us_csr_t {
	struct {
		unsigned rxrdy:1;
		unsigned txrdy:1;
		unsigned rxbrk:1;
		unsigned endrx:1;
		unsigned endtx:1;
		unsigned ovre:1;
		unsigned frame:1;
		unsigned pare:1;
		unsigned timeout:1;
		unsigned txempty:1;
		unsigned iteration:1;
		unsigned txbufe:1;
		unsigned rxbuff:1;
		unsigned nack:1;
		unsigned :2;
		unsigned riic:1;
		unsigned dsric:1;
		unsigned dcdic:1;
		unsigned ctsic:1;
		unsigned ri:1;
		unsigned dsr:1;
		unsigned dcd:1;
		unsigned cts:1;
	} bits;
	uint32_t reg;
} us_csr;

union us_rhr_t {
	struct {
		unsigned rxchr:9;
		unsigned :6;
		unsigned rxsynh:1;
	} bits;
	uint32_t reg;
} us_rhr;

union us_thr_t {
	struct {
		unsigned txchr:9;
		unsigned :6;
		unsigned txsynh:1;
	} bits;
	uint32_t reg;
} us_thr;

union us_brgr_t {
	struct {
		unsigned cd:16;
		unsigned fp:3;
	} bits;
	uint32_t reg;
} us_brgr;

union us_rtor_t {
	struct {
		unsigned to:16;
	} bits;
	uint32_t reg;
} us_rtor;

union us_ttgr_t {
	struct {
		unsigned tg:8;
	} bits;
	uint32_t reg;
} us_ttgr;

union us_fidi_t {
	struct {
		unsigned fi_di_ratio:11;
	} bits;
	uint32_t reg;
} us_fidi;

union us_ner_t {
	struct {
		unsigned nb_errors:8;
	} bits;
	uint32_t reg;
} us_ner;

union us_if_t {
	struct {
		unsigned irda_filter:8;
	} bits;
	uint32_t reg;
} us_if;


