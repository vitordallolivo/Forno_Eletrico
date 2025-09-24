/*
 * Adc_prm.h
 *
 * Created: 24/09/2025 08:04:49
 *  Author: 12279036932
 */ 


#ifndef ADC_PRM_H_
#define ADC_PRM_H_

//On board LEDs configuration
// Select ENABLED for LEDs that will be used otherwise DISABLED

#define ENABLED   1
#define DISABLED  0

#define CONFIG_AD_CH0     DISABLED	 // potenciômetro da placa multi function
#define CONFIG_AD_CH1     DISABLED
#define CONFIG_AD_CH2     DISABLED
#define CONFIG_AD_CH3     DISABLED
#define CONFIG_AD_CH4     DISABLED
#define CONFIG_AD_CH5     ENABLED    // potenciômetro externo
#define CONFIG_AD_CH6     DISABLED
#define CONFIG_AD_CH7     DISABLED

#define ADC_SAMPLING_TIME	50 //(0 to 255)



#endif /* ADC_PRM_H_ */