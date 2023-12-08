#include <stdint.h>

union pwm_mr_t {
	struct {
		unsigned diva:8;
		unsigned prea:4;
		unsigned :4;
		unsigned divb:8;
		unsigned preb:4;
	} bits;
	uint32_t reg;
} pwm_mr;

union pwm_ena_t {
	struct {
		unsigned chid0:1;
		unsigned chid1:1;
		unsigned chid2:1;
		unsigned chid3:1;
	} bits;
	uint32_t reg;
} pwm_ena;

typedef union pwm_ena_t pwm_dis;
typedef union pwm_ena_t pwm_sr;
typedef union pwm_ena_t pwm_ier;
typedef union pwm_ena_t pwm_idr;
typedef union pwm_ena_t pwm_imr;
typedef union pwm_ena_t pwm_isr;

union pwm_cmr_t {
	struct {
		unsigned cpre:4;
		unsigned :4;
		unsigned calg:1;
		unsigned cpol:1;
		unsigned cpd:1;
	} bits;
	uint32_t reg;
} pwm_cmr;

typedef uint32_t pwm_cdty;
typedef uint32_t pwm_cprd;
typedef uint32_t pwm_ccnt;
typedef uint32_t pwm_cupd;


