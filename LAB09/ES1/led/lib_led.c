/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Atomic led init functions
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

/*----------------------------------------------------------------------------
  Function that initializes LEDs and switch them off
 *----------------------------------------------------------------------------*/

unsigned char led_value;

void LED_init(void) {

/*
	Utilizziamo anche qui come nei pulsanti la configurazione mediante PINSEL4 per specificare
	i pin di GPIO, andando qui ad utilizzare la maschera FFFF0000 in and per specificare i pin
	da 0 a 7
*/	
  	LPC_PINCON->PINSEL4 &= 0xFFFF0000;	//PIN mode GPIO (00b value per P2.0 to P2.7)
/*
	Qui abbiamo poi la selezione dei PIN come output 
*/
	LPC_GPIO2->FIODIR   |= 0x000000FF;  	//P2.0...P2.7 Output (LEDs on PORT2 defined as Output)
 /* 
 	LPC_GPIO2->FIOSET    = 0x000000FF;	//all LEDs on 
*/
/*
	Abbiamo poi la seguente configurazione per pulire, ossia spegnere, tutti i led, che 
	a questo punto sono attivati e settati come output
*/
	
	LPC_GPIO2->FIOCLR    = 0x000000FF;  //all LEDs off
	
/*
	ATTENZIONE: FIOSET e FIOCLR servono per pulire i registiri al valore di maschera assegnato, FIOSET attiva in base
	alla maschera (vedi commento sopra per attivare tutti i led), mentre FIOCLR li disattiva, sempre in base alla maschera 
*/

/*
	questa variabile viene utilizzata per avere una nota del valore lasciato in essa da ogni funzione; la funzionalità
	ad ora mi è sconosciuta
*/
	led_value = 0;
}

/*
	Non specificato dal prof ma credo serva a de-inizializzare i led, non so quando potrebbe servire
*/
void LED_deinit(void) {

  LPC_GPIO2->FIODIR &= 0xFFFFFF00;  //P2.0...P2.7 Output LEDs on PORT2 defined as Output
}
