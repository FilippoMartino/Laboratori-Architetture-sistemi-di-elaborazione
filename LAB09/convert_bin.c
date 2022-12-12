#include <stdio.h>

void convert(int to_convert);

int main(int argc, char const *argv[]) {
	
	char vett_input[100] = {'0', '0', '0', '0', '2', '1', '1', '1', '2', '0', '1', '0', '0', '2', '0', '1', '3', '0', '1', '1', '4'};
	int count = 0;
	for (int i = 0; i < 100; i++){
		if (vett_input[i] == '2' || vett_input[i] == '3'){
			count ++;
			convert(count);
		}
		if (vett_input[i] == '4'){
			count ++;
			convert(count);
			break;
		}

	}

	return 0;
}

void convert(int to_convert){

	int bin[7];
	printf("Decimal to convert: %d\n", to_convert);

	for (int i = 6; i >= 0; i--){
		bin[i] = to_convert % 2;
		to_convert /= 2;
	}

	printf("Converted binary: ");
	for (int i = 0; i < 7; i++){
		printf("%d", bin[i]);
	}
	printf("\n");
	return;

}