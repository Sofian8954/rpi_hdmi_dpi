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
#define FB_TWO						0x11000000
#define FB_THREE					0x12000000
#define FB_FOUR						0x13000000
#define FB_FIVE						0x14000000
#define FB_SIX						0x15000000

//------------------------------------------------------------------------------//
uint16_t *fb_one;					// planes for HDMI
uint16_t *fb_two;
uint16_t *fb_three;
uint32_t *fb_four;
uint32_t *fb_five;					// planes for DPI
uint32_t *fb_six;

#endif  /*_KERNEL_H */
