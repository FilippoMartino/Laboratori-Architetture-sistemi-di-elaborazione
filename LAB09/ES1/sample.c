#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"

/* funzioni assembly */
extern int translate_morse(char* vett_input,
										int vet_input_lenght, 
										char* vett_output, 
										int vet_output_lenght, 
										char change_symbol, 
										char space, 
										char sentence_end);

/*
	Funzione per la conversione del vettore in input 
*/
void c_led_setup(void);
/* Funzione per la conversione decimale-binario */
void convert(int to_convert);
										
/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in funct_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

/* vettore dichiarato globale */										
char	vett_input[100] = {'0', '0', '0', '0', '2', '1', '1', '1', '2', '0', '1', '0', '0', '2', '0', '1', '3', '1', '1', '2', '0', '0', '1', '2', '1', '0', '2', '1', '0', '0', '2', '1', '1', '1', '3', '0', '1', '1', '1', '1', '2', '0', '0', '1', '1', '1', '4'};	
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  
	/* definizione variabili */
	/* int 	vett_input[100] 	= {0, 0, 0, 0, 2, 1, 1, 1, 2, 0, 1, 0, 0, 2, 0, 1, 3, 1, 1, 2, 0, 0, 1, 2, 1, 0, 2, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 1, 1, 1, 2, 0, 0, 1, 1, 1, 4}; */

	char	vett_output[100];
	char	change_symbol 		= '2';
	char	space							= '3';
	char	sentence_end			= '4';
	
	SystemInit();
	LED_init();
	BUTTON_init();
	
	//translate_morse((char*) vett_input, 100, vett_output, 100, change_symbol, space, sentence_end);

	while(1);

}



void c_led_setup(void){
	
	/* variabile conteggio caratteri morse */
	int count = 0;
	int i;
	
	/* ciclo per ogni valore morse presente nel vettore */
	for (i = 0; i < 100; i++){
		if (vett_input[i] == '2'){
			count ++;
			convert(count);
		}
		if (vett_input[i] == '3'){
			count += 2;
			convert(count);
		}
		if (vett_input[i] == '4'){
			count ++;
			convert(count);
			break;
		}
	}
	return;
}

void convert(int to_convert){

	int i;
	/* vettore in cui salvare numero binario (8 bit per 8 led) */
	int bin[8];
	
	/* Spengo tutti i led */
	LED_Out(0);
	for (i = 0; i < 8; i++){
		bin[i] = to_convert % 2;
		to_convert /= 2;
	}

	/* Accendiamo i led a seconda del valore binario */
	for (i = 0; i < 8; i++){
		if (bin[i])
			LED_On(i);
	}
	
	return;
}