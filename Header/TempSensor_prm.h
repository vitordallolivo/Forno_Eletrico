/*
 * TempSensor_prm.h
 *
 *  Created on: 03/10/2017
 *      Author: MAASDN
 */

#ifndef TEMPSENSOR_PRM_H_
#define TEMPSENSOR_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
//On board Temp Sensor configuration
// Select ENABLED for sensor that will be used otherwise DISABLED
#define USE_TEMP_SENSOR_1		DISABLED	
#define USE_TEMP_SENSOR_2		ENABLED


//Use table below to link each Temperature Sensor input configured as enabled with its respective Analog Input) as per 
// enumeration defined in HAL.h
#define TEMP_SENSOR_CONFIG \
	{\
		 POT_INT, 	/*TEMP_SENSOR_1*/\
		 POT_EXT,  	/*TEMP_SENSOR_2*/\
    }



#endif /* TEMPSENSOR_PRM_H_ */

