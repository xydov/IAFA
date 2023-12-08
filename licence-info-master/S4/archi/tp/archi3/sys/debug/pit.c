#include <stdint.h>

union pit_mr_t {
	struct {
		unsigned piv:20;
		unsigned :4;
		unsigned piten:1;
		unsigned pitien:1;
	} bits;
	uint32_t reg;
} pit_mr;

union pit_sr_t {
	struct {
		unsigned pits:1;
	} bits;
	uint32_t reg;
} pit_sr;

union pit_pivr_t {
	struct {
		unsigned cpiv:20;
		unsigned picnt:12;
	} bits;
	uint32_t reg;
} pit_pivr;

typedef union pit_pivr_t pit_piir;

