				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  ASM_funct
ASM_funct
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
				; extract argument 4 and 5 into R4 and R5
				LDR   r4, [r12]
				LDR   r5, [r12,#4]
				
				add	  r5, r4, r5
				; setup a value for R0 to return
				
				MOV	  r0, r5
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}

				

				
				
check_square  			PROC
						EXPORT  check_square            
						
						PUSH	{R4-R8, R10-R11, LR}	;	Salvo i valori dei registri in cui possono essere salvate variaibli e il valore dello stack pointer
						
						MUL		R0, R0, R0				;	R0 = x^2
						MUL		R1, R1, R1				;	R1 = y^2
						MUL		R2,	R2,	R2				;	R2 = r^2
						ADD		R0, R0, R1				;	R0 = x^2 + y^2
						CMP		R0, R2
						MOVLT	R0, #1
						MOVGT	R0, #0
						MOVEQ	R0, #1
						
						POP		{R4-R8, R10-R11, PC}
						
						ENDP
	

my_division  			PROC
						IMPORT __aeabi_fdiv
						EXPORT  my_division      
						; your assembly here
						bl __aeabi_fdiv
						; your assembly here
						ENDP
					

						END
                
					