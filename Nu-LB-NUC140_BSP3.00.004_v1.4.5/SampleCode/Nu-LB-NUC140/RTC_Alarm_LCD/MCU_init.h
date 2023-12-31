//Define Clock source
#define MCU_CLOCK_SOURCE      
#define MCU_CLOCK_SOURCE_HXT  // HXT, LXT, HIRC, LIRC
#define MCU_CLOCK_SOURCE_LXT
#define MCU_CLOCK_FREQUENCY   50000000  //Hz

//Define MCU Interfaces
// RTC
#define MCU_INTERFACE_RTC
// LCD
#define MCU_INTERFACE_SPI3
#define SPI3_CLOCK_SOURCE_HCLK // HCLK, PLL
#define PIN_SPI3_SS0_PD8
#define PIN_SPI3_SCLK_PD9
#define PIN_SPI3_MISO0_PD10
#define PIN_SPI3_MOSI0_PD11
// EEPROM
#define MCU_INTERFACE_I2C1
#define I2C1_CLOCK_FREQUENCY  400000 //Hz
#define PIN_I2C1_SCL_PA11      
#define PIN_I2C1_SDA_PA10
