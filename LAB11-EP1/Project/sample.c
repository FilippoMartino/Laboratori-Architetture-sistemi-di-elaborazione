/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

#define SIMULATOR 1

/* Il display ha dimensioni 239 X 319 (x, y) */

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  LCD_Initialization();
	
	joystick_init();
	TP_Init();
	TouchPanel_Calibrate();
	LCD_Clear(White);
	
	MakeBackground();
	
	
	/* Timer 0, per animazione centrale sprite */
	init_timer(0, 0, 0, 3, 1, 25000000); 						    	/* 1s * 25MHz = 25000000 = 0x17D7840 */
	enable_timer(0);
	
	/* Timer 1, per animazione cuori e decremento vita */
	//init_timer(1, 0, 0, 3, 0, 125000000); 							/* 5s * 25MHz = 125000000 = 0x07735940 */
	init_timer(1, 0, 0, 3, 1, 50000000); 									/* 5s * 25MHz = 125000000 = 0x07735940 */
	enable_timer(1);
	
	init_RIT(1250000, 0);																	/* 25ms * 25Mhz = 1250000 */
	enable_RIT();
	
	init_timer(2, 0, 0, 3, 1, 6250000);										/* 250ms * 25Mhz = 6250000 */
	
	LPC_SC->PCON |= 0x1;																	/* power-down	mode */
	LPC_SC->PCON &= ~(0x2);

	
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
