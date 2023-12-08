    .include "sys/carte.inc"

    .equ ARM_MODE_USR, 0x10 /* Normal User Mode */
    .equ ARM_MODE_FIQ, 0x11 /* FIQ Processing Fast Interrupts Mode */
    .equ ARM_MODE_IRQ, 0x12 /* IRQ Processing Standard Interrupts Mode */
    .equ ARM_MODE_SVC, 0x13 /* Supervisor Processing Software Interrupts Mode */
    .equ ARM_MODE_ABT, 0x17 /* Abort Processing memory Faults Mode */
    .equ ARM_MODE_UND, 0x1B /* Undefined Processing Undefined Instructions Mode */
    .equ ARM_MODE_SYS, 0x1F /* System Running Priviledged Operating System Tasks Mode */
    .equ I_BIT, 0x80 /* when I bit is set, IRQ is disabled (program status registers) */
    .equ F_BIT, 0x40 /* when F bit is set, FIQ is disabled (program status registers) */

    .arm
    .text
    .global irqHandler
/* =======================================================================  */
/* Function: AT91F_Irq_Handler                                              */
/*                                                                          */
/* This IRQ_Handler supports nested interrupts (an IRQ interrupt can itself */
/* be interrupted).                                                         */
/*                                                                          */
/* This handler re-enables interrupts and switches to "Supervisor" mode to  */
/* prevent any corruption to the link and IP registers.                     */
/*                                                                          */
/* The Interrupt Vector Register (AIC_IVR) is read to determine the address */
/* of the required interrupt service routine. The ISR routine can be a      */
/* standard C function since this handler minds all the save/restore        */
/* protocols.                                                               */
/*                                                                          */
/*                                                                          */
/* Programmers:                                                             */
/*--------------------------------------------------------------------------*/
/* ATMEL Microcontroller Software Support - ROUSSET -                       */
/*--------------------------------------------------------------------------*/
/* DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS   */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED        */
/* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND      */
/* NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR   */
/* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR                 */
/* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT        */
/* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       */
/* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE     */
/* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,        */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                       */
/* File source : Cstartup.s79                                               */
/* Object : Generic CStartup to AT91SAM7S256                                */
/* 1.0 09/May/06 JPP : Creation                                             */
/*                                                                          */
/*                                                                          */
/* Note: taken from Atmel web site (www.at91.com)                           */
/* Keil example project: AT91SAM7S-Interrupt_SAM7X                          */
/* ======================================================================== */
irqHandler:
    /* Manage Exception Entry */

    /* Adjust and save LR_irq in IRQ stack */
    sub     lr, lr, #4
    stmfd   sp!, {lr}

    /* Save r0 and SPSR (need to be saved for nested interrupt) */
    mrs     r14, SPSR
    stmfd   sp!, {r0, r14}

    /* Write in the IVR to support Protect Mode */
    /* No effect in Normal Mode */
    /* De-assert the NIRQ and clear the source in Protect Mode */
    ldr     r14, =AIC_BASE
    ldr     r0,  [r14, #AIC_IVR]
    str     r14, [r14, #AIC_IVR]

    /* Enable Interrupt and Switch in Supervisor Mode */
    msr     CPSR_c, #ARM_MODE_SVC

    /* Save scratch/used registers and LR in User Stack */
    stmfd   sp!, {r1-r3, r12, r14}

    /* Branch to the routine pointed by the AIC_IVR */
    mov     r14, pc
    bx      r0

    /* Manage Exception Exit */

    /* Restore scratch/used registers and LR from User Stack */
    ldmia   sp!, {r1-r3, r12, r14}

    /* Disable Interrupt and switch back in IRQ mode */
    msr     CPSR_c, #(I_BIT | ARM_MODE_IRQ)

    /* Mark the End of Interrupt on the AIC */
    ldr     r14, =AIC_BASE
    str     r14, [r14, #AIC_EOICR]

    /* Restore SPSR_irq and r0 from IRQ stack */
    ldmia   sp!, {r0, r14}
    msr     SPSR_cxsf, r14  @ ??????????????????

    /* Restore adjusted LR_irq from IRQ stack directly in the PC */
    ldmia   sp!, {pc}^
