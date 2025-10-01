/*
 * OvenTempControl_prm.h
 *
 *  Created on: 03/10/2017
 *      Author: MAASDN
 */

#ifndef OVENTEMPCONTROL_PRM_H_
#define OVENTEMPCONTROL_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Hal.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

//Configures the related sensor to be used on Temperature Control
#define OVEN_RELATED_SENSOR		TEMP_SENSOR_2      // TEMP_SENSOR_1

//MIN Set Point
#define TEMP_ON_MIN		180 //°C
#define TEMP_OFF_MIN	210 //°C

//MED Set Point
#define TEMP_ON_MED		250 //°C
#define TEMP_OFF_MED	300 //°C

//MAX Set Point
#define TEMP_ON_MAX		320 //°C
#define TEMP_OFF_MAX	380 //°C

//Define the loads to turn ON and OFF on by temperature control
#define TURN_HEATER_ON()  Hal__SetLed(LED_3, ACENDE_LED);
#define TURN_HEATER_OFF() Hal__SetLed(LED_3, APAGA_LED);

#endif /* OVENTEMPCONTROL_PRM_H_ */
