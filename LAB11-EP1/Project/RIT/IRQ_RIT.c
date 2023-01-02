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

/* variables needed for anti-debouncing function */
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;

/* extern variabiles */
extern int SATIETY;
extern int HAPPINESS;

/* extern functions */
extern void drawCandy (void);
extern void clearCandy(void);
extern void drawMeat(void);
extern void clearMeat(void);

void RIT_IRQHandler (void) {			
	
	/* funzione per intercettare feeding */
	getDisplayPoint(&display, Read_Ads7846(), &matrix);
	if (display.x > 0 && display.x < 120 && display.y > 270) {
		if (SATIETY < 6){
			drawMeat();
			clearMeat();
		}
	}
	/* selezionato pulsante satiety */
	if (display.x > 120 && display.y > 270){
		if (SATIETY < 6){
			drawCandy();
			clearCandy();
		}
	}
	
	reset_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
