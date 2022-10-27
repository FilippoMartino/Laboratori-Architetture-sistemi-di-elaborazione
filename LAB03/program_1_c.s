.data

	v1:	.double 22.87,55.4,2.36,42.78,76.68,15.58,64.05,96.07,53.85,84.53,69.73,46.85,77.72,80.74,93.31,16.89,50.6,57.89,73.82,51.94,95.08,98.2,92.31,61.28,54.66,78.39,19.32,24.02,61.01,55.1
	v2:	.double	62.2,14.82,29.06,70.49,71.88,8.33,25.48,85,36.59,15.05,27.86,26.81,95.71,59.96,21.59,57.24,9.54,25.35,28.08,53.53,22.21,1.01,49.95,67.31,60.04,19.3,55.21,58.99,50.79,67.49
	v3:	.double	78.18,76.61,79.74,26.55,39.01,88.02,35.06,93.82,73.18,54.53,75.73,43.84,67.54,97.59,29.13,25.33,22.83,34.54,64.51,14.88,31.07,67.01,82.48,88.77,6.78,87.13,62.04,39.27,15.07,44.22
	v4:	.double	44.57,37.73,44.98,82.39,68.38,44.07,90.36,1.65,19.86,65.37,63.66,38.31,22.43,18.78,48.28,27.49,50.45,24.95,69.16,16.81,76.56,39.15,27.65,9.93,78.45,74.77,3.88,89.41,69.26,58.45
	v5: .space	240		; byte per un double (64byte) * 60 posizioni
	v6: .space	240
	v7:	.space	240

.text

MAIN:
	
	xor		R11, R11, R11	; inizializzazione puntatore

	daddi	R20, R0, 10
	
LOOP:

	l.d		F1, v1(R11)
	l.d		F2, v2(R11)
	l.d		F3, v3(R11)
	l.d		F4, v4(R11)
	
	add.d	F10, F1, F2		; F10 = v1[i] + v2[i]
	mul.d	F11, F4, F1		; F11 = v4[i] * v1[i]
	add.d	F12, F2, F3		; F12 = v2[i] + v3[i]
	
	mul.d	F10, F10, F3	; F10 = (v1[i] + v2[i]) * v3[i]
	div.d	F6, F5, F11		; F6 = v5[i]/(v4[i] * v1[i])
	
	add.d	F5, F10, F4		; F5 = ((v1[i] + v2[i]) * v3[i]) + v4[i]
	mul.d	F12, F6, F12	; F12 = v6[i]* (v2[i] + v3[i])
	
	s.d		F6, v6(R11)		; load into v6[i]
	s.d		F5, v5(R11)		; load into v5[i]
	s.d		F12, v7(R11)	; load into v7[i]
	
	daddi	R11, R11, 8		; incremento puntatore
	
	l.d		F1, v1(R11)
	l.d		F2, v2(R11)
	l.d		F3, v3(R11)
	l.d		F4, v4(R11)
	
	add.d	F10, F1, F2		; F10 = v1[i] + v2[i]
	mul.d	F11, F4, F1		; F11 = v4[i] * v1[i]
	add.d	F12, F2, F3		; F12 = v2[i] + v3[i]
	
	mul.d	F10, F10, F3	; F10 = (v1[i] + v2[i]) * v3[i]
	div.d	F6, F5, F11		; F6 = v5[i]/(v4[i] * v1[i])
	
	add.d	F5, F10, F4		; F5 = ((v1[i] + v2[i]) * v3[i]) + v4[i]
	mul.d	F12, F6, F12	; F12 = v6[i]* (v2[i] + v3[i])
	
	s.d		F6, v6(R11)		; load into v6[i]
	s.d		F5, v5(R11)		; load into v5[i]
	s.d		F12, v7(R11)	; load into v7[i]
	
	daddi	R11, R11, 8		; incremento puntatore
	
	l.d		F1, v1(R11)
	l.d		F2, v2(R11)
	l.d		F3, v3(R11)
	l.d		F4, v4(R11)
	
	add.d	F10, F1, F2		; F10 = v1[i] + v2[i]
	mul.d	F11, F4, F1		; F11 = v4[i] * v1[i]
	add.d	F12, F2, F3		; F12 = v2[i] + v3[i]
	
	mul.d	F10, F10, F3	; F10 = (v1[i] + v2[i]) * v3[i]
	div.d	F6, F5, F11		; F6 = v5[i]/(v4[i] * v1[i])
	
	add.d	F5, F10, F4		; F5 = ((v1[i] + v2[i]) * v3[i]) + v4[i]
	mul.d	F12, F6, F12	; F12 = v6[i]* (v2[i] + v3[i])
	
	s.d		F6, v6(R11)		; load into v6[i]
	s.d		F5, v5(R11)		; load into v5[i]
	s.d		F12, v7(R11)	; load into v7[i]
	
	
	daddi	R20, R20, -1
	
	bnez	R20, LOOP
	daddi	R11, R11, 8		; incremento puntatore
	
	
	halt
