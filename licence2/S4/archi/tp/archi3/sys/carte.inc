@ ==============================================================================
@
@ Définitions de constantes pour la carte Olimex SAM7-EX256 
@
@ - includes additional leds
@ ==============================================================================

@ ===============================================================
@ Horloge du processeur
@ ===============================================================
.equ	MCK,		48000000	@ frequence d'horloge du processeur

@ ===============================================================
@ Boutons et leds
@ ===============================================================
.equ	SW1,		1<<24
.equ 	SW2,		1<<25
.equ	LED1,		0x40000000
.equ	LED2,		0x20000000
.equ	LED3,		0x10000000
.equ	LED4,		0x08000000


@ ===============================================================
@ Adresses de base des circuits de la carte
@ ===============================================================

@ Adresse de base du timer 0
.equ	TC0_BASE,	0xFFFA0000

@ Adresse de base des USART
.equ	USART0_BASE,	0xFFFC0000      @ Adresse de base USART 0  
.equ	USART1_BASE,	0xFFFC4000      @ Adresse de base USART 1  

@ Adresse de base du contrôleur d'interruptions
.equ	AIC_BASE,	0xFFFFF000

@ Adresse de base des PIO
.equ	PIOA_BASE,	0xFFFFF400      @ Adresse de base PIOA
.equ	PIOB_BASE,	0xFFFFF600	@ Adresse de base PIOB

@ Adresse de base
.equ	PMC_BASE,	0xFFFFFC00

@ Reset Controller (RSTC) base address
.equ	RSTC_BASE,	0xFFFFFD00

@ Real Time timer (RTT) base address
.equ	RTT_BASE,	0xFFFFFD20

@ Periodic Interval Timer (PIT) base address
.equ	PIT_BASE,	0xFFFFFD30

@ Watchdog Timer (WDT) base address
.equ	WDT_BASE,	0xFFFFFD40

@ Voltage Regulator Mode Controller (VREG) base address
.equ	VREG_BASE,	0xFFFFFD60

@ Memory Controller (MC) base address
.equ	MC_BASE,	0xFFFFFF00





