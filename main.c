/*
 * File:   main.c
 * Author: peio.gil
 *
 * Created on 23 de febrero de 2023, 14:47
 */


#include <xc.h>
#include "system.h"
#include "usb.h"
#include "usb_device_hid.h"
#include "app_device_custom_hid.h"
#include "app_led_usb_status.h"
#include <usart.h>
#include "serial.h"
MAIN_RETURN main(void)
{
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);
    USBDeviceInit();
    USBDeviceAttach();
    InitializeUsart();
    //TIMER0_SetConfiguration();
// ***************************************************************************** 
//    Initializes settings of the TC78H to default.
    //IniSettingsDefault();
// *****************************************************************************
//Select default 18f4550 pin modes for hardware connections con  el driver TC78H
// *****************************************************************************
    //Pin_SetUp_PortB_Driver ();
    //controlModeSelect(); //se le llama from el PC ahora para hacer pruebas
    while(1)
    {
        SYSTEM_Tasks();

        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            USBDeviceTasks();
        #endif

        //Application specific tasks
        APP_DeviceCustomHIDTasks();

    }//end while
}//end main

/*******************************************************************************
 End of File
*/