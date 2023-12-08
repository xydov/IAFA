#include <stdint.h>

union wdt_cr_t {
	struct {
		unsigned wdrstt:1;
		unsigned :23;
		unsigned key:8;
	} bits;
	uint32_t reg;
} wdt_cr;

union wdt_mr_t {
	struct {
		unsigned wdv:12;
		unsigned wdfien:1;
		unsigned wdrsten:1;
		unsigned wdrproc:1;
		unsigned wddis:1;
		unsigned wdd:12;
		unsigned wddbghlt:1;
		unsigned wdidlehlt:1;
	} bits;
	uint32_t reg;
} wdt_mr;

union wdt_sr_t {
	struct {
		unsigned wdunf:1;
		unsigned wderr:1;
	} bits;
	uint32_t reg;
} wdt_sr;

