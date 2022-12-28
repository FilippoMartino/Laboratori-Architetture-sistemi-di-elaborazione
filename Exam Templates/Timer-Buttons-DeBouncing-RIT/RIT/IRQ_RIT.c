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

/* variables needed for anti-debouncing function */
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;

void RIT_IRQHandler (void) {			
	
	
	
	
	
	/* ========== PER FUNZIONALITA' ANTI DEBOUNCING ========== */
	
	/* BUTTON 0 [EINT0] TRIGGERED */
	if(down_0 != 0){  
			down_0 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			switch(down_1){
			case 2:
				// 	HERE CODE TO BE EXECUTED ONE TIME ON BUTTON 0 [EINT0]
				break;
			default:
				//	HERE CODE TO BE EXECTUED AFTER FIRST ACTION ON TRIGGERED	
				break;
			}
		}	else {
		down_0 = 0;			
		NVIC_EnableIRQ(EINT0_IRQn);						/* enable EINT0 interrupts */
		LPC_PINCON->PINSEL4 |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	
	/* BUTTON 1 [EINT1] TRIGGERED */
	if(down_1 != 0){  
			down_1 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			switch(down_1){
			case 2:
				// 	HERE CODE TO BE EXECUTED ONE TIME ON BUTTON 0 [EINT1]
				break;
			default:
				//	HERE CODE TO BE EXECTUED AFTER FIRST ACTION ON TRIGGERED	
				break;
			}
		}	else {
		down_1 = 0;			
		NVIC_EnableIRQ(EINT1_IRQn);						/* enable EINT1 interrupts */
		LPC_PINCON->PINSEL4 |= (1 << 22);     /* External interrupt 1 pin selection */
		}
	}
	
	/* BUTTON 2 [EINT2] TRIGGERED */
	if(down_2 != 0){  
			down_2 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			switch(down_2){
			case 2:
				// 	HERE CODE TO BE EXECUTED ONE TIME ON BUTTON 0 [EINT1]
				break;
			default:
				//	HERE CODE TO BE EXECTUED AFTER FIRST ACTION ON TRIGGERED	
				break;
			}
		}	else {
		down_2 = 0;			
		NVIC_EnableIRQ(EINT2_IRQn);						/* enable EINT2 interrupts */
		LPC_PINCON->PINSEL4 |= (1 << 24);     /* External interrupt 2 pin selection */
		}
	}
	
	/* ========== FINE FUNZIONALITA' ANTI DEBOUNCING ========== */
	
	
	
	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
