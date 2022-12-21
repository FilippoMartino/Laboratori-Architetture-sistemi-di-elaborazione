/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 *		to control led11 and led 10 through EINT buttons (similarly to project 03_)
 *		to control leds9 to led4 by the timer handler (1 second - circular cycling)
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/

                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	init_timer_2(0x0000249F, 0x0000927C);
	//init_timer(0,0x001312D0);							/* TIMER0 Initialization              */
																				/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																				/* T = K / Fr = 0x001312D0 / 25MHz    */
																				/* T = K / Fr = 1250000 / 25MHz      */
																				/* T = 0.05s	( 50 milli second)   							*/
	LED_On(1);
	enable_timer(2);
					
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
