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
volatile int IS_LEFT_SELECTED = 0;
volatile int IS_RIGHT_SELECTED = 0;

/* extern variabiles */
extern int SATIETY;
extern int HAPPINESS;
extern int TO_RELOAD;

/* extern functions */
extern void drawCandy (void);
extern void clearCandy(void);
extern void drawMeat(void);
extern void clearMeat(void);
extern void selectLeft(void);
extern void clearLeft(void);
extern void selectRight(void);
extern void clearRight(void);

void RIT_IRQHandler (void) {	

	/* funzione per intercettare feeding */
	getDisplayPoint(&display, Read_Ads7846(), &matrix);
	
	/* if joystick Left */
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0  && !IS_LEFT_SELECTED && !EATING){
		clearRight();
		selectLeft();
		IS_LEFT_SELECTED = 1;
		IS_RIGHT_SELECTED = 0;
	}
	/* if joystick Right */
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && !IS_RIGHT_SELECTED && !EATING){
		clearLeft();
		selectRight();
		IS_LEFT_SELECTED = 0;
		IS_RIGHT_SELECTED = 1;
	}
	
	/* reset partita */
	if (TO_RELOAD){
		if ((LPC_GPIO1->FIOPIN & (1<<25)) == 0){			
			NVIC_SystemReset();
			LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
			return;	
			
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
	
	if ((LPC_GPIO1->FIOPIN & (1<<25)) == 0 && IS_LEFT_SELECTED && !ENDGAME) {
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
	if ((LPC_GPIO1->FIOPIN & (1<<25)) == 0 && IS_RIGHT_SELECTED && !ENDGAME){
		if (HAPPINESS < 5 && !EATING){
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
