// Blink example for usage low level api to digital write pins.
// https://github.com/iotool/IOTool_ATtiny2313_LowLevel
// 
// 2020-07-08  RoHa  100 byte ROM (5%), 0 byte RAM (0%) 

#define F_CPU             (1000000UL) // 1.0 MHz
#define IOTOOL__F_CPU      1000000UL  // 1.0 MHz CPU 
#include "iotool_attiny2313_lowlevel.h"

void loop();

int main() 
{
  // --- setup ---
  PINMODE_PD5_OUTPUT;     // pinMode(OUTPUT)

  // --- loop ---
  while(1)                // forever
  {
    loop();               
  }
}

void loop() 
{
  DELAY_1S;
  DIGITALWRITE_PD5_HIGH;
  DELAY_1S;
  DIGITALWRITE_PD5_LOW;
}
