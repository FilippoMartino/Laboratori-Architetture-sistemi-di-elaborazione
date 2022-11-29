#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int main(int argc, char const *argv[]){

	int ingredient_calories [] = {1, 30, 2, 70, 3, 200, 4, 42, 5, 81, 6, 20};
	int ingredient_quantity [] = {2, 50, 5, 3, 3, 10, 1, 5, 4, 8, 6, 30};

	int calories_ordered[SIZE] = {};
	int quantity_ordered[SIZE] = {};
	int temp_id;
	int temp_quant;
	int k;

	printf("Prima dell'ordinamento:\n");
	printf("ingredient_calories: ");
	for (int i = 0; i < SIZE * 2; i++)
		printf(" %d ", ingredient_calories[i]);
	printf("\n");
	printf("ingredient_quantity: ");
	for (int i = 0; i < SIZE * 2; i++)
		printf(" %d ", ingredient_quantity[i]);
	printf("\n");

	for (int i = 0; i < SIZE; i++){
		k = 0;
		for(int j = 1; j < SIZE; j++, k += 2){
			if (ingredient_calories[k + 1] < ingredient_calories[k + 3]){
				
				temp_id = ingredient_calories[k];
				temp_quant = ingredient_calories[k + 1];

				ingredient_calories[k] = ingredient_calories[k + 2];
				ingredient_calories[k + 1] = ingredient_calories[k + 3];

				ingredient_calories[k + 2] = temp_id;
				ingredient_calories[k + 3] = temp_quant;

				}
			}

		}

	for (int i = 0; i < SIZE; i++){
		k = 0;
		for(int j = 1; j < SIZE; j++, k += 2){
			if (ingredient_quantity[k + 1] < ingredient_quantity[k + 3]){
				
				temp_id = ingredient_quantity[k];
				temp_quant = ingredient_quantity[k + 1];

				ingredient_quantity[k] = ingredient_quantity[k + 2];
				ingredient_quantity[k + 1] = ingredient_quantity[k + 3];

				ingredient_quantity[k + 2] = temp_id;
				ingredient_quantity[k + 3] = temp_quant;

				}
			}

		}	

	for (int i = 0, k = 0; i < SIZE; i++, k += 2){
		calories_ordered[i] = ingredient_calories[k];
		quantity_ordered[i] = ingredient_quantity[k];
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