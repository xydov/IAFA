
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
// reads the register reg to the variable var
#define READ_REGISTER(var,reg) __asm volatile("mov %[result], " TOSTRING(reg) "\n\t" : [result] "=r" (var))

#include <stdio.h>
#include <sys/usart/usart.h>


void lowlevelinit(void);
void print_trace(void);
void dataAbortHandler(void) __attribute__ ((naked));


// Ensemble de routines, handlers nécessaires au bon fonctionnement des programmes

// Routine de trace/debug
// Affiche le contenu des registres

// Affiche une trace détaillée sur la console
void print_trace(void) {
	int lr, pc, fp; 

	READ_REGISTER(lr, lr);
	READ_REGISTER(pc, pc);
	READ_REGISTER(fp, fp);
	//printf("TRACE [lr=%8x, pc=%8x, fp=%8x]\n",lr,pc,fp);
}

// Fonction appelée en cas de data abort
void dataAbortHandler(void) {
	register unsigned int lnk_ptr;

	__asm__ __volatile__ (
	"sub lr, lr, #8\n"
	"mov %0, lr" : "=r" (lnk_ptr) 
	);
	while(1);
}

// Fonction fourre tout qui initialise pas mal de trucs utiles.
void lowlevelinit(void) {
	// Joystick / AIC / PIO Initialisaiton goes here
}