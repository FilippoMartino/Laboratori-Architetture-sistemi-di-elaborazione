#include <stdio.h>
#include <stdlib.h>
#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"
extern void c_led_setup(void);
/*
	Questo file permette la configurazione degli handler per gli interrupt causati
	dai pulsanti, o meglio dalla loro attivazione.
*/


/*
	Ognuna di queste funzioni specifica le operazioni da realizzare ogni qual volta il pulsante 0 (piuttosto che 1 o 2)
	venga premuto
	
	Alla fine di ogni funzione si pulisce l'interrupt, che altrimenti rimarrebbe a "sporcare" la IVT (interrupt vector table)
	specificando il registro EXTINT in bitwise AND con la maschera per selezionare a quale pin di input si stia specificando, 
	in questo caso 0, 1, o 2 in base al pulsante
*/

void EINT0_IRQHandler (void)	  
{

  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


/* 
	Al trigger del KEY1 si inizia la lettura del messaggio in c: 
	tutti i led vengono spenti e, ad ogni cambio di simbolo, i led
	devono mostrare il numero di simboli letti fino a quel punto
*/
void EINT1_IRQHandler (void)	  
{
  /* la funzione LED_Out assegna a tutti i led il valore in argomento */
	c_led_setup();
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
	
	
}

void EINT2_IRQHandler (void)	  
{
	LED_Off(0);
	LED_Off(1);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


