/**
	Fichiers de définition des structures bit-fields du SPI 
	Utiles pour l'interpreteur DWARF-2 intégré à GDB

	Fichiers de définition des registres timer (partiel)
**/

#include <stdint.h>

/* TC Block Mode Register */
union spi_cr_t {
	struct {
		unsigned spien:1;
		unsigned spidis:1;
		unsigned :5;
		unsigned swrst:1;
		unsigned :16;
		unsigned lastxfer:1;
	} bits;
	uint32_t reg;
} spi_cr;

union spi_mr_t {
	struct 
	{
		unsigned mstr:1;
		unsigned ps:1;
		unsigned pcsdec:1;
		unsigned :1;
		unsigned modfis:1;
		unsigned :2;
		unsigned llb:1;
		unsigned :8;
		unsigned pcs:4;
		unsigned :4;
		unsigned dlybcs:8;
	} bits;
	uint32_t reg;
} spi_mr;

union spi_rdr_t {
	struct {
		unsigned rd:16;
		unsigned pcs:4;
	} bits;
	uint32_t reg;
} spi_rdr;

union spi_tdr_t {
	struct {
		unsigned td:16;
		unsigned pcs:4;
	} bits;
	uint32_t reg;
} spi_tdr;

union spi_sr_t {
	struct {
		unsigned rdrf:1;
		unsigned tdre:1;
		unsigned modf:1;
		unsigned ovres:1;
		unsigned endrx:1;
		unsigned enxtx:1;
		unsigned rxbuff:1;
		unsigned txbufe:1;
		unsigned nssr:1;
		unsigned txempty:1;
		unsigned :6;
		unsigned spiens:1;
	} bits;
	uint32_t reg;
} spi_sr;

union spi_ier_t {
	struct {
		unsigned rdrf:1;
		unsigned tdre:1;
		unsigned modf:1;
		unsigned ovres:1;
		unsigned endrx:1;
		unsigned endtx:1;
		unsigned rxbuff:1;
		unsigned txbufe:1;
		unsigned nssr:1;
		unsigned txempty:1;
	} bits;
	uint32_t reg;
} spi_ier;


union spi_idr_t {
	struct {
		unsigned rdrf:1;
		unsigned tdre:1;
		unsigned modf:1;
		unsigned ovres:1;
		unsigned endrx:1;
		unsigned endtx:1;
		unsigned rxbuff:1;
		unsigned txbufe:1;
		unsigned nssr:1;
		unsigned txempty:1;
	} bits;
	uint32_t reg;
} spi_idr;

union spi_imr_t {
	struct {
		unsigned rdrf:1;
		unsigned tdre:1;
		unsigned modf:1;
		unsigned ovres:1;
		unsigned endrx:1;
		unsigned endtx:1;
		unsigned rxbuff:1;
		unsigned txbufe:1;
		unsigned nssr:1;
		unsigned txempty:1;
	} bits;
	uint32_t reg;
} spi_imr;

union spi_csr_t {
	struct {
		unsigned cpol:1;
		unsigned ncpha:1;
		unsigned :1;
		unsigned csaat:1;
		unsigned bits:4;
		unsigned scbr:8;
		unsigned dlybs:8;
		unsigned dlybct:8;
	} bits;
	uint32_t reg;
} spi_csr;
