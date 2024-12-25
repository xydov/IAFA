#include <stdint.h>

union rtt_mr_t {
	struct {
		unsigned rtpres:16;
		unsigned almien:1;
		unsigned rttincien:1;
		unsigned rttrst:1;
	} bits;
	uint32_t reg;
} rtt_mr;

union rtt_ar_t {
	struct {
		unsigned almv:32;
	} bits;
	uint32_t reg;
} rtt_ar;

union rtt_vr_t {
	struct {
		unsigned crtv:32;
	} bits;
	uint32_t reg;
} rtt_vr;

union rtt_sr_t {
	struct {
		unsigned alms:1;
		unsigned rttinc:1;
	} bits;
	uint32_t reg;
} rtt_sr;




