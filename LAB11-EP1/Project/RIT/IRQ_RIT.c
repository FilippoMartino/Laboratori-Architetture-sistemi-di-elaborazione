/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "../TIMER/timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "RIT.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int TO_EAT_MEAT;
volatile int EATING = 0;

/* extern variabiles */
extern int SATIETY;
extern int HAPPINESS;

/* extern functions */
extern void drawCandy (void);
extern void clearCandy(void);
extern void drawMeat(void);
extern void clearMeat(void);

void RIT_IRQHandler (void) {			
	
	if (!EATING) {
		disable_timer(2);
		enable_timer(0);
		enable_timer(1);
	}
	
	/* funzione per intercettare feeding */
	getDisplayPoint(&display, Read_Ads7846(), &matrix);
	
	if (display.x > 0 && display.x < 120 && display.y > 270) {
		display.x = 0;
		display.y = 0;
		if (SATIETY < 5 && !EATING){
			drawMeat();
			EATING = 1;
			/* abilitiamo il timer per animazione e disabilitiamo gli altri */
			TO_EAT_MEAT = 1;
			enable_timer(2);
			disable_timer(0);
			disable_timer(1);
			/* i timer verranno riabilitati in seguito */
		}
	}
	
	/* selezionato pulsante satiety */
	if (display.x > 120 && display.y > 270){
		display.x = 0;
		display.y = 0;
		if (SATIETY < 5 && !EATING){
			drawCandy();
			EATING = 1;
			/* abilitiamo il timer per animazione e disabilitiamo gli altri */
			TO_EAT_MEAT = 0;
			enable_timer(2);
			disable_timer(0);
			disable_timer(1);
			/* i timer verranno riabilitati in seguito */
			
		}
	}
	
	reset_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
