// Define Clock source
#define MCU_CLOCK_SOURCE
#define MCU_CLOCK_SOURCE_HXT          // HXT, LXT, HIRC, LIRC
#define MCU_CLOCK_FREQUENCY 50000000  // Hz

// Define MCU Interfaces
// SPI3 for LCD
#define MCU_INTERFACE_SPI3
#define SPI3_CLOCK_SOURCE_HCLK  // HCLK, PLL
#define PIN_SPI3_SS0_PD8
#define PIN_SPI3_SCLK_PD9
#define PIN_SPI3_MISO0_PD10
#define PIN_SPI3_MOSI0_PD11

// Timer 0
#define MCU_INTERFACE_TMR0
#define TMR0_CLOCK_SOURCE_HXT  // HXT, LXT, HCLK, EXT, LIRC, HIRC

// Timer 1
#define MCU_INTERFACE_TMR1
#define TMR1_CLOCK_SOURCE_HXT  // HXT, LXT, HCLK, EXT, LIRC, HIRC


// Timer 2
#define MCU_INTERFACE_TMR2
#define TMR2_CLOCK_SOURCE_HXT  // HXT, LXT, HCLK, EXT, LIRC, HIRC


// // Timer 3
// #define MCU_INTERFACE_TMR3
// #define TMR3_CLOCK_SOURCE_HXT  // HXT, LXT, HCLK, EXT, LIRC, HIRC

// PB15
#define MCU_INTERFACE_INT1_PB15

// WDT
// #define MCU_INTERFACE_WDT
// #define WDT_CLOCK_SOURCE_LIRC  // LIRC, HCLK_DIV2048, LXT
// #define WWDT_CLOCK_SOURCE_LIRC  // LIRC, HCLK_DIV2048, LXT
// #define WWDT_CLOCK_SOURCE_LIRC  // LIRC, HCLK_DIV2048, LXT
