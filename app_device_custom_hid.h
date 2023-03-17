/* 
 * File:   app_device_custom_hid.h
 * Author: peio.gil
 *
 * Created on 23 de febrero de 2023, 14:04
 */

#ifndef APP_DEVICE_CUSTOM_HID_H
#define	APP_DEVICE_CUSTOM_HID_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
#include <stdint.h>
//#include "18F2450_importado/typedefs.h"
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
void APP_DeviceCustomHIDInitialize(void);

/*********************************************************************
* Function: void APP_DeviceCustomHIDStart(void);
*
* Overview: Starts running the Custom HID demo.
*
* PreCondition: The device should be configured into the configuration
*   that contains the custome HID interface.  The APP_DeviceCustomHIDInitialize()
*   function should also have been called before calling this function.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDStart(void);

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
typedef unsigned char byte;

void APP_DeviceCustomHIDTasks(void);
uint16_t Vo_Read10bit(byte);
/** DEFINITIONS OF COMMANDS ****************************************/
enum CUSTOM_HID_DEMO_COMMANDS

{
    
    COMMAND_ON_BUCK=0xA0, 
    COMMAND_OFF_BUCK=0xA1,
    COMMAND_REF_VO=0XA2,
    COMMAND_READ_V0=0xA3,
            
} nire_C_HID_DEM_COM;


byte tensionSalidaBuck2,ordenUSB, count;
byte vo_ref[3];

void vo_ref_Write(byte *);
#endif	/* APP_DEVICE_CUSTOM_HID_H */