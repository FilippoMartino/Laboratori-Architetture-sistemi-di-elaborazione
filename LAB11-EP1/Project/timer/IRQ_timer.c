/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

/* variabili esterne */
extern int AMOGUS_STAND;
extern int HAPPINESS;
extern int SATIETY;

/* funzioni esterne */
extern void amogusClear(void);
extern void amogus_stand(void);
extern void amogus_sit(void);
extern void life(int life, int kind);

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

/* ogni volta che arrivo qui devo cambiare visualizzazione personaggio */
void TIMER0_IRQHandler (void) {
	
	
	if (AMOGUS_STAND){
		amogusClear();
		amogus_sit();
	} else {
		amogusClear();
		amogus_stand();
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	HAPPINESS -= 1;
	SATIETY 	-= 1;
	
	switch (HAPPINESS){
		case 4:
			life(80, 0);
			break;
		case 3:
			life(60, 0);
			break;
		case 2:
			life(40, 0);
			break;
		case 1:
			life(20, 0);
			break;
		case 0:
			HAPPINESS = 5;
			life(100, 0);
			//life(0, 0);
			//RUNNAWAY procedure...
			break;
	}
	
	switch (SATIETY){
		case 4:
			life(80, 1);
			break;
		case 3:
			life(60, 1);
			break;
		case 2:
			life(40, 1);
			break;
		case 1:
			life(20, 1);
			break;
		case 0:
			SATIETY = 5;
			life(100, 1);
			//life(0, 1);
			//RUNNAWAY procedure...
			break;
	}
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
