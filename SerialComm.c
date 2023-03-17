#include <usart.h>
#include <xc.h>

void InitializeUsart()
{
int spbrg=0;
//unsigned char config=0,baudconfig=0,i=0;
//CloseUSART();  //turn off usart if was previously on
// DSheet 15.0 
RCSTAbits.SPEN=1; // EUSART ENABLE
TRISCbits.TRISC6=0; //RC6 TRANSMIT OUTPUT
TRISCbits.TRISC7=1; //RC7RECEIVE INPUT

//-----configure USART -----
//config = USART_TX_INT_OFF & USART_RX_INT_ON& USART_ASYNCH_MODE &
// USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;
//-----SPBRG needs to be changed depending upon oscillator frequency-------
 //spbrg=48MHz/(16*9600)-1=312
spbrg=1210; 
//en realidad los baudios con los que sincroniza bien el dsPIC
//Aplicando la formula si con spbrg=265 son 11494 baudios el reloj esta
// a 47,288888 MHz(48 MHz) y para ajustar a 9600 spbrg=307
// and BRG is set to 1 in baudconfig BRG16 BAUD_16_BIT_RATE
//API configures USART for desired parameters
/**********************************************
//baudUSART()
 Clock Idle State:
BAUD_IDLE_CLK_HIGH Clock idle state is a high level
BAUD_IDLE_CLK_LOW Clock idle state is a low level
Baud Rate Generation:
BAUD_16_BIT_RATE 16-bit baud generation rate
BAUD_8_BIT_RATE 8-bit baud generation rate
RX Pin Monitoring:
BAUD_WAKEUP_ON RX pin monitored
BAUD_WAKEUP_OFF RX pin not monitored
Baud Rate Measurement:
BAUD_AUTO_ON Auto baud rate measurement enabled
BAUD_AUTO_OFF Auto baud rate measurement disabled
***********************************************/
//BAUDCONbits.ABDEN=0;
//BAUDCONbits.
baudUSART (BAUD_IDLE_CLK_LOW &
BAUD_16_BIT_RATE &
BAUD_WAKEUP_OFF &
BAUD_AUTO_OFF);
/*********************************************
//OpenUSART()
Interrupt on Transmission LIBRARY :
USART_TX_INT_ON Transmit interrupt ON
USART_TX_INT_OFF Transmit interrupt OFF
Interrupt on Receipt:
USART_RX_INT_ON Receive interrupt ON
USART_RX_INT_OFF Receive interrupt OFF
USART Mode:
USART_ASYNCH_MODE Asynchronous Mode
USART_SYNCH_MODE Synchronous Mode
Transmission Width:
USART_EIGHT_BIT 8-bit transmit/receive
USART_NINE_BIT 9-bit transmit/receive
Slave/Master Select*:
USART_SYNC_SLAVE Synchronous Slave mode
USART_SYNC_MASTER Synchronous Master mode
Reception mode:
USART_SINGLE_RX Single reception
USART_CONT_RX Continuous reception
Baud rate:
USART_BRGH_HIGH High baud rate
USART_BRGH_LOW Low baud rate
***********************************************/    
 OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON& USART_ASYNCH_MODE &
 USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH, spbrg);  
    // Enable priority interrupts
	RCONbits.IPEN = 1;
    PIE1bits.RCIE=1;
	// EUSART Receive is LOW priority interrupt
	IPR1bits.RCIP = 0;
	// enable all interrupts and peripheral interrupts
	RCSTAbits.CREN = 1; //enable el buffer de recepcion
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1; //enable  peripheral interrupts
	PIR1bits.RCIF=0; //Flag enable
    
    //di();  //macro de xc.h para deshabilitar interrupciones
} //Fin de InitializeUsart()
 
