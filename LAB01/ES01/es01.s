.data
	a: 		.byte 48,7,8,28,12,26,44,42,49,23,25,22,5,50,40,36,43,47,39,34,17,21,10,35,31,32,33,11,45,16,46,3,20,19,41,29,38,30,14,2,9,6,37,24,27,1,15,4,13,18
	b: 		.byte 39,26,32,31,24,35,27,4,40,10,49,45,5,38,15,48,17,36,13,33,19,47,20,11,14,30,46,3,22,23,42,7,25,29,34,43,2,44,41,50,37,8,28,12,21,1,16,9,6,18
	c: 		.space 50
	
	min: 	.space 1
	max:	.space 1

.text

MAIN:

	daddi	R1, R0, 50		; inizializzazione dei registri R1 ed R2 (rispettivamente contatore cicli e puntatore memoria)
	xor		R2, R2, R2
	
	daddi 	R6, R0, 0		; inizializzazione variabili per massimo e minimo
	daddi	R7, R0, 127
	
LOOP:
	
	lb		R3, a(R2)		; caricamento del valore nella R2-esima posizione dei due vettori a e b
	lb		R4, b(R2)
	
	dadd	R5, R3, R4		; inseriamo in R5 la somma tra R3 ed R4
	
	sb		R5, c(R2)		; scriviamo (store byte) il risultato della somma salvato in R5 all'iterno di c
	
	daddi	R2, R2, 1		; incremento e decremento puntatore e contatore
	daddi	R1, R1, -1
	
	slt		R8, R6, R5		; nel caso R6 (massimo fino a questo momento) sia minore di R5 (risultato attuale somma), setta R8 a vero
	beqz	R8, EXIT1		; se R8 è falso abbiamo in R6 il valore massimo, quello attuale è minore e non dobbiamo variare nulla
	
	dadd	R6, R5, R0		; in caso contrario sostituiamo il valore massimo con il valore attuale
	
EXIT1:

	slt		R8, R5, R7		; nel caso R5 (valore attuale), sia minore del minimo, R8 viene settato a vero
	beqz	R8, EXIT2
	
	dadd	R7, R5, R0		; sostituiamo il valore minimo nel registro

EXIT2:
	
	bnez	R1, LOOP
	
	sb		R6, max(R0)		; salviamo i valori dei due registri nelle variabili; lo faccio qui in modo da non accedere continuamente in memoria
	sb		R7, min(R0)
	
	

HALT