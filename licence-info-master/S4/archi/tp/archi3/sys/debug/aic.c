#include <stdint.h>

union aic_smr_t {
	struct {
		unsigned prior:3;
		unsigned :2;
		unsigned srctype:2;
	} bits;
	uint32_t reg;
} aic_smr;


/* No union for aic_svr/ivr/fvr, full 32 bits register */

union aic_isr_t {
	struct {
		unsigned irqid:5;
	} bits;
	uint32_t reg;
} aic_isr;

union aic_ipr_t {
	struct {
		unsigned fiq:1;
		unsigned sys:1;
		unsigned pid2:1;
		unsigned pid3:1;
		unsigned pid4:1;
		unsigned pid5:1;
		unsigned pid6:1;
		unsigned pid7:1;
		unsigned pid8:1;
		unsigned pid9:1;
		unsigned pid10:1;
		unsigned pid11:1;
		unsigned pid12:1;
		unsigned pid13:1;
		unsigned pid14:1;
		unsigned pid15:1;
		unsigned pid16:1;
		unsigned pid17:1;
		unsigned pid18:1;
		unsigned pid19:1;
		unsigned pid20:1;
		unsigned pid21:1;
		unsigned pid22:1;
		unsigned pid23:1;
		unsigned pid24:1;
		unsigned pid25:1;
		unsigned pid26:1;
		unsigned pid27:1;
		unsigned pid28:1;
		unsigned pid29:1;
		unsigned pid30:1;
		unsigned pid31:1;
	} bits;
	uint32_t reg;
} aic_ipr;

/* AIC Interrupt Mask Register */
typedef union aic_ipr_t aic_imr;

union aic_cisr {
	struct {
		unsigned nifq:1;
		unsigned nirq:1;
	} bits;
	uint32_t reg;
} aic_cisr;

typedef union aic_ipr_t aic_iecr;
typedef union aic_ipr_t aic_idcr;
typedef union aic_ipr_t aic_iccr;
typedef union aic_ipr_t aic_iscr;

typedef uint32_t aic_spu;

union aic_dcr_t {
	struct {
		unsigned prot:1;
		unsigned gmsk:1;
	} bits;
	uint32_t reg;
} aic_dcr;

union aic_ffer_t {
	struct {
		unsigned :1;
		unsigned sys:1;
		unsigned pid2:1;
		unsigned pid3:1;
		unsigned pid4:1;
		unsigned pid5:1;
		unsigned pid6:1;
		unsigned pid7:1;
		unsigned pid8:1;
		unsigned pid9:1;
		unsigned pid10:1;
		unsigned pid11:1;
		unsigned pid12:1;
		unsigned pid13:1;
		unsigned pid14:1;
		unsigned pid15:1;
		unsigned pid16:1;
		unsigned pid17:1;
		unsigned pid18:1;
		unsigned pid19:1;
		unsigned pid20:1;
		unsigned pid21:1;
		unsigned pid22:1;
		unsigned pid23:1;
		unsigned pid24:1;
		unsigned pid25:1;
		unsigned pid26:1;
		unsigned pid27:1;
		unsigned pid28:1;
		unsigned pid29:1;
		unsigned pid30:1;
		unsigned pid31:1;
	} bits;
	uint32_t reg;
} aic_ffer;

typedef union aic_ffer_t aic_ffdr;
typedef union aic_ffer_t aic_ffsr;
