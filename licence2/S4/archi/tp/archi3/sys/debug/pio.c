/**
	Fichiers de définition des structures bit-fields du TC 
	Utiles pour l'interpreteur DWARF-2 intégré à GDB

	Fichiers de définition des registres timer (partiel)
**/

/**

**/

#include <stdint.h>

union pio_pinreg_t {
	struct {
		unsigned p0:1;
		unsigned p1:1;
		unsigned p2:1;
		unsigned p3:1;
		unsigned p4:1;
		unsigned p5:1;
		unsigned p6:1;
		unsigned p7:1;
		unsigned p8:1;
		unsigned p9:1;
		unsigned p10:1;
		unsigned p11:1;
		unsigned p12:1;
		unsigned p13:1;
		unsigned p14:1;
		unsigned p15:1;
		unsigned p16:1;
		unsigned p17:1;
		unsigned p18:1;
		unsigned p19:1;
		unsigned p20:1;
		unsigned p21:1;
		unsigned p22:1;
		unsigned p23:1;
		unsigned p24:1;
		unsigned p25:1;
		unsigned p26:1;
		unsigned p27:1;
		unsigned p28:1;
		unsigned p29:1;
		unsigned p30:1;
		unsigned p31:1;
	} bits;
	uint32_t reg;
} pio_pinreg;

typedef union pio_pinreg_t pio_per;
typedef union pio_pinreg_t pio_pdr;
typedef union pio_pinreg_t pio_psr;
typedef union pio_pinreg_t pio_oer;
typedef union pio_pinreg_t pio_odr;
typedef union pio_pinreg_t pio_osr;
typedef union pio_pinreg_t pio_ifer;
typedef union pio_pinreg_t pio_ifdr;
typedef union pio_pinreg_t pio_ifsr;
typedef union pio_pinreg_t pio_sodr;
typedef union pio_pinreg_t pio_codr;
typedef union pio_pinreg_t pio_odsr;
typedef union pio_pinreg_t pio_pdsr;
typedef union pio_pinreg_t pio_ier;
typedef union pio_pinreg_t pio_idr;
typedef union pio_pinreg_t pio_imr;
typedef union pio_pinreg_t pio_isr;
typedef union pio_pinreg_t pio_mder;
typedef union pio_pinreg_t pio_mddr;
typedef union pio_pinreg_t pio_mdsr;
typedef union pio_pinreg_t pio_pudr;
typedef union pio_pinreg_t pio_puer;
typedef union pio_pinreg_t pio_pusr;
typedef union pio_pinreg_t pio_bsr;
typedef union pio_pinreg_t pio_absr;
typedef union pio_pinreg_t pio_ower;
typedef union pio_pinreg_t pio_owdr;
typedef union pio_pinreg_t pio_owsr;

