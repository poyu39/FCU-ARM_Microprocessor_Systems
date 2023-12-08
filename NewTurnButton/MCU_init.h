// Define Clock source
#define MCU_CLOCK_SOURCE
#define MCU_CLOCK_SOURCE_HXT  // HXT, LXT, HIRC, LIRC
#define MCU_CLOCK_FREQUENCY   50000000  //Hz

// PWM1 for turn button
#define MCU_INTERFACE_PWM1
#define PWM1_CH01_CLOCK_SOURCE_HXT // HXT, LXT, HCLK, HIRC
#define PWM1_CH23_CLOCK_SOURCE_HXT // HXT, LXT, HCLK, HIRC
#define PIN_PWM1_CH0_PB11
#define PIN_PWM1_CH1_PE5
#define PIN_PWM1_CH2_PE0
#define PIN_PWM1_CH3_PE1

#define MCU_INTERFACE_ADC
#define ADC_CLOCK_SOURCE_HXT  // HXT, LXT, PLL, HIRC, HCLK
#define ADC_CLOCK_DIVIDER     1
#define PIN_ADC7_PA7
