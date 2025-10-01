/*
 * OvenTempControl.c
 *
 *  Created on: 03/10/2017
 *      Author: MAASDN
 */
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\TempSensor.h"
#include "..\Header\OvenTempControl.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------


typedef struct
{
	unsigned short int Temp_On;
	unsigned short int Temp_Off;
}OVEN_TEMP_RANGE_TYPE;


OVEN_TEMP_CONTROL_LEVELS_TYPE Current_Level;
															                /*  Temp On         Temp Off   */
const OVEN_TEMP_RANGE_TYPE TEMP_CONTROL_PARAMETERS[NUM_OF_TEMP_LEVELS] =  {  	{TEMP_ON_MIN, 	TEMP_OFF_MIN},\
																				{TEMP_ON_MED, 	TEMP_OFF_MED},\
																				{TEMP_ON_MAX, 	TEMP_OFF_MAX},\
																				{0, 	0},\
																		  };


//-------------------------------------- Global Variables ----------------------------------------------------------------

OVEN_TEMP_CONTROL_STATE_TYPE Oven_TempControl_State;  //
//unsigned char TempControl_Enable;
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


//---------------------------------------------------------------------------------------------------------------------
void OvenTempControl__Initialize(void)
{
	Oven_TempControl_State = OVEN_INSIDE_RANGE;   
	Current_Level = TEMP_LEVEL_OVEN_OFF;
	//TempControl_Enable = DISABLED;
}


//************************************************************
// Esta função liga ou desliga o resistor de aquecimento
// em função da temp ON e temp OFF de cada level (MIN, MED ou MAX)
// ************************************************************



void OvenTempControl__Handler(void)
{
	unsigned short int temp_on;
	unsigned short int temp_off;
	unsigned short int current_temp;

	temp_on = TEMP_CONTROL_PARAMETERS[Current_Level].Temp_On;
	temp_off = TEMP_CONTROL_PARAMETERS[Current_Level].Temp_Off;
	current_temp = TempSensor__GetCelsius(OVEN_RELATED_SENSOR);

	if(Current_Level == TEMP_LEVEL_OVEN_OFF)
	{
		TURN_HEATER_OFF();
	}
	else
	{
		switch(Oven_TempControl_State)
		{
		case OVEN_INSIDE_RANGE:                    
			TURN_HEATER_OFF();
			if(current_temp <= temp_on)
			{
				Oven_TempControl_State = OVEN_HEATING;
			}
			break;

		case OVEN_HEATING:
			TURN_HEATER_ON();
			if(current_temp >= temp_off)
			{
				Oven_TempControl_State = OVEN_INSIDE_RANGE;
			}

			break;
		}
	}
}


//*****************************************************
// Esta função atualiza a variável global Current_Level

// ****************************************************

void OvenTempControl__SetLevel(OVEN_TEMP_CONTROL_LEVELS_TYPE level)
{
	Current_Level = level;
}

//*************************************************************

// Esta função retorna se a temperatura está dentro do range ou
// o resistor ligado.
// ************************************************************

OVEN_TEMP_CONTROL_STATE_TYPE OvenTempControl__GetState(void)
{
	return Oven_TempControl_State; 
}

//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

