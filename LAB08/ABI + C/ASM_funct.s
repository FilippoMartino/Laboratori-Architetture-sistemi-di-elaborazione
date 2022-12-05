
				

				AREA	mycode, CODE, READONLY
				
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
						PUSH	{R4-R8, R10-R11, LR}	; salviamo parametri
						
						LDR		R0, [R0]
						LDR		R1, [R1]				; carichiamo i valori puntati dagli indirizzi negli argomenti
						
						bl __aeabi_fdiv					; salto a funzione che deve effettuare divisione tra due registri 
						
						POP		{R4-R8, R10-R11, PC}	
						
						ENDP
						END
                
					