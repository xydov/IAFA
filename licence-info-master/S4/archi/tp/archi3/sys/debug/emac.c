#include <stdint.h>

union emac_ncr_t {
	struct {
		unsigned lb:1;
		unsigned llb:1;
		unsigned re:1;
		unsigned te:1;
		unsigned mpe:1;
		unsigned clrstat:1;
		unsigned incstat:1;
		unsigned westat:1;
		unsigned bp:1;
		unsigned tstart:1;
		unsigned thalt:1;
	} bits;
	uint32_t reg;
} emac_ncr;

union emac_ncfgr_t {
	struct {
		unsigned spd:1;
		unsigned fd:1;
		unsigned :1;
		unsigned jframe:1;
		unsigned caf:1;
		unsigned nbc:1;
		unsigned mti:1;
		unsigned uni:1;
		unsigned big:1;
		unsigned :1;
		unsigned clk:2;
		unsigned rty:1;
		unsigned pae:1;
		unsigned rbof:2;
		unsigned rlce:1;
		unsigned drfcs:1;
		unsigned efrhd:1;
		unsigned irxfcs:1;
	} bits;
	uint32_t reg;
} emac_ncfgr;

union emac_nsr_t {
	struct {
		unsigned :1;
		unsigned mdio:1;
		unsigned idle:1;
	} bits;
	uint32_t reg;
} emac_nsr_t;

union emac_tsr_t {
	struct {
		unsigned ubr:1;
		unsigned col:1;
		unsigned rle:1;
		unsigned tgo:1;
		unsigned bex:1;
		unsigned comp:1;
		unsigned und:1;
	} bits;
	uint32_t reg;
} emac_tsr;

union emac_rbqp_t {
	struct {
		unsigned :2;
		unsigned addr:30;
	} bits;
	uint32_t reg;
} emac_rbqp;

union emac_tbqp_t {
	struct {
		unsigned :2;
		unsigned addr:30;
	} bits;
	uint32_t reg;
} emac_tbqp;

union emac_rsr_t {
	struct {
		unsigned bna:1;
		unsigned rec:1;
		unsigned ovr:1;
	} bits;
	uint32_t reg;
} emac_rsr;

union emac_isr_t {
	struct {
		unsigned mfd:1;
		unsigned rcomp:1;
		unsigned rxubr:1;
		unsigned txubr:1;
		unsigned tund:1;
		unsigned rle:1;
		unsigned txerr:1;
		unsigned tcomp:1;
		unsigned :2;
		unsigned rovr:1;
		unsigned hresp:1;
		unsigned pfr:1;
		unsigned ptz:1;
	} bits;
	uint32_t reg;
} emac_isr;

typedef union emac_isr_t emac_ier;
typedef union emac_isr_t emac_idr;
typedef union emac_isr_t emac_ier;

union emac_man_t {
	struct {
		unsigned data:16;
		unsigned code:2;
		unsigned rega:5;
		unsigned phya:5;
		unsigned rw:2;
		unsigned sof:2;
	} bits;
	uint32_t reg;
} emac_man;

union emac_ptr_t {
	struct {
		unsigned ptime:16;
	} bits;
	uint32_t reg;
} emac_ptr;

typedef uint32_t emac_hrb;
typedef uint32_t emac_hrt;
typedef uint32_t emac_sa1b;

union emac_sa1t_t {
	struct {
		unsigned addr:16;
	} bits;
	uint32_t reg;
} emac_sa1t;

typedef uint32_t emac_sa2b;
typedef uint32_t emac_sa3b;
typedef uint32_t emac_sa4b;
typedef union emac_sa1t_t emac_sa2t;
typedef union emac_sa1t_t emac_sa3t;
typedef union emac_sa1t_t emac_sa4t;

union emac_tid_t {
	struct {
		unsigned tid:16;
	} bits;
	uint32_t reg;
} emac_tid;

union emac_usrio_t {
	struct {
		unsigned rmii:1;
		unsigned clken:1;
	} bits;
	uint32_t reg;
} emac_usrio;

union emac_pfr_t {
	struct {
		unsigned frok:16;
	} bits;
	uint32_t reg;
} emac_pfr;

union emac_fto_t {
	struct {
		unsigned frok:24;
	} bits;
	uint32_t reg;
} emac_fto;

union emac_scf_t {
	struct {
		unsigned scf:16;
	} bits;
	uint32_t reg;
} emac_scf;

union emac_mcf_t {
	struct {
		unsigned mcf:16;
	} bits;
	uint32_t reg;
} emac_mcf;

union emac_fro_t {
	struct {
		unsigned frok:24;
	} bits;
	uint32_t reg;
} emac_fro;

union emac_fcse_t {
	struct {
		unsigned fcse:8;
	} bits;
	uint32_t reg;
} emac_fcse;

union emac_ale_t {
	struct {
		unsigned ale:8;
	} bits;
	uint32_t reg;
} emac_ale;

union emac_dtf_t {
	struct {
		unsigned dtf:16;
	} bits;
	uint32_t reg;
} emac_dtf;

union emac_lcol_t {
	struct {
		unsigned lcol:8;
	} bits;
	uint32_t reg;
} emac_lcol;

union emac_excol_t {
	struct {
		unsigned excol:8;
	} bits;
	uint32_t reg;
} emac_excol;

union emac_tund_t {
	struct {
		unsigned tund:8;
	} bits;
	uint32_t reg;
} emac_tund;

union emac_cse_t {
	struct {
		unsigned cse:8;
	} bits;
	uint32_t reg;
} emac_cse;

union emac_rre_t {
	struct {
		unsigned rre:16;
	} bits;
	uint32_t reg;
} emac_rre;

union emac_rovr_t {
	struct {
		unsigned rovr:8;
	} bits;
	uint32_t reg;
} emac_rovr;

union emac_rse_t {
	struct {
		unsigned rse:8;
	} bits;
	uint32_t reg;
} emac_rse;

union emac_ele_t {
	struct {
		unsigned exl:8;
	} bits;
	uint32_t reg;
} emac_exl;

union emac_rja_t {
	struct {
		unsigned rjb:8;
	} bits;
	uint32_t reg;
} emac_rja;

union emac_usf_t {
	struct {
		unsigned usf:8;
	} bits;
	uint32_t reg;
} emac_usf;

union emac_ste_t {
	struct {
		unsigned sqer:8;
	} bits;
	uint32_t reg;
} emac_ste;

union emac_rle_t {
	struct {
		unsigned rlfm:8;		
	} bits;
} emac_rle;