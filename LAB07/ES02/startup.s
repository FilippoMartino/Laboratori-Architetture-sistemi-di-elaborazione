;/**************************************************************************//**
; * @file     startup_LPC17xx.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           NXP LPC17xx Device Series
; * @version  V1.10
; * @date     06. April 2011
; *
; * @note
; * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF
				
				AREA    MyRODataArea, DATA, READONLY, align=3

INGREDIENT_CALORIES 	DCD 0x01, 30, 0x02, 70, 0x03, 200, 0x04, 42, 0x05, 81
						DCD 0x06, 20
INGREDIENT_QUANTITY 	DCD 0x02, 50, 0x05, 3, 0x03, 10, 0x01, 5, 0x04
						DCD 8, 0x06, 30
NUM_INGREDIENTS 		DCB 6

				AREA    MyRWDataArea, DATA, READWRITE, align=3
CALORIES_ORDERED		SPACE	6*4
CAL_QUANT				SPACE	6*4
	
QUANTITY_ORDERED		SPACE	6*4
QUANT_QUANT				SPACE	6*4
					
                AREA    |.text|, CODE, READONLY, align=3


; Reset Handler

calories 		RN  0
quantity		RN	1 	
calories_rdr	RN	2
cal_quant		RN	3
quantity_rdr	RN	4
quant_quant		RN	5
i				RN	6	
j				RN	7
k				RN	8
temp			RN	9
elements		RN 	10
temp_2			RN	12

Most_caloric	RN	11

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
                LDR     R0, =Reset_Handler

				; your code here
				LDR 	calories, 		=INGREDIENT_CALORIES		; assegnazione puntatori
				LDR 	quantity, 		=INGREDIENT_QUANTITY
				LDR		calories_rdr,	=CALORIES_ORDERED
				LDR		cal_quant,		=CAL_QUANT
				LDR		quantity_rdr, 	=QUANTITY_ORDERED
				LDR		quant_quant,	=QUANT_QUANT
				LDR		elements,		=NUM_INGREDIENTS
				LDR		elements,		[elements]				; molto importante, ricordarsi di estrarre
																; il valore dall'indirizzo!
				
				MOV 	i, #0
				MOV		j, #0

LOAD_LOOP		
				MOV		k, j
				
				LDR		temp, [calories, k, LSL #2]
				STR		temp, [calories_rdr, i, LSL #2]			; calories_rdr[i] = calories[j]
				
				LDR		temp, [quantity, k, LSL #2]
				STR		temp, [quantity_rdr, i, LSL #2]			; quantity_rdr[i] = quatity[j]
				
				ADD		k, k, #1
				
				LDR		temp, [calories, k, LSL #2]
				STR		temp, [cal_quant, i, LSL #2]			; cal_quant[i] = calories[j + 1]
				
				LDR		temp, [quantity, k, LSL #2]
				STR		temp, [quant_quant, i, LSL #2]			; quant_quant[i] = quantity[j + 1]
				
				ADD		i, i, #1
				ADD		j, j, #2


				CMP		i, elements
				BNE		LOAD_LOOP
																; arrivato qui ho i 4 vettori da ordinare
																
				MOV		R0, elements							; uso R0 come vettore di appoggio
				ADD		R0, R0, #-1
				MOV		i, #0
EX_LOOP			
				MOV		j, #0
IN_LOOP			
				MOV		k, j					
				ADD		k, k, #1								; k = j + 1
				
				LDR		temp, 	[cal_quant, j, LSL #2]
				LDR		temp_2, [cal_quant, k, LSL #2]
				CMP		temp, temp_2
				BGT		NO_SWAP_C								; if (cal_quant[j] < cal_quant[j + 1]) SWAP
				
				STR		temp_2, [cal_quant, j, LSL #2]			; cal_quant[j] = cal_quant[j + 1];
				STR		temp, 	[cal_quant, k, LSL #2]			; cal_quant[j + 1] = temp;
				
				LDR		temp, 	[calories_rdr, j, LSL #2]
				LDR		temp_2, [calories_rdr, k, LSL #2]
				STR		temp_2, [calories_rdr, j, LSL #2]		; calories_rdr[j] = calories_rdr[j + 1];		
				STR		temp, 	[calories_rdr, k, LSL #2]		; calories_rdr[j + 1] = temp
NO_SWAP_C
				LDR		temp, 	[quant_quant, j, LSL #2]
				LDR		temp_2, [quant_quant, k, LSL #2]
				CMP		temp, temp_2
				BGT		NO_SWAP_Q								; if (quant_quant[j] < quant_quant[j + 1]) SWAP
				
				STR		temp_2, [quant_quant, j, LSL #2]		; quant_quant[j] = quant_quant[j + 1];
				STR		temp, 	[quant_quant, k, LSL #2]		; quant_quant[j + 1] = temp;
				
				LDR		temp, 	[quantity_rdr, j, LSL #2]
				LDR		temp_2, [quantity_rdr, k, LSL #2]
				STR		temp_2, [quantity_rdr, j, LSL #2]		; quantity_rdr[j] = quantity_rdr[j + 1];		
				STR		temp, 	[quantity_rdr, k, LSL #2]		; quantity_rdr[j + 1] = temp

NO_SWAP_Q
				ADD		j, j, #1
				CMP		j, R0
				BNE		IN_LOOP									; controlli ciclo interno
				
				ADD		i, i, #1								; controlli ciclo esterno
				CMP		i, elements
				BNE		EX_LOOP
				
				
				
				

				
				
				
				

				; STR		j, [Calories_rdr]
				
				B		.
				
                ENDP
					


 
; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit                

                END
