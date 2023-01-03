/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include <string.h>
#include "../RIT/RIT.h"

/* extern variabiles */
extern int AMOGUS_STAND;
extern int HAPPINESS;
extern int SATIETY;
extern int TO_EAT_MEAT;
extern int EATING;
extern int ENDGAME;

/* extern functions */
extern void amogusClear(void);
extern void areaClear(void);
extern void amogus_sit(void);
extern void amogus_stand(void);
extern int 	life(int, int);
extern void timeUpdate(char* toPrint);
extern void clearCandy(void);
extern void clearMeat(void);
extern void runRight(int phase, int fromLeft);
extern void runLeft(int phase, int fromRight);
extern void eatRight(void);
extern void eatLeft(void);
extern void endgameAnimation(int phase);
extern void resetGame(void);

/* internal */ 

/* AGE control */
static int h = 0;
static int m = 0;
static int s = 0;

void restoreLife(int value, int kind){
	switch (value){
		case 4:
			life(100, kind);
			break;
		case 3:
			life(80, kind);
			break;
		case 2:
			life(60, kind);
			break;
		case 1:
			life(40, kind);
			break;
		case 0:
			life(20, kind);
			break;
		default:
			break;
	}
}

/******************************************************************************
** Function name:			Timer0_IRQHandler
**
** Descriptions:			Timer/Counter 0 interrupt handler
**
** parameters:				None
** Returned value:		None
**
******************************************************************************/
void TIMER0_IRQHandler (void)
{
	
		char time[64];
		s ++;
		if (s == 60) {
			s = 0;
			m ++;
		}
		
		if (m == 60) {
			m = 0;
			h ++;
		}
		
		if (s < 10 && m > 9 && h > 9) {
			sprintf(time, "AGE: %d:%d:0%d", h, m, s);
		} else if (s < 10 && m < 10 && h > 9) {
			sprintf(time, "AGE: %d:0%d:0%d", h, m, s);
		} else if (s < 10 && m < 10 && h < 10) {
			sprintf(time, "AGE: 0%d:0%d:0%d", h, m, s);
		} else {
			sprintf(time, "AGE: %d:%d:%d", h, m, s);
		}
		
		timeUpdate(time);
		
		if (AMOGUS_STAND){
		//amogusClear();
		amogus_sit();
	} else {
		//amogusClear();
		amogus_stand();
	}
		
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
	
  return;
}


/******************************************************************************
** Function name:			Timer1_IRQHandler
**
** Descriptions:			Timer/Counter 1 interrupt handler
**
** parameters:				None
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
			life(0, 0);
			break;
		case -1:
			ENDGAME = 1;
			break;
		default:
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
			life(0, 0);
			break;
		case -1:
			ENDGAME = 1;
			break;
		default:
			break;
	}
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
** Function name:			Timer2_IRQHandler
**
** Descriptions:			Timer/Counter 2 interrupt handler
**
** parameters:				None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	
	static int phase = 0;
	static int toRet = 0;
	int i;
	
		if (ENDGAME == 1) {

			if (phase < 8){
				amogusClear();
				endgameAnimation(phase);
				phase ++;
			} else {
				areaClear();
				resetGame();
			}
		}

	
		if (TO_EAT_MEAT && !ENDGAME){
			
			if (phase < 5 && !toRet){
				amogusClear();
				runLeft(phase, 0);
				phase ++;
			} else if (phase == 5) {
				amogusClear();
				eatLeft();
				clearMeat();
				restoreLife(SATIETY, 1);
				SATIETY ++;
				toRet = 1;
				phase --;
			} else if (toRet && phase > 0) {
				areaClear();
				runRight(phase, 1);
				phase --;
			} else if (toRet && phase == 0){
				amogusClear();
				amogus_sit();
				EATING = 2;
				toRet = 0;
			}
			
		} else if (!TO_EAT_MEAT && !ENDGAME) {
			if (phase < 5 && !toRet){
				amogusClear();
				runRight(phase, 0);
				phase ++;
			} else if (phase == 5) {
				amogusClear();
				eatRight();
				clearCandy();
				restoreLife(HAPPINESS, 0);
				HAPPINESS ++;
				toRet = 1;
				phase --;
			} else if (toRet && phase > 0) {
				areaClear();
				runLeft(phase, 1);
				phase --;
			} else if (toRet && phase == 0){
				amogusClear();
				amogus_sit();
				EATING = 2;
				toRet = 0;
			}
		}
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
** Function name:			Timer3_IRQHandler
**
** Descriptions:			Timer/Counter 3 interrupt handler
**
** parameters:				None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}




/******************************************************************************
**                            End Of File
******************************************************************************/
