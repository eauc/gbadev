#ifndef M3_H_
#define M3_H_

#include <mem.h>
#include <screen.h>
#include <bmp16_plot.h>

#define M3_MEM_VIDEO  ((u16 *) MEM_VIDEO)

#define M3_SCREEN_WIDTH SCREEN_WIDTH

INLINE void m3_plot(screen_coord_t x,
		    screen_coord_t y,
		    color_t color) {

  bmp16_plot(x,y,color,M3_MEM_VIDEO,M3_SCREEN_WIDTH);

}

INLINE void m3_line(screen_coord_t x1,
		    screen_coord_t y1,
		    screen_coord_t x2,
		    screen_coord_t y2,
		    color_t color) {

  bmp16_line(x1,y1,x2,y2,color,M3_MEM_VIDEO,M3_SCREEN_WIDTH);

}

INLINE void m3_rect(screen_coord_t top,
		    screen_coord_t right,
		    screen_coord_t bottom,
		    screen_coord_t left,
		    color_t color) {

  bmp16_rect(top,right,bottom,left,color,M3_MEM_VIDEO,M3_SCREEN_WIDTH);

}

INLINE void m3_filled_rect(screen_coord_t top,
			   screen_coord_t right,
			   screen_coord_t bottom,
			   screen_coord_t left,
			   color_t color) {

  bmp16_filled_rect(top,right,bottom,left,color,M3_MEM_VIDEO,M3_SCREEN_WIDTH);

}

INLINE void m3_circle(screen_coord_t x_center,
		      screen_coord_t y_center,
		      screen_coord_t radius,
		      color_t color) {

  bmp16_circle(x_center,y_center,radius,color,M3_MEM_VIDEO,M3_SCREEN_WIDTH);

}

INLINE void m3_filled_circle(screen_coord_t x_center,
			     screen_coord_t y_center,
			     screen_coord_t radius,
			     color_t color) {

  bmp16_filled_circle(x_center,y_center,radius,color,M3_MEM_VIDEO,M3_SCREEN_WIDTH);

}

#endif
