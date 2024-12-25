#include <stdint.h>

union can_mr_t {
	struct {
		unsigned canen:1;
		unsigned lpm:1;
		unsigned abm:1;
		unsigned ovl:1;
		unsigned teof:1;
		unsigned ttm:1;
		unsigned timfrz:1;
		unsigned drpt:1;
	} bits;
	uint32_t reg;
} can_mr;

union can_ier_t {
	struct {
		unsigned mb0:1;
		unsigned mb1:1;
		unsigned mb2:1;
		unsigned mb3:1;
		unsigned mb4:1;
		unsigned mb5:1;
		unsigned mb6:1;
		unsigned mb7:1;
		unsigned :8;
		unsigned erra:1;
		unsigned warn:1;
		unsigned errp:1;
		unsigned boff:1;
		unsigned sleep:1;
		unsigned wakeup:1;
		unsigned tovf:1;
		unsigned tstp:1;
		unsigned cerr:1;
		unsigned serr:1;
		unsigned ferr:1;
		unsigned berr:1;
	} bits;
	uint32_t reg;
} can_ier;

typedef union can_ier_t can_idr;
typedef union can_imr_t can_imr;

union can_sr_t {
	struct {
		unsigned mb0:1;
		unsigned mb1:1;
		unsigned mb2:1;
		unsigned mb3:1;
		unsigned mb4:1;
		unsigned mb5:1;
		unsigned mb6:1;
		unsigned mb7:1;
		unsigned :8;
		unsigned erra:1;
		unsigned warn:1;
		unsigned errp:1;
		unsigned boff:1;
		unsigned sleep:1;
		unsigned wakeup:1;
		unsigned tovf:1;
		unsigned tstp:1;
		unsigned cerr:1;
		unsigned serr:1;
		unsigned ferr:1;
		unsigned berr:1;
		unsigned rbsy:1;
		unsigned tbsy:1;
		unsigned ovlsy:1;
	} bits;
	uint32_t reg;
} can_sr;

union can_br_t {
	struct {
		unsigned phase2:3;
		unsigned :1;
		unsigned phase1:3;
		unsigned :1;
		unsigned propag:3;
		unsigned :1;
		unsigned sjw:2;
		unsigned :2;
		unsigned brp:7;
		unsigned :1;
		unsigned smp:1;
	} bits;
	uint32_t reg;
} can_br;

union can_tim_t {
	struct {
		unsigned timer0:1;
		unsigned timer1:1;
		unsigned timer2:1;
		unsigned timer3:1;
		unsigned timer4:1;
		unsigned timer5:1;
		unsigned timer6:1;
		unsigned timer7:1;
		unsigned timer8:1;
		unsigned timer9:1;
		unsigned timer10:1;
		unsigned timer11:1;
		unsigned timer12:1;
		unsigned timer13:1;
		unsigned timer14:1;
		unsigned timer15:1;
	} bits;
	uint32_t reg;
} can_tim;

union can_timestp_t {
	struct {
		unsigned mtimestamp0:1;
		unsigned mtimestamp1:1;
		unsigned mtimestamp2:1;
		unsigned mtimestamp3:1;
		unsigned mtimestamp4:1;
		unsigned mtimestamp5:1;
		unsigned mtimestamp6:1;
		unsigned mtimestamp7:1;
		unsigned mtimestamp8:1;
		unsigned mtimestamp9:1;
		unsigned mtimestamp10:1;
		unsigned mtimestamp11:1;
		unsigned mtimestamp12:1;
		unsigned mtimestamp13:1;
		unsigned mtimestamp14:1;
		unsigned mtimestamp15:1;
	} bits;
	uint32_t reg;
} can_timestp_t;

union can_ecr_t {
	struct {
		unsigned rec:8;
		unsigned :8;
		unsigned tec:8;
	} bits;
	uint32_t reg;
} can_ecr;

union can_tcr_t {
	struct {
		unsigned mb0:1;
		unsigned mb1:1;
		unsigned mb2:1;
		unsigned mb3:1;
		unsigned mb4:1;
		unsigned mb5:1;
		unsigned mb6:1;
		unsigned mb7:1;
		unsigned :23;
		unsigned timrst:1;
	} bits;
	uint32_t reg;
} can_tcr;

typedef union can_tcr_t can_acr;

union can_mmr_t {
	struct {
		unsigned mtimemark0:1;
		unsigned mtimemark1:1;
		unsigned mtimemark2:1;
		unsigned mtimemark3:1;
		unsigned mtimemark4:1;
		unsigned mtimemark5:1;
		unsigned mtimemark6:1;
		unsigned mtimemark7:1;
		unsigned mtimemark8:1;
		unsigned mtimemark9:1;
		unsigned mtimemark10:1;
		unsigned mtimemark11:1;
		unsigned mtimemark12:1;
		unsigned mtimemark13:1;
		unsigned mtimemark14:1;
		unsigned mtimemark15:1;
		unsigned prior:4;
		unsigned :4;
		unsigned mot:3;
	} bits;
	uint32_t reg;
} can_mmr;

union can_mam_t {
	struct {
		unsigned midvb:18;
		unsigned midva:11;
		unsigned mide:1;
	} bits;
	uint32_t reg;
} can_mam_t;

typedef union can_mam_t can_mid;

union can_mfid_t {
	struct {
		unsigned mfid:29;
	} bits;
	uint32_t reg;
} can_mfid;


union can_msr_t {
	struct {
		unsigned mtimestamp0:1;
		unsigned mtimestamp1:1;
		unsigned mtimestamp2:1;
		unsigned mtimestamp3:1;
		unsigned mtimestamp4:1;
		unsigned mtimestamp5:1;
		unsigned mtimestamp6:1;
		unsigned mtimestamp7:1;
		unsigned mtimestamp8:1;
		unsigned mtimestamp9:1;
		unsigned mtimestamp10:1;
		unsigned mtimestamp11:1;
		unsigned mtimestamp12:1;
		unsigned mtimestamp13:1;
		unsigned mtimestamp14:1;
		unsigned mtimestamp15:1;
		unsigned mdlc:4;
		unsigned mrtr:1;
		unsigned :1;
		unsigned mabt:1;
		unsigned mrdy:1;
		unsigned mmi:1;
	} bits;
	uint32_t reg;
} can_msr;

typedef uint32_t can_mdl;
typedef uint32_t can_mdh;

union can_mcr_t {
	struct {
		unsigned :16;
		unsigned mdlc:4;
		unsigned mrtr:1;
		unsigned :1;
		unsigned macr:1;
		unsigned mtcr:1;
	} bits;
	uint32_t reg;
} can_mcr;
