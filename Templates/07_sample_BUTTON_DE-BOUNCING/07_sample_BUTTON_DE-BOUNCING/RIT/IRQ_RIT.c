/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

/*
	Le funzioni del main, da richiamare dopo il trigger dei relativi pulsanti
*/
extern void c_led_setup(void);
extern void ASM_conversion(void);

/*
	Tre variabili di stato, una per ognuno dei pulsanti
*/
volatile int down_1 = 0;
volatile int down_2 = 0;

void RIT_IRQHandler (void)
{			
	/* Se mi trovo qui dentro dopo che un pulsante sia stato selezionato la sua variabile sarà ad 1 */
	/* Ora devo fare i controlli per tutte le porte */
	
	if (down_1 != 0){
			
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			down_1 ++;
			
			/* controllo variabile di stato */
			switch(down_1){
				/* prima volta che intercetto lo switch selezionato */
				case 2:
					/* la funzione LED_Out assegna a tutti i led il valore in argomento */
					c_led_setup();
					break;
				default:
					break;
			}
		} else {
		/* pulsante rilasciato, ripristiniamo variabile di stato */
		down_1 = 0;
		NVIC_EnableIRQ(EINT1_IRQn); 							/* reab interrupt sul KEY1 */
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */
		}
	}
		if (down_2 != 0) {
			if ((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
				down_2 ++;
				switch (down_2){
					case 2:
						/* disabilitiamo INT0 */
						NVIC_DisableIRQ(EINT0_IRQn);
						/* disabilitiamo KEY1 */
						NVIC_DisableIRQ(EINT1_IRQn);
	
						ASM_conversion();
	
						/* Riabilitiamo i due pulsanti */
						NVIC_EnableIRQ(EINT0_IRQn);
						NVIC_EnableIRQ(EINT1_IRQn);
						break;
					default:
					break;
			}
		} else {
			/* pulsante rilasciato, ripristiniamo variabile di stato */
			down_2 = 0;
			NVIC_EnableIRQ(EINT2_IRQn); 							/* reab interrupt sul KEY2 */
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
		}
	}

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	reset_RIT();
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
