#include <bmp16_plot.h>
#include <types.h>

void bmp16_line(screen_coord_t x1,
		screen_coord_t y1,
		screen_coord_t x2,
		screen_coord_t y2,
		color_t color,
		color_t *mem,
		screen_coord_t mem_width) {

  s32 dx = 0;
  s32 dy = 0;

  s32 x_inc = (x2 > x1) ? 1 : -1;
  s32 y_inc = (y2 > y1) ? mem_width : -mem_width;
  s32 count = 0;
  s32 x_main_inc = 0;
  s32 y_main_inc = 0;
  s32 count_main_inc = 0;
  s32 x_sub_inc = 0;
  s32 y_sub_inc = 0;
  s32 count_sub_inc = 0;

  u32 end = 0;
  u32 ind = 0;

  if(x1 == x2) {

    x_main_inc = 0;
    y_main_inc = 0;
    count_main_inc = 0;
    x_sub_inc = 0;
    y_sub_inc = y_inc;
    count_sub_inc = 0;
    count = 0;

  }
  else if(y1 == y2) {

    x_main_inc = 0;
    y_main_inc = 0;
    count_main_inc = 0;
    x_sub_inc = x_inc;
    y_sub_inc = 0;
    count_sub_inc = 0;
    count = 0;

  }
  else {

    dy = ABS((s32)(y2 - y1));
    dx = ABS((s32)(x2 - x1));

    if(dy > dx) {

      x_main_inc = x_inc;
      y_main_inc = 0;
      count_main_inc = 2 * dy;
      x_sub_inc = 0;
      y_sub_inc = y_inc;
      count_sub_inc = 2 * dx;
      count = -dy;

    }
    else {

      x_main_inc = 0;
      y_main_inc = y_inc;
      count_main_inc = 2 * dx;
      x_sub_inc = x_inc;
      y_sub_inc = 0;
      count_sub_inc = 2 * dy;
      count = -dx;

    }

  }

  end = x2 + y2 * mem_width;
  for(ind = x1 + y1 * mem_width ;
      ind != end ;
      ind += x_sub_inc + y_sub_inc) {

    mem[ind] = color;
    count += count_sub_inc;
    if(count > 0) {

      ind += x_main_inc + y_main_inc;
      count -= count_main_inc;
      
    }

  }
  mem[ind] = color;

}

void bmp16_rect(screen_coord_t top,
		screen_coord_t right,
		screen_coord_t bottom,
		screen_coord_t left,
		color_t color,
		color_t *mem,
		screen_coord_t mem_width) {

  bmp16_line(left,top,right,top,color,mem,mem_width);
  bmp16_line(left,bottom,right,bottom,color,mem,mem_width);
  bmp16_line(left,top,left,bottom,color,mem,mem_width);
  bmp16_line(right,top,right,bottom,color,mem,mem_width);

}

void bmp16_filled_rect(screen_coord_t top,
		       screen_coord_t right,
		       screen_coord_t bottom,
		       screen_coord_t left,
		       color_t color,
		       color_t *mem,
		       screen_coord_t mem_width) {

  u32 ix = 0;
  u32 iy = 0;
  screen_coord_t height = bottom-top+1;
  screen_coord_t width = right-left+1;
  color_t *start = mem + top * mem_width + left;

  for(iy = 0 ; iy < height ; iy ++) {

    for(ix = 0 ; ix < width ; ix++) {

      start[ix + iy * mem_width] = color;

    }

  }

}

void bmp16_circle(screen_coord_t x_center,
		  screen_coord_t y_center,
		  screen_coord_t radius,
		  color_t color,
		  color_t *mem,
		  screen_coord_t mem_width) {

  screen_coord_t x = radius;
  screen_coord_t y = 0;
  s32 dx = 2 * x - 1;
  s32 dy = x + 2;
  u32 ind = 0;

  for(;
      x >= y ;
      y++) {

    ind = (x + x_center) + (y + y_center) * mem_width;
    mem[ind] = color;
    ind = (-x + x_center) + (y + y_center) * mem_width;
    mem[ind] = color;
    ind = (-x + x_center) + (-y + y_center) * mem_width;
    mem[ind] = color;
    ind = (x + x_center) + (-y + y_center) * mem_width;
    mem[ind] = color;
    ind = (y + x_center) + (x + y_center) * mem_width;
    mem[ind] = color;
    ind = (-y + x_center) + (x + y_center) * mem_width;
    mem[ind] = color;
    ind = (-y + x_center) + (-x + y_center) * mem_width;
    mem[ind] = color;
    ind = (y + x_center) + (-x + y_center) * mem_width;
    mem[ind] = color;
    
    dy += 4 * y - 2;
    if(dy > dx) {

      x--;
      dy -= 2 * dx;
      dx -= 2;
      
    }

  }

}

void bmp16_filled_circle(screen_coord_t x_center,
			 screen_coord_t y_center,
			 screen_coord_t radius,
			 color_t color,
			 color_t *mem,
			 screen_coord_t mem_width) {

  screen_coord_t x = radius;
  screen_coord_t y = 0;
  s32 dx = 2 * x - 1;
  s32 dy = x + 2;
  u32 ind1 = 0;
  u32 ind2 = 0;
  s32 i = 0;

  for(;
      x >= y ;
      y++) {

    for(i = -x,
	  ind1 = x_center + (y + y_center) * mem_width,
	  ind2 = x_center + (-y + y_center) * mem_width;
	i <= (s32)x;
	i++) {

      mem[ind1 + i] = color;
      mem[ind2 + i] = color;

    }
    dy += 4 * y - 2;
    if(dy > dx) {

      for(i = -y,
	    ind1 = x_center + (x + y_center) * mem_width,
	    ind2 = x_center + (-x + y_center) * mem_width;
	  i <= (s32)y;
	  i++) {

	mem[ind1 + i] = color;
	mem[ind2 + i] = color;

      }
      x--;
      dy -= 2 * dx;
      dx -= 2;
      
    }

  }

}

