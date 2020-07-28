/********************************************************************************/
/*							Constantinescu Sofian								*/
/*		www.pickit.ro								sofian@pickit.ro			*/
/********************************************************************************/
#ifndef _GPIO_H
#define _GPIO_H

//------------------------------------------------------------------------------//
#include "peripherals/gpio.h"

//------------------------------------------------------------------------------//
bool Gpio_Setup (uint8_t Gpio, GPIOMODE Mode);
bool Gpio_Output (uint8_t Gpio, bool On);
bool Gpio_Input (uint8_t Gpio);
bool Gpio_Resistor (uint8_t Gpio, GPIO_FIX_RESISTOR Resistor);


#endif	/*_GPIO_H */