@ ===============================================================
@ Offsets des adresses des  registres   des circuits 
@ (a ajouter a l'adresse de base)
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	PIO_PER,		0x00	@ PIO Enable Register 
.equ	PIO_PDR,		0x04	@ PIO Disable Register 
.equ	PIO_PSR,		0x08	@ PIO Status Register 
.equ	PIO_RES0,		0x0C	@ Reserved 0 
.equ	PIO_OER,		0x10	@ Output Enable Register 
.equ	PIO_ODR,		0x14	@ Output Disable Register 
.equ	PIO_OSR,		0x18	@ Output Status Register 
.equ	PIO_RES1,		0x1C	@ Reserved 1 
.equ	PIO_IFER,		0x20	@ Input Filter Enable Register 
.equ	PIO_IFDR,		0x24	@ Input Filter Disable Register 
.equ	PIO_IFSR,		0x28	@ Input Filter Status Register 
.equ	PIO_RES2,		0x2C	@ Reserved 2 
.equ	PIO_SODR,		0x30	@ Set Output Data Register 
.equ	PIO_CODR,		0x34	@ Clear Output Data Register 
.equ	PIO_ODSR,		0x38	@ Output Data Status Register 
.equ	PIO_PDSR,		0x3C	@ Pin Data Status Register 
.equ	PIO_IER,		0x40	@ Interrupt Enable Register 
.equ    PIO_IDR,		0x44	@ Interrupt Disable Register 
.equ    PIO_IMR,		0x48	@ Interrupt Mask Register 
.equ    PIO_ISR,		0x4C	@ Interrupt Status Register 
.equ    PIO_MDER,		0x50	@ Interrupt Enable Register 
.equ    PIO_MDDR,		0x54	@ Interrupt Disable Register 
.equ    PIO_MDSR,		0x58	@ Interrupt Status Register 
.equ	PIO_RES1,		0x5C	@ Reserved
.equ    PIO_PUDR,		0x60	@ Pull-up Disable Register 
.equ    PIO_PUER,		0x64	@ Pull-up Enable Register 
.equ	PIO_PUSR,		0x68	@ Pull-up Status Register
.equ    PIO_RES2,		0x6C	@ Reserved
.equ    PIO_ASR,		0x70	@ Preipheral A Select Register 
.equ    PIO_BSR,		0x74	@ Preipheral B Select Register 
.equ	PIO_ABSR,		0x78	@ AB Status Register
.equ    PIO_RES3,		0x7C	@ Reserved 
.equ	PIO_OWER,		0xA0	@ Output Write Enable Register
.equ    PIO_OWDR,		0xA4	@ Output Write Disable Register 
.equ    PIO_OWSR,		0xA8	@ Output Write Status Register 
.equ	PIO_RES4,		0xAC	@ Reserved

@ ===============================================================
@ AIC
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	AIC_SMR,	0x000		@ Base Source Mode Registers
.equ	AIC_SVR,	0x080  		@ Base Source Vector Registers

@ source 12 = timer 0
.equ	AIC_SMR12,	AIC_SMR+12*4	
.equ	AIC_SVR12,	AIC_SVR+12*4     

@ Source 3 = PIOB�
.equ	AIC_SMR3,	AIC_SMR+3*4	
.equ	AIC_SVR3,	AIC_SVR+3*4 

.equ	AIC_IVR,	0x100  		@ IRQ Vector Register 
.equ	AIC_FVR,	0x104  		@ FIQ Vector Register 
.equ	AIC_ISR,	0x108  		@ Interrupt Status Register 
.equ	AIC_IPR,	0x10C  		@ Interrupt Pending Register 
.equ	AIC_IMR,	0x110  		@ Interrupt Mask Register 
.equ	AIC_CISR,	0x114 		@ Core Interrupt Status Register 
.equ	AIC_RES1,	0x118 		@ Reserved 0 
.equ	AIC_RES2,	0x11C 		@ Reserved 1 
.equ	AIC_IECR,	0x120 		@ Interrupt Enable Command Register 
.equ	AIC_IDCR,	0x124 		@ Interrupt Disable Command Register 
.equ	AIC_ICCR,	0x128 		@ Interrupt Clear Command Register 
.equ	AIC_ISCR,	0x12C 		@ Interrupt Set Command Register 
.equ	AIC_EOICR,	0x130		@ End of Interrupt Command Register 
.equ	AIC_SPU,	0x134  		@ Spurious Vector Register 
.equ    AIC_DCR,         0x138
.equ	AIC_FFER,	 0x140
.equ	AIC_FFDR,	 0x144
.equ	AIC_FFSR,	 0x148

@ ===============================================================
@ Timer Counter 
@ ===============================================================
@ Offsets registres
@ -----------------
.equ TC_CCR,	0x00 	@ Channel Control Register
.equ TC_CMR,	0x04 	@ Channel Mode Register (Capture Mode / Waveform Mode)
.equ TC_CV,	0x10 	@ Counter Value
.equ TC_RA,	0x14 	@ Register A
.equ TC_RB,	0x18 	@ Register B
.equ TC_RC,	0x1C 	@ Register C
.equ TC_SR,	0x20 	@ Status Register
.equ TC_IER,	0x24 	@ Interrupt Enable Register
.equ TC_IDR,	0x28 	@ Interrupt Disable Register
.equ TC_IMR,	0x2C 	@ Interrupt Mask Register
.equ TC_BCR,	0xC0	@ Block Control Register 
.equ TC_BMR,	0xC4	@ Block Mode Register 


@ ===============================================================
@ USART
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	US_CR,		0x00	@ Control Register 
.equ	US_MR,          0x04	@ Mode Register 
.equ	US_IER,         0x08	@ Interrupt Enable Register 
.equ	US_IDR,         0x0C	@ Interrupt Disable Register 
.equ	US_IMR,         0x10	@ Interrupt Mask Register 
.equ	US_CSR,         0x14	@ Channel Status Register 
.equ	US_RHR,         0x18	@ Receive Holding Register 
.equ	US_THR,         0x1C	@ Transmit Holding Register 
.equ	US_BRGR,        0x20	@ Baud Rate Generator Register 
.equ    US_RTOR,        0x24	@ Receiver Timeout Register 
.equ    US_TTGR,        0x28	@ Transmitter Time-guard Register 
.equ    US_RES,         0x2C	@ Reserved 
.equ    US_RPR,         0x30	@ Receiver Pointer Register 
.equ    US_RCR,         0x34	@ Receiver Counter Register 
.equ    US_TPR,         0x38	@ Transmitter Pointer Register 
.equ    US_TCR,         0x3C	@ Transmitter Counter Register 
@ Bits pour US_CR : registre de controle
@ -----------------
.equ RXD0,1
.equ TXD0,2
.equ US_RSTRX,      0x0004      @ Reset Receiver 
.equ US_RSTTX,      0x0008      @ Reset Transmitter 
.equ US_RXEN ,      0x0010      @ Receiver Enable 
.equ US_RXDIS,      0x0020      @ Receiver Disable 
.equ US_TXEN ,      0x0040      @ Transmitter Enable 
.equ US_TXDIS,      0x0080      @ Transmitter Disable 
.equ US_RSTSTA,     0x0100      @ Reset Status Bits 
.equ US_STTBRK,     0x0200      @ Start Break 
.equ US_STPBRK,     0x0400      @ Stop Break 
.equ US_STTTO,      0x0800      @ Start Time-out 
.equ US_SENDA,      0x1000      @ Send Address 

@ Bits pour US_MR : registre de mode
@ -----------------
.equ US_CLKS,       0x0030      @ Clock Selection 
.equ US_CLKS_MCK,    0x00        @ Master Clock 
.equ US_CLKS_MCK8,   0x10        @ Master Clock divided by 8 
.equ US_CLKS_SCK,    0x20        @ External Clock 
.equ US_CLKS_SLCK,   0x30        @ Slow Clock 

.equ US_CHRL,        0x00C0      @ Byte Length 
.equ US_CHRL_5,      0x00        @ 5 bits 
.equ US_CHRL_6,      0x40        @ 6 bits 
.equ US_CHRL_7,      0x80        @ 7 bits 
.equ US_CHRL_8,      0xC0        @ 8 bits 
.equ US_ASYNC, 0

.equ US_SYNC,        0x0100      @ Synchronous Mode Enable 

.equ US_PAR,         0x0E00      @ Parity Mode 
.equ US_PAR_EVEN,    0x000        @ Even Parity 
.equ US_PAR_ODD,     0x200        @ Odd Parity 
.equ US_PAR_SPACE,   0x400        @ Space Parity to 0 
.equ US_PAR_MARK,    0x600        @ Marked Parity to 1 
.equ US_PAR_NONE,     0x800        @ No Parity 

.equ US_NBSTOP,      0x3000      @ Stop Bit Number 
.equ US_NBSTOP_1,    0x0000      @ 1 Stop Bit 
.equ US_NBSTOP_1_5,  0x1000      @ 1.5 Stop Bits 
.equ US_NBSTOP_2,    0x2000      @ Stop Bits 

.equ US_CHMODE,	                  0xC000  @ Channel Mode 
.equ US_CHMODE_NORMAL,            0x0000  @ Normal Mode 
.equ US_CHMODE_AUTOMATIC_ECHO,    0x4000  @ Automatic Echo 
.equ US_CHMODE_LOCAL_LOOPBACK,    0x8000  @ Local Loopback 
.equ US_CHMODE_REMOTE_LOOPBACK,   0xC000  @ Remote Loopback 
.equ US_MODE9,       0x20000     @ 9 Bit Mode 
.equ US_CLKO ,       0x40000     @ Baud Rate Output Enable 

@  Bits pour US_IER, US_IDR, US_IMR, US_CSR: registres d'etat et d'interruption
@ -----------------
.equ US_RXRDY,       0x001       @ Receiver Ready 
.equ US_TXRDY,       0x002       @ Transmitter Ready 
.equ US_RXBRK,       0x004       @ Receiver Break 
.equ US_ENDRX,       0x008       @ End of Receiver PDC Transfer 
.equ US_ENDTX,       0x010       @ End of Transmitter PDC Transfer 
.equ US_OVRE ,       0x020       @ Overrun Error 
.equ US_FRAME,       0x040       @ Framing Error 
.equ US_PARE ,       0x080       @ Parity Error 
.equ US_TIMEOUT,     0x100       @ Receiver Timeout 
.equ US_TXEMPTY,     0x200       @ Transmitter Empty 


@ ===============================================================
@ PWM
@ ===============================================================
@ Offsets registres
@ -----------------
.equ PWM_MR,         0x000	 @ PWM Mode Register
.equ PWM_ENA,        0x004	 @ PWM Enable Register
.equ PWM_DIS,        0x008	 @ PWM Disabla Register
.equ PWM_SR,         0x00C	 @ PWM Status Register
.equ PWM_IER,        0x010	 @ PWM Interrupt Enable Register
.equ PWM_IDR,        0x014	 @ PWM Interrupt Disable Register
.equ PWM_IMR,        0x018	 @ PWM Interrupt Mask Register
.equ PWM_ISR,        0x01C	 @ PWM Interrupt Status Register
.equ Reserved,       0x04C	 @ Reserved
.equ PWM_CMR,        0x200	 @ PWM Channel Mode Register
.equ PWM_CDTY,       0x204	 @ PWM Channel Duty Cycle Register
.equ PWM_CPRD,       0x208	 @ PWM Channel Period Register
.equ PWM_CCNT,       0x20C	 @ PWM Channel Counter Register
.equ PWM_CUPD,       0x210	 @ PWM Channel Update Register

@ ===============================================================
@ PMC registers
@ ===============================================================
@ Offsets registres
@ -----------------
.equ PMC_SCER,		0x00 	@ (PMC_SCER System Clock Enable Register
.equ PMC_SCDR,		0x04	@ (PMC_SCDR System Clock Disable Register
.equ PMC_SCSR,		0x08	@ (PMC_SCSR System Clock Status Register
.equ PMC_PCER,		0x10	@ (PMC_PCER Peripheral Clock Enable Register
.equ PMC_PCDR,		0x14	@ (PMC_PCDR Peripheral Clock Disable Register
.equ PMC_PCSR,		0x18 	@ (PMC_PCSR Peripheral Clock Status Register
.equ CKGR_MOR,		0x20 	@ main oscillator register
.equ CKGR_MCFR,		0x24 	@ Main clock frequency register
.equ CKGR_PLLR,		0x2C 	@ PLL register
.equ PMC_MCKR,		0x30 	@ (PMC_MCKR Master Clock Register)
.equ PMC_PCK,		0x40 	@ (PMC_PCKR Programmable Clock Register)
.equ PMC_IER,		0x60 	@ (PMC_IER Interrupt Enable Register)
.equ PMC_IDR,		0x64 	@ (PMC_IDR Interrupt Disable Register)
.equ PMC_SR,		0x68 	@ (PMC_SR Status Register)
.equ PMC_IMR,		0x6C 	@ (PMC_IMR Interrupt Mask Register)

@ Bits utiles
@ -----------------
.equ	MOSCS,				0x01
.equ	LOCK,				0x04
.equ	MCKRDY,				0x08
.equ	PID_PIOA,			0x04
.equ	PID_PIOB,			0x08
.equ	PID_USART0,			0x40
.equ	PID_USART1,			0x80
.equ	PID_PWMC,			0x400
.equ	PID_TC0,			0x1000
.equ	PID_TC1,			0x2000
.equ	PID_TC2,			0x4000

@ ===============================================================
@ Real Time Timer Controller Interface
@ ===============================================================
@ Offsets registres
@ -----------------
.equ RTTC_RTMR,	    0x00 	@ (RTTC_RTMR Real-time Mode Register
.equ RTTC_RTAR,	    0x04 	@ (RTTC_RTAR Real-time Alarm Register
.equ RTTC_RTVR,	    0x08 	@ (RTTC_RTVR Real-time Value Register
.equ RTTC_RTSR,	    0x0C 	@ (RTTC_RTSR Real-time Status Register

@ ===============================================================
@ Periodic Interval Timer Controller Interface
@ ===============================================================
@ Offsets registres
@ -----------------
.equ PITC_PIMR,	0x00 	@ (PITC_PIMR Period Interval Mode Register
.equ PITC_PISR,	0x04 	@ (PITC_PISR Period Interval Status Register
.equ PITC_PIVR,	0x08 	@ (PITC_PIVR Period Interval Value Register
.equ PITC_PIIR,	0x0C 	@ (PITC_PIIR Period Interval Image Register


@ ===============================================================
@ Serial Parallel Interface
@ ===============================================================
@ Offsets registres
@ -----------------
.equ SPI_CR,  0x00 	@ (SPI_CR Control Register
.equ SPI_MR,  0x04 	@ (SPI_MR Mode Register
.equ SPI_RDR, 0x08 	@ (SPI_RDR Receive Data Register
.equ SPI_TDR, 0x0C 	@ (SPI_TDR Transmit Data Register
.equ SPI_SR,  0x10 	@ (SPI_SR Status Register
.equ SPI_IER, 0x14 	@ (SPI_IER Interrupt Enable Register
.equ SPI_IDR, 0x18 	@ (SPI_IDR Interrupt Disable Register
.equ SPI_IMR, 0x1C 	@ (SPI_IMR Interrupt Mask Register
.equ SPI_CSR, 0x30 	@ (SPI_CSR Chip Select Register



@ ===============================================================
@ Two-wire Interface
@ ===============================================================
@ Offsets registres
@ -----------------
.equ TWI_CR,   0x00 	@ (TWI_CR Control Register
.equ TWI_MMR,  0x04 	@ (TWI_MMR Master Mode Register
.equ TWI_IADR, 0x0C 	@ (TWI_IADR Internal Address Register
.equ TWI_CWGR, 0x10 	@ (TWI_CWGR Clock Waveform Generator Register
.equ TWI_SR,   0x20 	@ (TWI_SR Status Register
.equ TWI_IER,  0x24 	@ (TWI_IER Interrupt Enable Register
.equ TWI_IDR,  0x28 	@ (TWI_IDR Interrupt Disable Register
.equ TWI_IMR,  0x2C 	@ (TWI_IMR Interrupt Mask Register
.equ TWI_RHR,  0x30 	@ (TWI_RHR Receive Holding Register
.equ TWI_THR,  0x34 	@ (TWI_THR Transmit Holding Register


@ ===============================================================
@ PWMC Channel Interface
@ ===============================================================
@ Offsets registres
@ -----------------
.equ PWMC_CMR,        0x00 	@ (PWMC_CMR Channel Mode Register
.equ PWMC_CDTYR,      0x04 	@ (PWMC_CDTYR Channel Duty Cycle Register
.equ PWMC_CPRDR,      0x08 	@ (PWMC_CPRDR Channel Period Register
.equ PWMC_CCNTR,      0x0C 	@ (PWMC_CCNTR Channel Counter Register
.equ PWMC_CUPDR,      0x10 	@ (PWMC_CUPDR Channel Update Register
.equ Reserved,        0x14 	@ (Reserved Reserved



@ ===============================================================
@ Pulse Width Modulation Controller Interface
@ ===============================================================
@ Offsets registres
@ -----------------
.equ PWMC_MR,	0x00 	@ (PWMC_MR PWMC Mode Register
.equ PWMC_ENA,	0x04 	@ (PWMC_ENA PWMC Enable Register
.equ PWMC_DIS,	0x08 	@ (PWMC_DIS PWMC Disable Register
.equ PWMC_SR,	0x0C 	@ (PWMC_SR PWMC Status Register
.equ PWMC_IER,	0x10 	@ (PWMC_IER PWMC Interrupt Enable Register
.equ PWMC_IDR,	0x14 	@ (PWMC_IDR PWMC Interrupt Disable Register
.equ PWMC_IMR,	0x18 	@ (PWMC_IMR PWMC Interrupt Mask Register
.equ PWMC_ISR,	0x1C 	@ (PWMC_ISR PWMC Interrupt Status Register
.equ PWMC_VR,	0xFC 	@ (PWMC_VR PWMC Version Register


@ ===============================================================
@ Ethernet MAC 10/100
@ ===============================================================
@ Offsets registres
@ -----------------
.equ EMAC_NCR,	  0x00 @ (EMAC_NCR Network Control Register
.equ EMAC_NCFGR,  0x04 @ (EMAC_NCFGR Network Configuration Register
.equ EMAC_NSR,	  0x08 @ (EMAC_NSR Network Status Register
.equ EMAC_TSR,	  0x14 @ (EMAC_TSR Transmit Status Register
.equ EMAC_RBQP,	  0x18 @ (EMAC_RBQP Receive Buffer Queue Pointer
.equ EMAC_TBQP,	  0x1C @ (EMAC_TBQP Transmit Buffer Queue Pointer
.equ EMAC_RSR,	  0x20 @ (EMAC_RSR Receive Status Register
.equ EMAC_ISR,	  0x24 @ (EMAC_ISR Interrupt Status Register
.equ EMAC_IER,	  0x28 @ (EMAC_IER Interrupt Enable Register
.equ EMAC_IDR,	  0x2C @ (EMAC_IDR Interrupt Disable Register
.equ EMAC_IMR,	  0x30 @ (EMAC_IMR Interrupt Mask Register
.equ EMAC_MAN,	  0x34 @ (EMAC_MAN PHY Maintenance Register
.equ EMAC_PTR,	  0x38 @ (EMAC_PTR Pause Time Register
.equ EMAC_PFR,	  0x3C @ (EMAC_PFR Pause Frames received Register
.equ EMAC_FTO,	  0x40 @ (EMAC_FTO Frames Transmitted OK Register
.equ EMAC_SCF,	  0x44 @ (EMAC_SCF Single Collision Frame Register
.equ EMAC_MCF,	  0x48 @ (EMAC_MCF Multiple Collision Frame Register
.equ EMAC_FRO,	  0x4C @ (EMAC_FRO Frames Received OK Register
.equ EMAC_FCSE,	  0x50 @ (EMAC_FCSE Frame Check Sequence Error Register
.equ EMAC_ALE,	  0x54 @ (EMAC_ALE Alignment Error Register
.equ EMAC_DTF,	  0x58 @ (EMAC_DTF Deferred Transmission Frame Register
.equ EMAC_LCOL,	  0x5C @ (EMAC_LCOL Late Collision Register
.equ EMAC_ECOL,	  0x60 @ (EMAC_ECOL Excessive Collision Register
.equ EMAC_TUND,	  0x64 @ (EMAC_TUND Transmit Underrun Error Register
.equ EMAC_CSE,	  0x68 @ (EMAC_CSE Carrier Sense Error Register
.equ EMAC_RRE,	  0x6C @ (EMAC_RRE Receive Ressource Error Register
.equ EMAC_ROV,	  0x70 @ (EMAC_ROV Receive Overrun Errors Register
.equ EMAC_RSE,	  0x74 @ (EMAC_RSE Receive Symbol Errors Register
.equ EMAC_ELE,	  0x78 @ (EMAC_ELE Excessive Length Errors Register
.equ EMAC_RJA,	  0x7C @ (EMAC_RJA Receive Jabbers Register
.equ EMAC_USF,	  0x80 @ (EMAC_USF Undersize Frames Register
.equ EMAC_STE,	  0x84 @ (EMAC_STE SQE Test Error Register
.equ EMAC_RLE,	  0x88 @ (EMAC_RLE Receive Length Field Mismatch Register
.equ EMAC_TPF,	  0x8C @ (EMAC_TPF Transmitted Pause Frames Register
.equ EMAC_HRB,	  0x90 @ (EMAC_HRB Hash Address Bottom[31:0]
.equ EMAC_HRT,	  0x94 @ (EMAC_HRT Hash Address Top[63:32]
.equ EMAC_SA1L,	  0x98 @ (EMAC_SA1L Specific Address 1 Bottom,	   First 4 bytes
.equ EMAC_SA1H,	  0x9C @ (EMAC_SA1H Specific Address 1 Top,	   Last 2 bytes
.equ EMAC_SA2L,	  0xA0 @ (EMAC_SA2L Specific Address 2 Bottom, First 4 bytes
.equ EMAC_SA2H,	  0xA4 @ (EMAC_SA2H Specific Address 2 Top, Last 2 bytes
.equ EMAC_SA3L,	  0xA8 @ (EMAC_SA3L Specific Address 3 Bottom, First 4 bytes
.equ EMAC_SA3H,	  0xAC @ (EMAC_SA3H Specific Address 3 Top, Last 2 bytes
.equ EMAC_SA4L,	  0xB0 @ (EMAC_SA4L Specific Address 4 Bottom, First 4 bytes
.equ EMAC_SA4H,	  0xB4 @ (EMAC_SA4H Specific Address 4 Top, Last 2 bytes
.equ EMAC_TID,	  0xB8 @ (EMAC_TID Type ID Checking Register
.equ EMAC_TPQ,	  0xBC @ (EMAC_TPQ Transmit Pause Quantum Register
.equ EMAC_USRIO      ,0xC0 @ (EMAC_USRIO USER Input/Output Register
.equ EMAC_WOL,	  0xC4 @ (EMAC_WOL Wake On LAN Register
.equ EMAC_REV,	  0xFC @ (EMAC_REV Revision Register



@ ===============================================================
@ Analog to Digital Convertor
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	ADC_CR,		0x00 @ (ADC_CR ADC Control Register
.equ	ADC_MR,		0x04 @ (ADC_MR ADC Mode Register
.equ	ADC_CHER,	0x10 @ (ADC_CHER ADC Channel Enable Register
.equ	ADC_CHDR,	0x14 @ (ADC_CHDR ADC Channel Disable Register
.equ	ADC_CHSR,	0x18 @ (ADC_CHSR ADC Channel Status Register
.equ	ADC_SR,		0x1C @ (ADC_SR ADC Status Register
.equ	ADC_LCDR,	  0x20 @ (ADC_LCDR ADC Last Converted Data Register
.equ	ADC_IER,	  0x24 @ (ADC_IER ADC Interrupt Enable Register
.equ	ADC_IDR,	  0x28 @ (ADC_IDR ADC Interrupt Disable Register
.equ	ADC_IMR,	  0x2C @ (ADC_IMR ADC Interrupt Mask Register
.equ	ADC_CDR0,	  0x30 @ (ADC_CDR0 ADC Channel Data Register 0
.equ	ADC_CDR1,	  0x34 @ (ADC_CDR1 ADC Channel Data Register 1
.equ	ADC_CDR2,	  0x38 @ (ADC_CDR2 ADC Channel Data Register 2
.equ	ADC_CDR3,	  0x3C @ (ADC_CDR3 ADC Channel Data Register 3
.equ	ADC_CDR4,	  0x40 @ (ADC_CDR4 ADC Channel Data Register 4
.equ	ADC_CDR5,	  0x44 @ (ADC_CDR5 ADC Channel Data Register 5
.equ	ADC_CDR6,	  0x48 @ (ADC_CDR6 ADC Channel Data Register 6
.equ	ADC_CDR7,	  0x4C @ (ADC_CDR7 ADC Channel Data Register 7


@ ===============================================================
@ Registres du contrôleur mémoire
@ Note : il n'y a qu'un seul EFC0 sur les sam7-ex256
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	MC_RCR,		0x00	@ Remap Control Register
.equ	MC_ASR,		0x04	@ Abort Status Register
.equ	MC_AASR,	0x08	@ Abort Address Status Register
.equ	MC_FMR,		0x60	@ Flash Mode Register
.equ	MC_FCR,		0x64	@ Flash Command Register
.equ	MC_FSR,		0x68	@ Flash Status Register


@ ===============================================================
@ Registres du contrôleur de reset
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	RSTC_CR,	0x00	@ Control Register
.equ	RSTC_SR,	0x04	@ Status Register
.equ	RSTC_MR,	0x08	@ Mode Register


@ ===============================================================
@ Registres du Watchdog
@ ===============================================================
@ Offsets registres
@ -----------------
.equ	WDT_CR,		0x00	@ Control Register
.equ	WDT_MR,		0x04	@ Mode Register
.equ	WDT_SR,		0x08	@ Status Register

@ Numéros de bits utiles
@ -----------------
.equ	WDDIS,		0x00008000
