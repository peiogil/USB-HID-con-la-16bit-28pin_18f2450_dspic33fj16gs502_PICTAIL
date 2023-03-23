/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_hid.h"
#include <string.h>
#include <stdbool.h>
#include "system.h"
//#include "timers.h"
//#include "SparkFun_ProDriver_TC78H670FTG_Library.h"
#include "app_device_custom_hid.h"
#include <usart.h>

/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[64];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[64];
        #pragma udata

    #elif defined(__XC8)
        unsigned char ReceivedDataBuffer[64] HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[64] HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[64];
    unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;

 //bool TIMER0_CONTANDO=false;
//extern PRODRIVERSettings settings;

/** FUNCTIONS ******************************************************/

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize()
{
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP,(uint8_t*)&ReceivedDataBuffer[0],64);
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks()
{   
    //enum CUSTOM_HID_DEMO_COMMANDS nire_C_HID_DEM_COM;
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }
    
    //Check if we have received an OUT data packet from the host
    if(HIDRxHandleBusy(USBOutHandle) == false)
    {   
        //We just received a packet of data from the USB host.
        //Check the first uint8_t of the packet to see what command the host
        //application software wants us to fulfill.
       nire_C_HID_DEM_COM=ReceivedDataBuffer[0];
        switch(nire_C_HID_DEM_COM)				//Look at the data the host sent, to see what kind of application specific command it sent.
        {
            /*
            case COMMAND_TOGGLE_LED:  //Toggle LEDs command
                LED_Toggle(LED_USB_DEVICE_HID_CUSTOM);
            break;
            
            case COMMAND_GET_BUTTON_STATUS_S2:  //Get push button state
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    ToSendDataBuffer[0] = COMMAND_GET_BUTTON_STATUS_S2;				//Echo back to the host PC the command we are fulfilling in the first uint8_t.  In this case, the Get Pushbutton State command.
                    ToSendDataBuffer[1] = 0x00;
                  
                    if(BUTTON_IsPressed(BUTTON_S2) == false)	//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
                    {
                            ToSendDataBuffer[1] = 0x01;
                    }
                    else									//sw2 must be == 0, pushbutton is pressed and overpowering the pull up resistor
                    {
                            ToSendDataBuffer[1] = 0x00;
                    }
                      
                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
           break; 
           */
        /*
            case COMMAND_TOGGLE_LED_D4:  //Toggle LEDs command
               LED_Toggle(LED_D4_TEST);
            break;
            //Código nuevo  usuario
            //Cuando se pulsa el botón S3 desde el PC en respuesta enciende el Led D4
            case COMMAND_GET_BUTTON_STATUS_S3:  //Get push button state
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    ToSendDataBuffer[0] = 0x82;				//Echo back to the host PC the command we are fulfilling in the first uint8_t.  In this case, the Get Pushbutton State command.
                    if(BUTTON_IsPressed(BUTTON_S3) == false)	//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
                    {
                            ToSendDataBuffer[1] = 0x01;
                    }
                    else									//sw3 must be == 0, pushbutton is pressed and overpowering the pull up resistor
                    {
                            ToSendDataBuffer[1] = 0x00;
                    }
                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
            break;
            */    
         case COMMAND_READ_V0:
         {
         uint16_t vo=0;
         //Check to make sure the endpoint/buffer is free before we modify the contents
                    if(!HIDTxHandleBusy(USBInHandle))
                    {
                        vo = Vo_Read10bit(COMMAND_READ_V0);
            
                        ToSendDataBuffer[0] = COMMAND_READ_V0;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
                        ToSendDataBuffer[1] = (uint8_t)vo; //LSB
                        ToSendDataBuffer[2] = vo >> 8;     //MSB


                        //Prepare the USB module to send the data packet to the host
                        USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                    }
         }
         break;
            case COMMAND_REF_VO:
            {
               
    //if(!HIDTxHandleBusy(USBInHandle)) // anulada este condición es para meter datos al host
                
                    buffer_user_usb [0]=nire_C_HID_DEM_COM;
                    buffer_user_usb [1]=ReceivedDataBuffer[1];
                    buffer_user_usb [2]=ReceivedDataBuffer[2];
                    vo_ref_Write(buffer_user_usb);
                    
              
                
            }   
         break;
         
            case  COMMAND_ON_BUCK:
            {
                //Lo primero es enviar la referencia de tensión antes de encender    
                buffer_user_usb [0]=COMMAND_REF_VO;
                    buffer_user_usb [1]=ReceivedDataBuffer[1]; //la referencia de tensión byte L
                    buffer_user_usb [2]=ReceivedDataBuffer[2]; //la referencia de tensión byte H
                    on_buck2();
                
            }
            break;
            case  COMMAND_OFF_BUCK:
            {
                while (BusyUSART());
            TXREG=COMMAND_OFF_BUCK;
            }
            break;
             }
        //Re-arm the OUT endpoint, so we can receive the next OUT data packet 
        //that the host may try to send us.
        USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer[0], 64);
    }
}

