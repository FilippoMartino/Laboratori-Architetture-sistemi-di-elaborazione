.data
	
	ifmap:	.byte 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	kernel:	.byte	1,1,1,1,1,1,1,1,1
	ofmap:	.space	9

.text

MAIN:

	dadd	R1, R0, R0		; puntatori alle tre matrici, rispettivamente ifmap, kernel e ofmap
	dadd	R2, R0, R0
	dadd	R3, R0, R0
	
	dadd	R4, R0, R0		; storage
	
	daddi	R5, R0, 9		; contatore ciclo interno
	dadd	R6, R0, R0		; contatore ciclo esterno
	daddi 	R7, R0, 3		; contatore riga
	daddi 	R10, R0, 0		; contatore colonna
	
	daddi 	R8, R0, 9
	daddi	R9, R0, 3		; costanti
	daddi	R15, R0, 5

EX_LOOP:

	beqz	R1, IN_LOOP		; per saltare il ciclo esterno la prima volta
	
	bne		R6, R9, SKIP_CLEAR	; controllo se non debba ripristinare il contatore esterno
	
	dadd	R6, R0, R0		; pulisco il contatore del ciclo esterno
	daddi	R10, R10, 1		; aggiorno il valore del puntatore alla riga successiva
	dmul	R14, R10, R15
	
SKIP_CLEAR:	

	dadd 	R1, R14, R6		; assegno il valore del contatore del ciclo esterno al puntatore della ifmap
	
END_IF:

	xor		R2, R2, R2		; inizializzo il valore del puntatore della kernel
	xor		R4, R4, R4		; inizializzo la variabile per il risultato

IN_LOOP:

	beqz	R5, STORE		; nel caso abbia finito di processare una matrice 3x3 vado a salvare il dato

	lb		R11, ifmap(R1)	; sommo in R13 i due valori delle rispettive matrici	
	lb		R12, kernel(R2)
	dmul	R13, R11, R12
	
	dadd	R4, R4, R13		; aggiorno risultato
	
	daddi	R7, R7, -1		; decremento contatore di riga
	daddi	R5, R5, -1		; decremento contatore ciclo interno
	daddi	R2, R2, 1		; incremento puntatore kernel
	
	bnez	R7,IN_ROW
	
	daddi	R1, R1, 3		; incremento puntatore della ifmap
	daddi	R7, R0, 3		; se mi trovo qui significa che devo passare alla riga successiva, ripristino contatore di riga
	
	j		IN_LOOP
	
IN_ROW:

	daddi	R1, R1, 1		; incremento puntatore (di 1 byte)
	j		IN_LOOP
	
	
STORE:
	
	sb		R4, ofmap(R3)
	daddi	R3, R3, 1
	
	beq		R3, R8, MY_END	; controllo sulla chiusura dei cicli
	
	daddi	R5, R0, 9
	daddi 	R6, R6, 1		; incremento contatore ciclo esterno
	j		EX_LOOP
	
	
MY_END:


HALT