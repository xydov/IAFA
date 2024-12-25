/**
	Fichiers de définition des structures bit-fields du TC 
	Utiles pour l'interpreteur DWARF-2 intégré à GDB

	Fichiers de définition des registres timer (partiel)
**/

#include <stdint.h>

/* TC Block Mode Register */
union tc_bcr_t {
	struct {
		unsigned sync:1;
	} bits;
	uint32_t reg;
} tc_bcr;


union tc_bmr_t {
	struct {
		unsigned tc0xc0s:2;
		unsigned tc1xc1s:2;
		unsigned tc2xc2s:2;
	} bits;
	uint32_t reg;
} tc_bmr;

union tc_ccr_t {
	struct {
		unsigned clken:1;
		unsigned clkdis:1;
		unsigned swtrg:1;
	} bits;
	uint32_t reg;
} tc_ccr;

union tc_cmr_t {
	/* Capture Mode */
	struct 	{
		unsigned tcclks:3;
		unsigned clki:1;
		unsigned burst:2;
		unsigned ldbstop:1;
		unsigned ldbdis:1;
		unsigned etrgedg:2;
		unsigned abetrg:1;
		unsigned :2;
		unsigned cpctrg:1;
		unsigned wave:1;
		unsigned ldra:2;
		unsigned ldrb:2;
	} capbits;

	/* Waveform Mode */
	struct {
		unsigned tcclks:3;
		unsigned clki:1;
		unsigned burst:2;
		unsigned cpcstop:1;
		unsigned cpcdis:1;
		unsigned eevtedg:2;
		unsigned eevt:2;
		unsigned enetrg:1;
		unsigned wavsel:2;
		unsigned wave:1;
		unsigned acpa:2;
		unsigned acpd:2;
		unsigned aeevt:2;
		unsigned aswtrg:2;
		unsigned bcpb:2;
		unsigned bcpc:2;
		unsigned beevt:2;
		unsigned bswtrg:2;		
	} wavbits;
	uint32_t reg;
} tc_cmr;

/* TC RA/RB/RC register format */
union tc_rx_t {
	struct {
		unsigned rv:16;
	} bits;
	uint32_t reg;
} tc_rx;

/* Ces registres ont tous la même structure */
typedef union tc_rx tc_cv; 
typedef union tc_rx tc_ra; 
typedef union tc_rx tc_rb; 
typedef union tc_rx tc_rc; 

/* TC Status Register */
union tc_sr_t {
    struct {
        unsigned covfs:1;
        unsigned lovrs:1;
        unsigned cpas:1;
        unsigned cpbs:1;
        unsigned cpcs:1;
        unsigned ldras:1;
        unsigned ldrbs:1;
        unsigned etrgs:1;
        unsigned :8; 		// Reserved
        unsigned clksta:1;
        unsigned mtioa:1;
        unsigned mtiob:1;
    } bits;
    uint32_t reg;
} tc_sr;
