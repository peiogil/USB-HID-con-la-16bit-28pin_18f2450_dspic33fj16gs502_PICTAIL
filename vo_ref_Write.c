#include <stdint.h>
#include <usart.h>
#include "app_device_custom_hid.h"
void vo_ref_Write (byte*buffer)
{

nire_C_HID_DEM_COM=*buffer;
count=1;
while (BusyUSART());
    TXREG=nire_C_HID_DEM_COM;   
while (count==1);      // Wait for conversion
count=1;
 while (BusyUSART());
TXREG=*(buffer+1);               //env�a el byte bajo
while (count==1); // Wait for conversion
//count=1;
while (BusyUSART());
TXREG=*(buffer+2);               //env�a el byte alto y vuelve a la llamada
//while (count==1);      // no va a haber respuesta
return;
}