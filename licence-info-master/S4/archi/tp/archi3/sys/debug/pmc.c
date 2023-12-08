#include <stdint.h>

union pmc_scer_t {
	struct {
		unsigned : 7;
		unsigned udp:1;
		unsigned pck0:1;
		unsigned pck1:1;
		unsigned pck2:1;
	} bits;
	uint32_t reg;
} pmc_pcer_t;

union pmc_scdr_t {
	struct {
		unsigned pck:1;
		unsigned :6;
		unsigned udp:1;
		unsigned pck0:1;
		unsigned pck1:1;
		unsigned pck2:1;
	} bits;
	uint32_t reg;
} pmc_scdr;

typedef union pmc_scdr_t pmc_scsr;

union pmc_pcer_t {
	struct {
		unsigned :2;
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
 } pmc_pcer;

typedef union pmc_pcer_t pmc_pcdr;
typedef union pmc_pcsr_t pmc_pcsr;

union pmc_ckgr_mor_t {
	struct {
		unsigned moscen:1;
		unsigned oscbypass:1;
		unsigned :6;
		unsigned oscount:8;
	} bits;
	uint32_t reg;
} pmc_ckgr_mor;

union pmc_ckgr_mcfr_t {
	struct {
		unsigned mainf:16;
		unsigned mainrdy:1;
	} bits;
	uint32_t reg;
} pmc_ckgr_mcfr;

union pmc_ckgr_pllr_t {
	struct {
		unsigned div:8;
		unsigned pllcount:6;
		unsigned out:2;
		unsigned mul:11;
		unsigned :1;
		unsigned usbdiv:2;
		unsigned :2;
	} bits;
	uint32_t reg;
} pmc_ckgr_pllr;

union pmc_mckr_t {
	struct {
		unsigned css:2;
		unsigned pres:3;
	} bits;
	uint32_t reg;
} pmc_mckr;

typedef union pmc_mckr_t pmc_pckx;

union pmc_ier_t {
	struct {
		unsigned moscs:1;
		unsigned :1;
		unsigned lock:1;
		unsigned mckrdy:1;
		unsigned :4;
		unsigned pckrdy0:1;
		unsigned pckrdy1:1;
		unsigned pckrdy2:1;
	} bits;
	uint32_t reg;
} pmc_ier;

typedef union pmc_ier_t pmc_idr;
typedef union pmc_ier_t pmc_sr;
typedef union pmc_imr_t pmc_imr;