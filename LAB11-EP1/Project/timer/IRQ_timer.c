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

/* extern variabiles */
extern int AMOGUS_STAND;
extern int HAPPINESS;
extern int SATIETY;

/* extern functions */
extern void amogusClear(void);
extern void amogus_sit(void);
extern void amogus_stand(void);
extern int 	life(int, int);
extern void timeUpdate(char* toPrint);


/* internal; AGE control */
static int h = 0;
static int m = 0;
static int s = 0;

/******************************************************************************
** Function name:			Timer0_IRQHandler
**
** Descriptions:			Timer/Counter 0 interrupt handler
**
** parameters:				None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/
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
