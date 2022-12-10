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
					
					LDRB	R4, [SP]
					LDRB	R5, [SP, #4]
					LDRB	R6, [SP, #8]
					
					; R4 -> change_symbol
					; R5 -> space
					; R6 -> sentence_end
					
					; R7 -> counter
					; R8 -> mask
					
					; R9 -> pointer to morse table
					; R10 -> pointer to conversion table
					; R11 -> conversion counter
LOOP				

					LDRB	R8, [R0, R7]
					LSL		R8, #2
					ADD		R7, R7, #1
					CMP		R7, #4
					BNE		LOOP
					

					
					POP		{R4-R8, R10-R11, PC}		; restore registers
	
	ENDP
		


	END