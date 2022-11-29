#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int main(int argc, char const *argv[]){

	int ingredient_calories [] = {1, 30, 2, 70, 3, 200, 4, 42, 5, 81, 6, 20};
	int ingredient_quantity [] = {2, 50, 5, 3, 3, 10, 1, 5, 4, 8, 6, 30};

	int calories_ordered[SIZE] = {};
	int cal_quant[SIZE] = {};

	int quantity_ordered[SIZE] = {};
	int quant_quant[SIZE] = {};

	int temp;
	int k;

	/* estrazione id calorie e quantità (uso vettore quantity oredered da appoggio per risp variab */
	for (int i = 0, k = 0; i < SIZE; i++, k += 2){
		calories_ordered[i] = ingredient_calories[k];
		cal_quant[i] 		= ingredient_calories[k + 1];
		quantity_ordered[i] = ingredient_quantity[k];
		quant_quant[i] 		= ingredient_quantity[k + 1];
	}



	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE - 1; j++){

			/* controllo sulle calorie */

			if (cal_quant[j] < cal_quant[j + 1]){
				
				/* swap delle calorie (quantità) */
				temp = cal_quant[j];
				cal_quant[j] = cal_quant[j + 1];
				cal_quant[j + 1] = temp;

				/* swap degli id */
				temp = calories_ordered[j];
				calories_ordered[j] = calories_ordered[j + 1];
				calories_ordered[j + 1] = temp;

			}

			/* controllo sulle quantità */

			if (quant_quant[j] < quant_quant[j + 1]){
				
				/* swap delle quantità (quantità) */
				temp = quant_quant[j];
				quant_quant[j] = quant_quant[j + 1];
				quant_quant[j + 1] = temp;

				/* swap degli id (quantità) */
				temp = quantity_ordered[j];
				quantity_ordered[j] = quantity_ordered[j + 1];
				quantity_ordered[j + 1] = temp;

			}
		}
	}
	

	printf("calories_ordered: [");
	for(int i = 0; i < SIZE - 1; i++)
		printf("%d, ", calories_ordered[i]);
	printf("%d]\n", calories_ordered[SIZE - 1]);

	printf("quantity_ordered: [");
	for(int i = 0; i < SIZE - 1; i++)
		printf("%d, ", quantity_ordered[i]);
	printf("%d]\n", quantity_ordered[SIZE - 1]);


	return 0;
}