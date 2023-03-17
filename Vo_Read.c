#include <stdint.h>
#include <usart.h>
#include "app_device_custom_hid.h"

uint16_t Vo_Read10bit(byte orden)
{
    nire_C_HID_DEM_COM=orden;
    uint16_t result;
count=1;
    while (BusyUSART());
    TXREG=nire_C_HID_DEM_COM;   
    
 while (count==1);      // Wait for conversion
      result = tensionSalidaBuck2;    //recive el byte ALTO de la Vo
      result <<=8; //lo prepara para recibir el byte bajo
count=1; 
      while (BusyUSART());
    TXREG=nire_C_HID_DEM_COM;
 while (count==1);      // Wait for conversion
            result |= tensionSalidaBuck2;   //tensionSalidaBuck2 es ahora el contenido del byte bajo del ADC
    return result;


}
