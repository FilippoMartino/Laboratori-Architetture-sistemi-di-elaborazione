#include <stdio.h>
#include <stdlib.h>
#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"
extern void c_led_setup(void);
extern void ASM_conversion(void);
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


/*
	Premendo INT0 devo riniziare dal punto 1, ossia dal trigger di KEY 1
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

/*
	Premendo il tasto due inizia la conversione del messaggio in ASCII:
	- durante la conversione devono essere disabilitati INT0 e KEY1
	- al ritorno della chiamata i led mostrano il numero totale di simboli convertiti
	- i pulsanti disabilitati devono essere riabilitati
*/
void EINT2_IRQHandler (void)	  
{
	
	/* disabilitiamo INT0 */
	NVIC_DisableIRQ(EINT0_IRQn);
	/* disabilitiamo KEY1 */
	NVIC_DisableIRQ(EINT1_IRQn);
	
	ASM_conversion();
	
	/* Riabilitiamo i due pulsanti */
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


