/********************************************************************************/
/*							Constantinescu Sofian								*/
/*		www.pickit.ro								sofian@pickit.ro			*/
/********************************************************************************/

// Includes ------------------------------------------------------------------- //
#include "utils.h"
#include "peripherals/gpio.h"

//------------------------------------------------------------------------------//
// Return true for success, false for any failure
bool Gpio_Setup (uint8_t Gpio, GPIOMODE Mode) {

	uint32_t CopyReg, BitMask;

	if ((Gpio < MAX_GPIO_NUM) && (Mode <= GPIO_ALTFUNC3)) {						// Check GPIO pin number and resistor mode is valid
		BitMask = ((Gpio % 10) * 3);											// Create bit mask
		switch (Gpio / 10) {
			case 0x00:
				CopyReg = GPFSEL0;
				CopyReg &= ~(7 << BitMask);										// Clear GPIO mode bits for that port
				CopyReg |= (Mode << BitMask);									// Logical OR GPIO mode bits
				GPFSEL0 = CopyReg;
				break;
			case 0x01:
				CopyReg = GPFSEL1;
				CopyReg &= ~(7 << BitMask);	
				CopyReg |= (Mode << BitMask);
				GPFSEL1 = CopyReg;
				break;
			case 0x02:
				CopyReg = GPFSEL2;
				CopyReg &= ~(7 << BitMask);	
				CopyReg |= (Mode << BitMask);
				GPFSEL2 = CopyReg;
				break;
			case 0x03:
				CopyReg = GPFSEL3;
				CopyReg &= ~(7 << BitMask);	
				CopyReg |= (Mode << BitMask);
				GPFSEL3 = CopyReg;
				break;
			case 0x04:
				CopyReg = GPFSEL4;
				CopyReg &= ~(7 << BitMask);	
				CopyReg |= (Mode << BitMask);
				GPFSEL4 = CopyReg;
				break;
			case 0x05:
				CopyReg = GPFSEL5;
				CopyReg &= ~(7 << BitMask);	
				CopyReg |= (Mode << BitMask);
				GPFSEL5 = CopyReg;
				break;
			default:
				return false;
		}
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------//
// Return true for success, false for any failure
bool Gpio_Output (uint8_t Gpio, bool On) {

	uint32_t PinMask;

	if (Gpio < MAX_GPIO_NUM) {													// Check GPIO pin number valid, return false if invalid
		PinMask = (1 << (Gpio % 32));											// Create mask bit
		if (On)	{																// true means set, false means clear
			if (Gpio < 32) {
				GPSET0 = PinMask;
			}
			else {
				GPSET1 = PinMask;
			}
		}
		else {
			if (Gpio < 32) {
				GPCLR0 = PinMask;
			}
			else {
				GPCLR1 = PinMask;
			}

		}
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------//
// Return true = GPIO input high, false = GPIO input low
bool Gpio_Input (uint8_t Gpio) {

	uint32_t PinRead;

	if (Gpio < MAX_GPIO_NUM) {													// Check GPIO pin number valid, return false if invalid
		if (Gpio < 32) {
			PinRead = GPLEV0;													// Read pin level
		}
		else {
			PinRead = GPLEV1;
		}
		if (PinRead & (1 << (Gpio % 32))) {
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------//
// Set the GPIO port number resistors to pull up/pull down
// Return true for success, false for any failure
bool Gpio_Resistor (uint8_t Gpio, GPIO_FIX_RESISTOR Resistor) {

	uint32_t PinMask;

	if ((Gpio < MAX_GPIO_NUM) && (Resistor <= PULLUP)) {						// Check GPIO pin number and resistor is valid
		PinMask = (1 << (Gpio % 32));											// Create mask bit
		GPPUD = Resistor;														// Set fixed resistor request to PUD register
		delay(150);
		if (Gpio < 32) {
			GPPUDCLK0 = PinMask;												// Set the PUD clock bit register
		}
		else {
			GPPUDCLK1 = PinMask;
		}
		delay(150);
		GPPUD = 0;																// Clear GPIO resister setting
		if (Gpio < 32) {
			GPPUDCLK0 = 0;														// Clear PUDCLK from GPIO
		}
		else {
			GPPUDCLK1 = 0;
		}
		return true;
	}
	return false;
}
