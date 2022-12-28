/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Permette la configurazione e l'utilizzo di 4 timer
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 to 3
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
		LPC_TIM0->TCR = 1;
  }
  else if(timer_num == 1)
  {
		LPC_TIM1->TCR = 1;
  }
	else if(timer_num == 2)
	{
		LPC_TIM2->TCR = 1;
	}	
	else 
	{
		LPC_TIM3->TCR = 1;
	}
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 to 3
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
		LPC_TIM0->TCR = 0;
  }
  else if(timer_num == 1)
  {
		LPC_TIM1->TCR = 0;
  }
	else if(timer_num == 2)
	{
		LPC_TIM2->TCR = 0;
	}
	else
	{
		LPC_TIM3->TCR = 0;
	}
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 to 3
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
		regVal = LPC_TIM0->TCR;
		regVal |= 0x02;
		LPC_TIM0->TCR = regVal;
  }
  else if (timer_num == 1)
  {
		regVal = LPC_TIM1->TCR;
		regVal |= 0x02;
		LPC_TIM1->TCR = regVal;
  }
  else if (timer_num == 2)
  {
		regVal = LPC_TIM2->TCR;
		regVal |= 0x02;
		LPC_TIM2->TCR = regVal;
  }
  else
  {
		regVal = LPC_TIM3->TCR;
		regVal |= 0x02;
		LPC_TIM3->TCR = regVal;
  }
  return;
}

/******************************************************************************
** 	Function name:	init_timer
**
** 	Descriptions:		inizializzazione timer
**
** 	parameters:			timer number: 0 to 3
**									Prescaler:		utilizzato per ampliare il tempo massimo, possibili multipli di 2
**																nel caso non venga utilizzato, inserire 0
**									MatchReg:		 	registro nel quale si specifica l'intervallo del timer 0 to 3
**									SRImatchReg:	funzionalità MatchRegister, quella specificata nel MCR, ossia Stop, Reset, Interrupt.
**									TimerInterval:intervallo di tempo.
**
**	FUNZIONALITA' SRI: 	vengono controllati 3 bit, partendo dal MSB, il primo determina lo STOP o meno, il secondo il
**											RESET o meno, il terzo se viene generato un INTERRUPT o meno: valori 1-TRUE 0-FALSE
**											La funzione provvede poi a spostare il valore di tre bit binario nella giusta posizioni in base al MR che
**											stiamo configurado (NOTARE che questa libreria permette la configurazione di un MR per TIMER); vediamo due esempi:
**											- valore 7: [111] STOP-TRUE, RESET-TRUE, INTERRUPT-TRUE
**											- valore 4: [100] STOP-TRUE, RESET-FALSE, INTERRUPT-FALSE
**	
**									
** 	Returned value:	0 if all well, 1 if timer_num not valid
**
******************************************************************************/

uint32_t init_timer ( uint8_t timer_num, uint32_t Prescaler, uint8_t MatchReg, uint8_t SRImatchReg, uint8_t priority, uint32_t TimerInterval)
{
  if ( timer_num == 0 )
  {
		LPC_TIM0->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM0->MR0 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM0->MR1 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM0->MR2 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM0->MR3 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}			

	NVIC_EnableIRQ(TIMER0_IRQn);
	
	/* priority set */
	NVIC_SetPriority(TIMER0_IRQn, priority);	
	return (0);
  }
  else if ( timer_num == 1 )
  {
		LPC_TIM1->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM1->MR0 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM1->MR1 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM1->MR2 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM1->MR3 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		NVIC_EnableIRQ(TIMER1_IRQn);
		
		/* priority set */
		NVIC_SetPriority(TIMER1_IRQn, priority);
		return (0);
	}
  else if ( timer_num == 2 )
  {
		LPC_TIM2->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM2->MR0 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM2->MR1 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM2->MR2 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM2->MR3 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		NVIC_EnableIRQ(TIMER2_IRQn);
		
		/* priority set */
		NVIC_SetPriority(TIMER2_IRQn, priority);
		return (0);
  }
	  else if ( timer_num == 3 )
  {
		LPC_TIM3->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM3->MR0 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM3->MR1 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM3->MR2 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM3->MR3 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		NVIC_EnableIRQ(TIMER3_IRQn);
		
		/* priority set */
		NVIC_SetPriority(TIMER3_IRQn, priority);
		return (0);
	}
	
  return (1);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
