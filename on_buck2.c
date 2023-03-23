#include <usart.h>
#include "app_device_custom_hid.h"
void on_buck2 ()
{
    //Escribe la referncia
    vo_ref_Write(buffer_user_usb);
    //Envía la orden de encendido
    while (BusyUSART());
            TXREG=COMMAND_ON_BUCK;
}
