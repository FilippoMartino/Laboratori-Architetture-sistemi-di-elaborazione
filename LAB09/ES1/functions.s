					AREA MorseData, DATA, READONLY

MORSE				DCD	0xFFFFFF01, 0xFFFF1000, 0xFFFF1010, 0xFFFFF100, 0xFFFFFFF0, 0xFFFF0010 
					DCD 0xFFFFF110, 0xFFFF0000, 0xFFFFFF00, 0xFFFF0111, 0xFFFFF101, 0xFFFF0100 
					DCD 0xFFFFFF11, 0xFFFFFF10, 0xFFFFF111, 0xFFFF0110, 0xFFFF1101, 0xFFFFF010 
					DCD 0xFFFFF000, 0xFFFFFFF1, 0xFFFFF001, 0xFFFF0001, 0xFFFFF011, 0xFFFF1001
					DCD 0xFFFF1011, 0xFFFF1100, 0xFFF01111, 0xFFF00111, 0xFFF00011, 0xFFF00001
					DCD 0xFFF00000, 0xFFF10000, 0xFFF11000, 0xFFF11100, 0xFFF11110, 0xFFF11111

CONVERSION			DCB	"A", "B", "C", "D", "E", "F"
					DCB	"G", "H", "I", "J", "K", "L"
					DCB	"M", "N", "O", "P", "Q", "R"
					DCB	"S", "T", "U", "V", "W", "X"
					DCB	"Y", "Z", "1", "2", "3", "4"
					DCB	"5", "6", "7", "8", "9", "0"
					
					AREA myCode, CODE, READONLY
			
translate_morse		PROC
					EXPORT	translate_morse
						
					PUSH	{R4-R8, R10-R11, LR}		; save registers
					
					; R0 -> *vett_input
					; R1 -> vett_input_size
					; R2 -> *vett_output
					; R3 -> vett_output_size
					; R11 -> output_counter
					
					MOV		R11, #0
					ADD		SP, SP, #32
					LDRB	R4, [SP]
					LDRB	R5, [SP, #4]
					LDRB	R6, [SP, #8]
					ADD		SP, SP, #-32
					
					; R4 -> change_symbol
					; R5 -> space
					; R6 -> sentence_end
					
					; R7 -> counter
					
					MOV		R7, #0
					
					; R8 -> mask
					
LOOP				MOV		R8, #0xFFFFFFFF

					; R9 -> input

READ				LDRB	R9, [R0, R7]		; carico valore morse (bit)
					ADD		R7, R7, #1
					CMP		R7, R1
					BEQ		END_TM
					CMP		R9, #'0'			; inizio i confronti
					BEQ		is_zero
					CMP		R9, #'1'
					BEQ		is_one
					BL		convert				; nel caso debba convertire chiamo la procedura
					CMP		R9, R6
					BEQ		END_TM
					B		LOOP				; ritorno dalla procedura
								
is_zero				LSL		R8, #4				; sposta a sinistra di una posizione la maschera (4 byte in hex)
					EOR		R8, #0				; OR con 0 per essere sicuri che ultima cifra scritta sia uno zero
					B		READ

is_one				LSL		R8, #4
					EOR		R8, #1				; shift come prima e OR per essere sicuri di aver uno come ultima cifra
					B		READ

is_space			
					
					LSL		R8, #2
					ADD		R7, R7, #1
					CMP		R7, #4
					BNE		LOOP
					

					
END_TM				POP		{R4-R8, R10-R11, PC}		; restore registers
					MOV		R0, R11
					MOV		R1, #2
					ENDP
						
convert				PROC
					PUSH	{R0-R10, R12, LR}
					LDR		R0, =MORSE
					LDR		R1, =CONVERSION		; puntatori alle tabelle per conversione
					MOV		R3, #-1				; counter
					
					B		load_morse			; salvo parola
					
check_space			CMP		R9, R5
					BEQ		load_space
					B		END_CONV

load_morse			ADD		R3, R3, #1
					LDR		R4, [R0, R3, LSL #2]; scorro i valori della tabella morse e carico in R4
					CMP		R4, R8				; confronto con la maschera
					BNE		load_morse
					LDRB	R6, [R1, R3]		; carico il valore corrispondente all'indirizzo nella tab di conv
					STRB	R6, [R2, R11]
					ADD		R11, R11, #1		; carico il valore nel vettore di output ed incremento contatore
					B		check_space
					
load_space			MOV		R3, #' '
					STRB	R3, [R2, R11]
					ADD		R11, R11, #1
					B		END_CONV

END_CONV			POP		{R0-R10, R12, PC}
					ENDP
						
					END