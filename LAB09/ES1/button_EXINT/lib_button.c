
#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {
  
  /*
    La maggior parte della configurazione che si va a fare sui "piedini" viene fatta mediante
    il modulo "pin connect", ovvero LPC_PINCON 
    PINSEL4 è un registro dedicato ai dispositivi di input/output, led e switch:
    lo utilizzeremo spesso per gestire i pin della porta 2; ad esempio dalla
    porta 2 abbiamo i pin da 1 a 9 dedicati al controllo dei led, mentre i pin 10, 11 e 12 per il
    controllo dei pulsanti
    
    La configurazione su GPIO (General Purpose Input Output) indica che i pin 10, 11 e 12 siano da
    intendersi come input.
    
    La gestione del singolo pin (a noi interessa poter specificare e controllare il singolo pulsante
    o il singolo led), viene fatta specificando il giusto indirizzo: nel manuale, alla voce PINSEL4
    troviamo i bit dedicati ad ogni pin:
    - per il primo pulsante, il P.10, abbiamo i bit 20 e 21
    - "" secondo, P.11, abbiamo i bit 22 e 23
    - "" terzo, P.12, abbiamo 24 e 25
    
    Di consegnuenza la configurazione di seguito si limita a dire:
    utilizza LPC_PINCON->PINSEL4 per specificare il registro dell GPIO, di seguito
    facciamo delle operazioni bitwise in c per specificare quali bit configurare:
    "|= (1 << 20)" è una OR bit a bit con PINSEL4 shiftata di 20 posizioni, in modo
    che l'indirizzo risultante sia quello del primo pulsante ed avvenga la configurazione
    Attenzione: avremo
    Bits:   ...|23|22|21|20|19|18|...
    Value:  ...|x |x |0 |1 |x | x|...
    Quesa configurazione risultante dall'operazione bitwise OR va bene in quanto nel manuale
    viene specficata necessario per l'identificazione il valore "01"; nel caso venisse 
    richiesta una "11" avremo dovuto fare un'operazione differente
    
    Tutto questo solo per specificare che "|= (1 << 20)" serve a specifiare su quale pin
    eseguire la configurazione
    
    Passando a GPIO2: questo è il registro della DIREZIONE; l'operazione "&= ~(1 << 10)"
    consiste nel prendere 1 come valore, shiftarlo di 10 posizioni a sinistra e negare
    il tutto, ottenendo qualcosa del genere (ad esempio su 16 bits:
    |1|1|1|1|1|1|0|1|1|1|1|1|1|1|1|1|
    Facendo una and con il registro FIODIR alla posizione 10 otterremo uno 0 (anche questo
    indirizzo viene specificato nelle tabelle di configurazione)
    
    Facciamo quindi l'abilitazione e configurazione come input per i pin 10, 11, 12 ossia
    ai tre pulsanti
 
  */
  
  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  /*
    Setting della modalità di interrupt: in parole povere specifichiamo in che modo l'hardware
    dedicato all'input e in questo caso ai segnali di interrupt (legati ai pulsanti) debba
    attivarsi, con sensibilità si intende ad esempio un attivazione sul fronte di salita
    o discesa del clock, si potrebbe inoltre configurare per restare sempre attivo una volta
    ricevuto l'interrupt o disattivarsi.
    La configurazione specificata consiste in sensibilità sul fronte di discesa del clock;
    segnale finito
  */
  
  LPC_SC->EXTMODE = 0x7;
  
  /*
    Abilitazione delle interruzzioni, sovrascrive quello già implementato "weak" dal sistema
  */

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
}
