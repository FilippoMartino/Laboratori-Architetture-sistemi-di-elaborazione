#include<stdio.h>


/* Prototipo funzione assembler, riceve 6 interi e ne restituisce 1 */
extern int check_square(int x, int y, int r);
extern float my_division(float* a, float* b);

extern int _ROWS;
extern int	_COLUMNS;
extern int 	_Matrix_Coordinates[11][22];

int main(void){

	/* devo recuperare le informazioni sulla matrice dal file assembly */
	
	
	
	int i, j;
	float r = 5, sum = 0, pi;


	for (i = 0; i < _ROWS; i++){
			for(j = 0; j < _COLUMNS; j+=2){
				sum += check_square(_Matrix_Coordinates[i][j], _Matrix_Coordinates[i][j + 1], r);
			}
	}
	r = r * r;
	pi = my_division(&sum, &r);
	__asm__("svc 0xCA");
	__asm__("svc 0xFE");

	while(1);
}
