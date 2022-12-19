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
#include "../led/led.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/
void TIMER0_IRQHandler (void)
{
	static uint8_t position = 7;
	LED_Off(position);
	if(position == 7)
		position = 2;
	else
		position++;
	LED_On(position);
	/* alternatively to LED_On and LED_off try to use LED_Out */
	//LED_Out((1<<position)|(led_value & 0x3));							
	/* LED_Out is CRITICAL due to the shared led_value variable */
	/* LED_Out MUST NOT BE INTERRUPTED */
	
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
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void) {
	
	/* 
		devo controllare quale dei due MATCH REGISTER ha attivato l'interruzione: 
		- nel caso sia il primo spengo il led
		- nel caso sia il secondo accendo
	*/
	
	/* 
		Per controllare se ho interruzione rispetto ad un MR piuttosto che ad un altro:
		- controllo il match control regsiter del timer, in base a quale bit guardo ho informazioni su un MR
			-> bit [0-2] MR0
			-> bit [3-5] MR1
			-> bit [6-8] MR2
			-> bit [9-11] MR3
		Dei tre bit a disposizione, il meno significativo, controlla il match:
			- nel caso sia uguale ad 1 abbiamo match
			- uguale a 0 nessun match e nessun interrupt
			
	*/
	
	/* verifico se MR0 attivo */
	if ((LPC_TIM2->MCR & (1)) == 1){
		// MR0 triggered
		LED_On(0);
	} else if (((LPC_TIM2->MCR) & (1 << 3)) == 1) {
		// MR1 triggered
		LED_Off(0);
	}
	
	
	
	
	
	LPC_TIM2->IR = 1;
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
