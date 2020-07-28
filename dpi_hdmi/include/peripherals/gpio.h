/********************************************************************************/
/*							Constantinescu Sofian								*/
/*		www.pickit.ro								sofian@pickit.ro			*/
/********************************************************************************/

#ifndef	_P_GPIO_H
#define	_P_GPIO_H

// Includes ------------------------------------------------------------------- //
#include "base.h"

//------------------------------------------------------------------------------//
#define MAX_GPIO_NUM				54											// GPIO 0..53 are valid

//------------------------------------------------------------------------------//
#define GPFSEL0						*((volatile uint32_t*)(PBASE + 0x00200000))
#define GPFSEL1						*((volatile uint32_t*)(PBASE + 0x00200004))
#define GPFSEL2						*((volatile uint32_t*)(PBASE + 0x00200008))
#define GPFSEL3						*((volatile uint32_t*)(PBASE + 0x0020000C))
#define GPFSEL4						*((volatile uint32_t*)(PBASE + 0x00200010))
#define GPFSEL5						*((volatile uint32_t*)(PBASE + 0x00200014))
//------------------------------------------------------------------------------//
#define GPSET0						*((volatile uint32_t*)(PBASE + 0x0020001C))
#define GPSET1						*((volatile uint32_t*)(PBASE + 0x00200020))
//------------------------------------------------------------------------------//
#define GPCLR0						*((volatile uint32_t*)(PBASE + 0x00200028))
#define GPCLR1						*((volatile uint32_t*)(PBASE + 0x0020002C))
//------------------------------------------------------------------------------//
#define GPLEV0						*((volatile uint32_t*)(PBASE + 0x00200034))
#define GPLEV1						*((volatile uint32_t*)(PBASE + 0x00200038))
//------------------------------------------------------------------------------//
#define GPEDS0						*((volatile uint32_t*)(PBASE + 0x00200040))
#define GPEDS1						*((volatile uint32_t*)(PBASE + 0x00200044))
//------------------------------------------------------------------------------//
#define GPREN0						*((volatile uint32_t*)(PBASE + 0x0020004C))
#define GPREN1						*((volatile uint32_t*)(PBASE + 0x00200050))
//------------------------------------------------------------------------------//
#define GPFEN0						*((volatile uint32_t*)(PBASE + 0x00200058))
#define GPFEN1						*((volatile uint32_t*)(PBASE + 0x0020005C))
//------------------------------------------------------------------------------//
#define GPHEN0						*((volatile uint32_t*)(PBASE + 0x00200064))
#define GPHEN1						*((volatile uint32_t*)(PBASE + 0x00200068))
//------------------------------------------------------------------------------//
#define GPLEN0						*((volatile uint32_t*)(PBASE + 0x00200070))
#define GPLEN1						*((volatile uint32_t*)(PBASE + 0x00200074))
//------------------------------------------------------------------------------//
#define GPAREN0						*((volatile uint32_t*)(PBASE + 0x0020007C))
#define GPAREN1						*((volatile uint32_t*)(PBASE + 0x00200080))
//------------------------------------------------------------------------------//
#define GPAFEN0						*((volatile uint32_t*)(PBASE + 0x00200088))
#define GPAFEN1						*((volatile uint32_t*)(PBASE + 0x0020008C))
//------------------------------------------------------------------------------//
#define GPPUD						*((volatile uint32_t*)(PBASE + 0x00200094))
#define GPPUDCLK0					*((volatile uint32_t*)(PBASE + 0x00200098))
#define GPPUDCLK1					*((volatile uint32_t*)(PBASE + 0x0020009C))

//------------------------------------------------------------------------------//
// ENUMERATED FSEL REGISTERS ... BCM2835.PDF MANUAL see page 92
typedef enum {
	GPIO_INPUT		= 0b000,
	GPIO_OUTPUT		= 0b001,
	GPIO_ALTFUNC5	= 0b010,
	GPIO_ALTFUNC4	= 0b011,
	GPIO_ALTFUNC0	= 0b100,
	GPIO_ALTFUNC1	= 0b101,
	GPIO_ALTFUNC2	= 0b110,
	GPIO_ALTFUNC3	= 0b111
} GPIOMODE;

//------------------------------------------------------------------------------//
// ENUMERATED GPIO RESISTOR ... BCM2835.PDF MANUAL see page 101
typedef enum {
	NO_RESISTOR		= 0b00,
	PULLDOWN		= 0b01,
	PULLUP			= 0b10
} GPIO_FIX_RESISTOR;

#endif  /*_P_GPIO_H */
