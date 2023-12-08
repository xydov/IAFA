#include <stdint.h>

union adc_cr_t {
	struct {
		unsigned start:1;
	} bits;
	uint32_t reg;
} adc_cr;

union adc_mr_t {
	struct {
		unsigned trgen:1;
		unsigned trgsel:3;
		unsigned lowres:1;
		unsigned sleep:1;
		unsigned :2;
		unsigned prescal:6;
		unsigned :2;
		unsigned startup:5;
		unsigned :3;
		unsigned shtim:4; 
	} bits;
	uint32_t reg;
} adc_mr;

union adc_cher_t {
	struct {
		unsigned ch0:1;
		unsigned ch1:1;
		unsigned ch2:1;
		unsigned ch3:1;
		unsigned ch4:1;
		unsigned ch5:1;
		unsigned ch6:1;
		unsigned ch7:1;
	} bits;
	uint32_t reg;
} adc_cher_t;

typedef union adc_cher_t adc_chdr;
typedef union adc_cher_t adc_chsr;

union adc_sr_t {
	struct {
		unsigned eoc0:1;
		unsigned eoc1:1;
		unsigned eoc2:1;
		unsigned eoc3:1;
		unsigned eoc4:1;
		unsigned eoc5:1;
		unsigned eoc6:1;
		unsigned eoc7:1;
		unsigned ovre0:1;
		unsigned ovre1:1;
		unsigned ovre2:1;
		unsigned ovre3:1;
		unsigned ovre4:1;
		unsigned ovre5:1;
		unsigned ovre6:1;
		unsigned ovre7:1;
		unsigned drdy:1;
		unsigned govre:1;
		unsigned endrx:1;
		unsigned rxbuff:1;
	} bits;
	uint32_t reg;
} adc_sr;

union adc_lcdr_t {
	struct {
		unsigned ldata:10;
	} bits;
	uint32_t reg;
} adc_lcdr;

typedef union adc_sr_t adc_ier;
typedef union adc_sr_t adc_idr;
typedef union adc_sr_t adc_imr;

union adc_cdr_t {
	struct {
		unsigned data:10;
	} bits;
	uint32_t reg;
} adc_cdr;



