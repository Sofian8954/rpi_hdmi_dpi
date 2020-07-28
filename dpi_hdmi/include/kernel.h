/********************************************************************************/
/*							Constantinescu Sofian								*/
/*		www.pickit.ro								sofian@pickit.ro			*/
/********************************************************************************/
#ifndef	_KERNEL_H
#define	_KERNEL_H
// Includes ------------------------------------------------------------------- //
#include "peripherals/base.h"
#include "peripherals/gpio.h"

//------------------------------------------------------------------------------//
#define HDMI_WIDTH					1280
#define HDMI_HEIGHT					1024

//------------------------------------------------------------------------------//
#define FB_ONE						0x10000000
#define FB_TWO						0x10100000
#define FB_THREE					0x10200000
#define FB_FOUR						0x10300000

//------------------------------------------------------------------------------//
uint16_t *fb_one;
uint16_t *fb_two;
uint16_t *fb_three;
uint32_t *fb_four;

#endif  /*_KERNEL_H */
