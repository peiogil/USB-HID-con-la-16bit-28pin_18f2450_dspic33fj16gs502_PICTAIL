
#include <usart.h>
#include "app_device_custom_hid.h"
#include <xc.h>

/** V E C T O R  R E M A P P I N G *******************************************/
/*
extern void _startup (void);        // See c018i.c in your C18 compiler dir

#pragma idata 
char TRXcount=0;

#pragma udata 

//FIFO receiveBuffer;
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800

void _reset (void)
{
  _asm goto _startup _endasm

}
#pragma code

//Acciones cuando se produzcan interrupciones
#pragma code _HIGH_INTERRUPT_VECTOR = 0x000008
void _high_ISR (void)
{
	_asm 
	goto SerialReceiveInterrupt 
	_endasm
;
}
#pragma code _LOW_INTERRUPT_VECTOR = 0x000018
void _low_ISR (void)
{
}
#pragma code
#pragma interrupt SerialReceiveInterrupt
// Interrupt service routine when receiving via serial line
*/
//solo funciona la config. con int. de bajo nivel
//si se programa para high_priority las ignora.
//las config. de las isr es muy diferente al c18
//esta sintaxis es para la versions xc8 v1.00.
//hay otras que ahora no sé para que versiones son válidas
//En MPLAB® XC8 C Compiler User?s Guide for PIC® MCU
//Revision C (February 2020)
//p.e. void __interrupt(low_priority) tcInt(void)
// con este compilador da error
void interrupt low_priority SerialReceiveInterrupt(void)
//void interrupt SerialReceiveInterrupt(void)
//void interrupt  SerialReceiveInterrupt(void)

{
    byte limpiarRX;
//ADI ARAKATZEN DENEAN BREAK-AREKIN EZ DU ONGI EGITEN
//GELDITZEN DENEAN IKUSI DA ONGI DAGOELA
 //Disable all interrupts
	//INTCONbits.GIE = 0;

	// if serial interrupt
	if(PIR1bits.RCIF && PIE1bits.RCIE)
 		{


switch(nire_C_HID_DEM_COM)
{

case COMMAND_REF_VO:
    //La rutina vo_ref_write 1º envía el comando de vo_referencia
    //en respuesta dspic provoca una terrupción. Haciendo count=0 permite que
    // la rutina vo:_ref siga el proceso de enviar 2 datos
    limpiarRX=ReadUSART();
    count=0;
break;

//0xA3 lectura de la tensión de salida se le llama 2 veces porque son
//10 bits. La llamada doble se gestiona desde la función ServiceRequests en Vo_Reac.c
case COMMAND_READ_V0:
tensionSalidaBuck2=ReadUSART(); //aquí sí que sirve la lectura del registro
		count=0;
break;
default:
        limpiarRX=ReadUSART();
/*
//coeficientes del regulador 5 coef x2 bytes=10 TRXcount
case 0xA4:
limpiarRX=ReadUSART(); //limpiar el registro leyendolo, si no se bloquea
if (TRXcount<10){
TRXcount++;
TXREG=receiveBuffer.buffer[TRXcount];
}
else{
TRXcount=0;
finParamReg=0;
}

break;

case 0xA5:
//protocolo enviar referencia
//1) Se envía la identificacion de la orden rectSincrona=0xA5 al dsPIC esto provoca una int en el dsPIC
//2) Como respuesta a la int el dsPIC a traves del TRX de su UART responde que le ha llegado y provoca esta interrupción.
//3) Ahora desde el 18f2450 se le envía el contenido del byte de orden byte=1 =>rect sincrona byte=0 rect NO sincrona.
limpiarRX=ReadUSART();  //limpiar el registro leyendolo, sino se bloquea
TXREG=receiveBuffer.buffer[1];
break;
*/
}
 
/*
	if(RCSTAbits.OERR==1)
	{
 
				RCSTAbits.CREN=0;
				RCSTAbits.CREN=1;
	}
*/
	
	// Enable interrupts


}
    PIR1bits.RCIF=0;
    return;
	//INTCONbits.GIE = 1;  //las interrupciones NO se habilitan dentro de la ISR
    //Esto puede dar lugar a un funcionamiento ineseperado del programa.
    // con la instrucción return al mismo tiempo se habilitan las interrupciones
}


