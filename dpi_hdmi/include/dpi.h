/********************************************************************************/
/*							Constantinescu Sofian								*/
/*		www.pickit.ro								sofian@pickit.ro			*/
/********************************************************************************/
#ifndef	_DPI_H
#define	_DPI_H
// Includes ------------------------------------------------------------------- //
#include "peripherals/base.h"
#include "peripherals/gpio.h"
#include "hvs.h"

//------------------------------------------------------------------------------//
#define CM_PASSWORD					0x5A000000
#define CM_DPICTL					*((volatile uint32_t*)(PBASE + 0x00101068))		/* Clock Manager DPI Clock Control */
#define CM_DPIDIV					*((volatile uint32_t*)(PBASE + 0x0010106C))		/* Clock Manager DPI Clock Divisor */

//------------------------------------------------------------------------------//
#define DPI_CTL						*((volatile uint32_t*)(PBASE + 0x00208000))

//------------------------------------------------------------------------------//
#define PV0_C						*((volatile uint32_t*)(PBASE + 0x00206000))
#define PV0_VC						*((volatile uint32_t*)(PBASE + 0x00206004))
#define PV0_VSYNCD_EVEN				*((volatile uint32_t*)(PBASE + 0x00206008))
#define PV0_HORZA					*((volatile uint32_t*)(PBASE + 0x0020600C))
#define PV0_HORZB					*((volatile uint32_t*)(PBASE + 0x00206010))
#define PV0_VERTA					*((volatile uint32_t*)(PBASE + 0x00206014))
#define PV0_VERTB					*((volatile uint32_t*)(PBASE + 0x00206018))
#define PV0_VERTA_EVEN				*((volatile uint32_t*)(PBASE + 0x0020601C))
#define PV0_VERTB_EVEN				*((volatile uint32_t*)(PBASE + 0x00206020))
#define PV0_INTEN					*((volatile uint32_t*)(PBASE + 0x00206024))
#define PV0_INTSTAT					*((volatile uint32_t*)(PBASE + 0x00206028))
#define PV0_STAT					*((volatile uint32_t*)(PBASE + 0x0020602C))
#define PV0_HACT_ACT				*((volatile uint32_t*)(PBASE + 0x00206030))

//------------------------------------------------------------------------------//
// LCD
#define HDMI_WIDTH					1280
#define HDMI_HEIGHT					1024

#define LCD_WIDTH					480
#define LCD_HEIGHT					272

#define LCD_HFP						2
#define LCD_HBP						41
#define LCD_HSYNC					43

#define LCD_VFP						2
#define LCD_VBP						12
#define LCD_VSYNC					14

//------------------------------------------------------------------------------//
    hvs_plane planes_DPI[2];

//------------------------------------------------------------------------------//
void setup_dpi_pixel_valve(void);
void setup_HVS_DPI(void);
void write_display_list_DPI(hvs_plane planes[], uint8_t count);

#endif  /*_DPI_H */
