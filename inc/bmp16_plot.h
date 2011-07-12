#ifndef PLOT_H_
#define PLOT_H_

#include <screen.h>
#include <color.h>

INLINE void bmp16_plot(screen_coord_t x,
		       screen_coord_t y,
		       color_t color,
		       color_t *mem,
		       screen_coord_t mem_width) {

  mem[x + (y * mem_width)] = color;

}

void bmp16_line(screen_coord_t x1,
		screen_coord_t y1,
		screen_coord_t x2,
		screen_coord_t y2,
		color_t color,
		color_t *mem,
		screen_coord_t mem_width);

void bmp16_rect(screen_coord_t top,
		screen_coord_t right,
		screen_coord_t bottom,
		screen_coord_t left,
		color_t color,
		color_t *mem,
		screen_coord_t mem_width);

void bmp16_filled_rect(screen_coord_t top,
		       screen_coord_t right,
		       screen_coord_t bottom,
		       screen_coord_t left,
		       color_t color,
		       color_t *mem,
		       screen_coord_t mem_width);

void bmp16_circle(screen_coord_t x_center,
		  screen_coord_t y_center,
		  screen_coord_t radius,
		  color_t color,
		  color_t *mem,
		  screen_coord_t mem_width);

void bmp16_filled_circle(screen_coord_t x_center,
			 screen_coord_t y_center,
			 screen_coord_t radius,
			 color_t color,
			 color_t *mem,
			 screen_coord_t mem_width);

#endif
