#include "debug.h"
#include "draw.h"
#include "hvs.h"
#include "mini_uart.h"
#include "mm.h"
#include "printf.h"
#include "utils.h"

#include "kernel.h"
#include "dpi.h"

void kernel_main(void) {

	uint8_t i, x, y;

	uart_init();
    init_printf(0, putc);
    debug_print_registers();

	fb_one		= (uint16_t*)FB_ONE;
	fb_two		= (uint16_t*)FB_TWO;
	fb_three	= (uint16_t*)FB_THREE;
	fb_four		= (uint32_t*)FB_FOUR;
	fb_five		= (uint32_t*)FB_FIVE;
	fb_six		= (uint32_t*)FB_SIX;

    /* Each framebuffer will be a quarter of the screen in dimensions. */
    const uint16_t screen_width = HDMI_WIDTH, screen_height = HDMI_HEIGHT;
    const uint16_t fb_width = screen_width / 2, fb_height = screen_height / 2;
    const uint16_t fb_center_x = fb_width / 2;
    const uint16_t fb_center_y = fb_height / 2;

	setup_dpi_pixel_valve();
	setup_HVS_DPI();				// setup value from Raspbian Buster

	i = 0;
	for (x = 0; x < 2; x++) {
		planes_DPI[i].format = HVS_PIXEL_FORMAT_RGBA8888,
		planes_DPI[i].pixel_order = HVS_PIXEL_ORDER_ARGB,
		planes_DPI[i].start_x = (LCD_WIDTH / 2) * x;
		planes_DPI[i].start_y = 0;
		planes_DPI[i].height = LCD_HEIGHT,
		planes_DPI[i].width = (LCD_WIDTH / 2),
		planes_DPI[i].pitch = LCD_WIDTH * 2,
		i++;
	}

    planes_DPI[0].framebuffer = fb_five;
    planes_DPI[1].framebuffer = fb_six;

    clear_plane_32(planes_DPI[0], RED_32);
    clear_plane_32(planes_DPI[1], BLUE_32);
	write_display_list_DPI(planes_DPI, 2);

    /* Set up initial display list - a single plane centered on the screen. */
    hvs_plane plane = {
        .format = HVS_PIXEL_FORMAT_RGB565,
        .pixel_order = HVS_PIXEL_ORDER_ARGB,
        .start_x = (screen_width - fb_width) / 2,
        .start_y = (screen_height - fb_height) / 2,
        .height = fb_height,
        .width = fb_width,
        .pitch = fb_width * sizeof(uint16_t),
        .framebuffer = fb_one
    };
    clear_plane_16(plane, BLUE_16);
    printf("Writing initial display list.r\n");
    write_display_list(&plane, 1);

    /* Pause for a few seconds... */
    delay(9000000);

    /* We'll use this rect to draw rectangles. */
    rect r  = {
        .left = fb_center_x - 100,
        .top = fb_center_y - 100,
        .right = fb_center_x + 100,
        .bottom = fb_center_y + 100
    };

    /* Clear the framebuffer and do some drawing... */
    printf("Clearing framebuffer and drawing.\r\n");
    clear_plane_16(plane, GREEN_16);
    draw_rectangle_16(plane, WHITE_16, r);

    /* Pause for a few seconds... */
    delay(9000000);

    /* Move the plane across the screen. */
    printf("Translating plane across screen.r\n");
    for (i = 0; i < 10; i++) {
        plane.start_x = i * ((screen_width - fb_width) / 10);
        plane.start_y = i * ((screen_height - fb_height) / 10);
        write_display_list(&plane, 1);
        delay(9000000 * 0.25);
    }

    /* Set up 4 planes. */
    hvs_plane planes[4];
    i = 0;
    for (y = 0; y < 2; y++) {
        for (x = 0; x < 2; x++) {
            planes[i].format = HVS_PIXEL_FORMAT_RGB565,
            planes[i].pixel_order = HVS_PIXEL_ORDER_ARGB,
            planes[i].start_x = fb_width * x;
            planes[i].start_y = fb_height * y;
            planes[i].height = fb_height,
            planes[i].width = fb_width,
            planes[i].pitch = fb_width * 2,
            i++;
        }
    }
    planes[0].framebuffer = fb_one;
    planes[1].framebuffer = fb_two;
    planes[2].framebuffer = fb_three;
    planes[3].framebuffer = fb_four;

    /* We'll make the fourth framebuffer a 32-bit pixel format, just for demonstrations. */
    planes[3].format = HVS_PIXEL_FORMAT_RGBA8888;
    planes[3].pitch = fb_width * 4;

    printf("Updating display list with 4 framebuffers.r\n");
    write_display_list(planes, 4);

    /* Clear the 3 new framebuffers. */

    clear_plane_16(planes[1], BLUE_16);
    clear_plane_16(planes[2], WHITE_16);
    clear_plane_32(planes[3], RED_32);

    /* Draw some additional shapes. */
    draw_rectangle_16(planes[0], WHITE_16, r);
    draw_circle_16(planes[1], WHITE_16, fb_center_x, fb_center_y, 100);
    draw_circle_16(planes[2], BLACK_16, fb_center_x, fb_center_y, 100);
    draw_rectangle_32(planes[3], YELLOW_32, r);

    delay(9000000);

    /* Move the fourth plane to the center of the screen. */
    planes[3].start_x = (screen_width - fb_width) / 2;
    planes[3].start_y = (screen_height - fb_height) / 2;

    printf("Moving the fourth plane to the center of the screen.r\n");
    write_display_list(planes, 4);

    delay(9000000);

    /* Make the fourth plane partially-transparent with a yellow square. */
    printf("Clearing the fourth plane with a partially-transparent color.r\n");
    uint32_t half_trasparent_red = 0x7F0000FF;
    clear_plane_32(planes[3], half_trasparent_red);
    draw_rectangle_32(planes[3], YELLOW_32, r);

    delay(9000000);

    int first_plane = 0;
    printf("Now rotating framebuffers in an infinite loop.\r\n");
    while (1) {
        /* Rotate the planes every so often... */
        for (y = 0; y < 2; y++) {
            for (x = 0; x < 2; x++) {
                int plane_index = (y * 2 + x + first_plane) % 4;
                planes[plane_index].start_x = fb_width * x;
                planes[plane_index].start_y = fb_height * y;
            }
        }
        write_display_list(planes, 4);

		planes_DPI[0].start_x = planes_DPI[0].start_x?0:(LCD_WIDTH / 2);
		planes_DPI[1].start_x = planes_DPI[1].start_x?0:(LCD_WIDTH / 2);
		write_display_list_DPI(planes_DPI, 2);

        delay(9000000 * 1);

        first_plane = (first_plane + 1) % 4;
    }
}
