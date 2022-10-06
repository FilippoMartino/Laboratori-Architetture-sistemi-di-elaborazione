.data
	v1:		.byte 	2,6,-3,11,5,4,3,9,3,4,5,11,-3,6,2
	flag: 	.space 	1
	
.text

MAIN:

	daddi	R1, R0, 1		; variabile booleana per sequenza palindroma, inizializzata a vero di default
	daddi	R2, R0, 7		; contatore per conteggio elementi, metà (naturale) della lunghezza della stringa
	
	daddi	R3, R0, 0		; puntatore inizio vettore
	daddi	R4, R0, 14		; puntatore fine vettore
	
LOOP:
	
	lb		R5, v1(R3)		; carico nei in R5 ed R6 i due valori simmetrici
	lb		R6, v1(R4)
	
	daddi	R3, R3, 1		; incremento/decremento puntatori simmetricamente
	daddi	R4, R4, -1
	
	beq		R5, R6, PAL		; se i due numeri simmetrici sono uguali vado avanti
	
	xor		R1, R1, R1		; altrimenti metto a 0 la variabile ed esco dal ciclo
	j		END_PAL
	

PAL:	

	daddi	R2, R2, -1
	bnez	R2, LOOP
	
END_PAL:

	sb		R1, flag(R0)	; salvo il valore booleano

HALT