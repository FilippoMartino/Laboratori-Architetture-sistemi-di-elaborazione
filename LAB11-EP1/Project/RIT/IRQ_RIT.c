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
volatile int ENDGAME = 0;
volatile int IS_T2_ENABLED = 0;

/* extern variabiles */
extern int SATIETY;
extern int HAPPINESS;
extern int TO_RELOAD;

/* extern functions */
extern void drawCandy (void);
extern void clearCandy(void);
extern void drawMeat(void);
extern void clearMeat(void);

void RIT_IRQHandler (void) {	

	/* funzione per intercettare feeding */
	getDisplayPoint(&display, Read_Ads7846(), &matrix);
	
	/* reset partita */
	if (TO_RELOAD){
		if (display.x > 0 && display.y > 270){
			display.x = 0;
			display.y = 0;
			
			/* Restore di tutte le variabili e gioco */
			ENDGAME = 0;
			LCD_Clear(White);
			MakeBackground();
			enable_RIT();
			enable_timer(0);
			enable_timer(1);
			reset_timer(0);
			reset_timer(1);
			disable_timer(2);
			
			TO_RELOAD = 0;
		}
	}	
	
	/* Ripristina i timer 0 e 1, disabilita il due, il tutto dopo aver magiato (lo fa solo nel interrupt imm. dopo	*/
	if (EATING == 2 && !ENDGAME) {
		EATING = 0;
		disable_timer(2);
		enable_timer(0);
		enable_timer(1);
	}
	
	/* funzione per gestire l'endgame quando una delle due barre della vita sono vuote */
	if (ENDGAME == 1 && !IS_T2_ENABLED){
		enable_timer(2);
		IS_T2_ENABLED = 1;
		disable_timer(0);
		disable_timer(1);
		reset_RIT();
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		return;	
	}
	
	/* funzione per intercettare feeding */
	
	if (display.x > 0 && display.x < 120 && display.y > 270 && !ENDGAME) {
		display.x = 0;
		display.y = 0;
		if (HAPPINESS < 5 && !EATING){
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
	if (display.x > 120 && display.y > 270 && !ENDGAME){
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
