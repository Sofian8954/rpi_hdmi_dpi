/********************************************************************************/
/*							Constantinescu Sofian								*/
/*		www.pickit.ro								sofian@pickit.ro			*/
/********************************************************************************/

// Includes ------------------------------------------------------------------- //
#include "dpi.h"
#include "gpio.h"
#include "hvs.h"
#include "peripherals/hvs.h"
#include "kernel.h"
#include "utils.h"

//------------------------------------------------------------------------------//
void setup_dpi_pixel_valve(void) {

	// setup pin for DPI
	Gpio_Setup(0, GPIO_ALTFUNC2);			// CLK
	Gpio_Setup(1, GPIO_ALTFUNC2);			// DE
	Gpio_Setup(2, GPIO_ALTFUNC2);			// VSYNC
	Gpio_Setup(3, GPIO_ALTFUNC2);			// HSYNC

	Gpio_Setup(4, GPIO_ALTFUNC2);			// Blue
	Gpio_Setup(5, GPIO_ALTFUNC2);
	Gpio_Setup(6, GPIO_ALTFUNC2);
	Gpio_Setup(7, GPIO_ALTFUNC2);
	Gpio_Setup(8, GPIO_ALTFUNC2);
	Gpio_Setup(9, GPIO_ALTFUNC2);
	Gpio_Setup(10, GPIO_ALTFUNC2);
	Gpio_Setup(11, GPIO_ALTFUNC2);

	Gpio_Setup(12, GPIO_ALTFUNC2);			// Green
	Gpio_Setup(13, GPIO_ALTFUNC2);
	Gpio_Setup(14, GPIO_ALTFUNC2);
	Gpio_Setup(15, GPIO_ALTFUNC2);
	Gpio_Setup(16, GPIO_ALTFUNC2);
	Gpio_Setup(17, GPIO_ALTFUNC2);
	Gpio_Setup(18, GPIO_ALTFUNC2);
	Gpio_Setup(19, GPIO_ALTFUNC2);

	Gpio_Setup(20, GPIO_ALTFUNC2);			// Red
	Gpio_Setup(21, GPIO_ALTFUNC2);
	Gpio_Setup(22, GPIO_ALTFUNC2);
	Gpio_Setup(23, GPIO_ALTFUNC2);
	Gpio_Setup(24, GPIO_ALTFUNC2);
	Gpio_Setup(25, GPIO_ALTFUNC2);
	Gpio_Setup(26, GPIO_ALTFUNC2);
	Gpio_Setup(27, GPIO_ALTFUNC2);

	Gpio_Resistor(0, NO_RESISTOR);			// Disable pull UD
	Gpio_Resistor(1, NO_RESISTOR);
	Gpio_Resistor(2, NO_RESISTOR);
	Gpio_Resistor(3, NO_RESISTOR);

	Gpio_Resistor(4, NO_RESISTOR);			// Blue
	Gpio_Resistor(5, NO_RESISTOR);
	Gpio_Resistor(6, NO_RESISTOR);
	Gpio_Resistor(7, NO_RESISTOR);
	Gpio_Resistor(8, NO_RESISTOR);
	Gpio_Resistor(9, NO_RESISTOR);
	Gpio_Resistor(10, NO_RESISTOR);
	Gpio_Resistor(11, NO_RESISTOR);

	Gpio_Resistor(12, NO_RESISTOR);			// Green
	Gpio_Resistor(13, NO_RESISTOR);
	Gpio_Resistor(14, NO_RESISTOR);
	Gpio_Resistor(15, NO_RESISTOR);
	Gpio_Resistor(16, NO_RESISTOR);
	Gpio_Resistor(17, NO_RESISTOR);
	Gpio_Resistor(18, NO_RESISTOR);
	Gpio_Resistor(19, NO_RESISTOR);

	Gpio_Resistor(20, NO_RESISTOR);			// Red
	Gpio_Resistor(21, NO_RESISTOR);
	Gpio_Resistor(22, NO_RESISTOR);
	Gpio_Resistor(23, NO_RESISTOR);
	Gpio_Resistor(24, NO_RESISTOR);
	Gpio_Resistor(25, NO_RESISTOR);
	Gpio_Resistor(26, NO_RESISTOR);
	Gpio_Resistor(27, NO_RESISTOR);

//------------------------------------------------------------------------------//
// Setuip Clock Manager for DPI
	// GP0CLK 36.8640MHz: PLLD 500 MHz / 36.8640MHz = 13.5633 : I = 13 : F = (0.5633 * 4096) = 2307
	// 9Mhz: OSC 19.2Mhz / 9.6Mhz = 2 : I = 2 : F =(0 * 4096) = 0
	CM_DPICTL = (CM_PASSWORD + 0x0021);		// Disable Clock Generator, oscillator
	CM_DPIDIV = (CM_PASSWORD + 0x2000);		// Div by I=2:F=0
	CM_DPICTL = (CM_PASSWORD + 0x0211);		// Enable Clock Generator, 1stage MASH, PLLD

//------------------------------------------------------------------------------//
// DPI Register
	DPI_CTL  = 0x00013301;		// Enable DPI

//------------------------------------------------------------------------------//
// PV0 Register

	// PV0_C =	0x00177005;
	PV0_VC = 0x00000003;
	PV0_VSYNCD_EVEN = 0x00000000;
	// PV0_HORZA =	0x002B0029;
	// PV0_HORZB =	0x000201E0;
	// PV0_VERTA =	0x0002000C;
	// PV0_VERTB =	0x00020110;
	PV0_VERTA_EVEN = 0x00000000;
	PV0_VERTB_EVEN = 0x00000000;
	PV0_INTEN =	0x00000000;
	PV0_INTSTAT = 0x00000000;
	PV0_STAT =	0x00000644;
	PV0_HACT_ACT = 0x000001E0;


	PV0_HORZA = ((LCD_HBP << 16) | LCD_HSYNC);
	PV0_HORZB = ((LCD_HFP << 16) | LCD_WIDTH);

	PV0_VERTA = ((LCD_VBP << 16) | LCD_VSYNC);
	PV0_VERTB = ((LCD_VFP << 16) | LCD_HEIGHT);

	PV0_C = 0x00177005;
}
//------------------------------------------------------------------------------//
// setup value from Raspbian Buster
void setup_HVS_DPI(void) {

	uint32_t *ptrMem;

	ptrMem = (uint32_t*)(PBASE + 0x00400334);
	*ptrMem++ = 0x00000664;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x801E0110;
	*ptrMem++ = 0x81000000;
	*ptrMem++ = 0xA19920C8;
	*ptrMem++ = 0x50FF3C90;
	*ptrMem++ = 0x80500400;
	*ptrMem++ = 0x81000000;
	*ptrMem++ = 0xA0A2B3EE;
	*ptrMem++ = 0x3C8F0800;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x10000000;
	*ptrMem++ = 0x07FF0000;
	*ptrMem++ = 0x000000FF;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x64647276;

}
//------------------------------------------------------------------------------//
// setup value from Raspbian Buster
void setup_HVS(void) {

	uint32_t *ptrMem;

	ptrMem = (uint32_t*)(PBASE + 0x00400000);
	*ptrMem++ = 0x9A0C0FFF;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x71BF0000;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x0000F81E;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x00000334;			// 0x00400020
	*ptrMem++ = 0x00000664;			// 0x00400024
	*ptrMem++ = 0x00000000;			// 0x00400028
	*ptrMem++ = 0x30000000;
	*ptrMem++ = 0x00000334;
	*ptrMem++ = 0x00000664;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x801E0110;
	*ptrMem++ = 0x81000000;
	*ptrMem++ = 0xA19AF044;
	*ptrMem++ = 0x50FF3C90;
	*ptrMem++ = 0x80500400;
	*ptrMem++ = 0x81000000;
	*ptrMem++ = 0xA02082CC;
	*ptrMem++ = 0x3C8F0800;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x10000000;
	*ptrMem++ = 0x07FF0000;
	*ptrMem++ = 0x000000FF;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x64647276;

	*ptrMem++ = 0x00000000;			// 0x3F400080
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x00000000;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x64647276;
	*ptrMem++ = 0x00001011;
	*ptrMem++ = 0x000011CD;
	*ptrMem++ = 0x00FFFFFF;
	*ptrMem++ = 0x000014E8;

	ptrMem = (uint32_t*) 0x3F4000E0;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;
	*ptrMem++ = 0x00000062;

}
//------------------------------------------------------------------------------//
static volatile uint32_t* dlist_memory = (uint32_t*) 0x3F402400;

/* We'll use a simple "double buffering" scheme to avoid writing out a new display list while
   one is still in-flight. */
static const uint16_t dlist_buffer_count = 2;
static const uint16_t dlist_offsets[] = { 0, 128 };
static uint16_t next_dlist_buffer = 0;

#define WRITE_WORD(word) (dlist_memory[(*offset)++] = word)

static void write_plane(uint16_t* offset, hvs_plane plane)
{
    /* Write out the words for this plane. Each word conveys some information to the HVS on how it
       should interpret this plane. */

    /* Control Word */
    const uint8_t number_of_words = 7;
    uint32_t control_word = SCALER_CTL0_VALID              |        // denotes the start of a plane
                            SCALER_CTL0_UNITY              |        // indicates no scaling
                            plane.pixel_order       << 13  |        // pixel order
                            number_of_words         << 24  |        // number of words in this plane
                            plane.format;                           // pixel format
    WRITE_WORD(control_word);

    /* Position Word 0 */
    uint32_t position_word_0 = plane.start_x        << 0   |
                               plane.start_y        << 12;
    WRITE_WORD(position_word_0);

    /* Position Word 1: scaling, only if non-unity */

    /* Position Word 2 */
    uint32_t position_word_2 = plane.width         << 0    |
                               plane.height        << 16;
    WRITE_WORD(position_word_2);

    /* Position Word 3: used by HVS */
    WRITE_WORD(0xDEADBEEF);

    /* Pointer Word */
    /* This cast is okay, because the framebuffer pointer can always be held in 4 bytes
       even though we're on a 64 bit architecture. */
    uint32_t framebuffer = (uint32_t) (intptr_t) plane.framebuffer;
    WRITE_WORD(0x80000000 | framebuffer);

    /* Pointer Context: used by HVS */
    WRITE_WORD(0xDEADBEEF);

    /* Pitch Word */
    uint32_t pitch_word = plane.pitch;
    WRITE_WORD(pitch_word);
}

void write_plane_DPI(void) {

hvs_plane plane;
	plane.format = HVS_PIXEL_FORMAT_RGBA8888,
	plane.pixel_order = HVS_PIXEL_ORDER_ARGB,
	plane.start_x = 0;
	plane.start_y = 0;
	plane.height = LCD_HEIGHT,
	plane.width = LCD_WIDTH,
	plane.pitch = LCD_WIDTH * sizeof(uint32_t),
    plane.framebuffer = fb_four;

    uint16_t offset = dlist_offsets[next_dlist_buffer];
    const uint16_t start = offset;

	write_plane(&offset, plane);
// End Word
    dlist_memory[offset] = SCALER_CTL0_END;
// Tell the HVS where the display list is by writing to the SCALER_DISPLIST1 register.
    put32(SCALER_DISPLIST0, start);

    next_dlist_buffer = (next_dlist_buffer + 1) % dlist_buffer_count;
 }

