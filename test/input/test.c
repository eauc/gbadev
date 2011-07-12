#include "screen.h"
#include "display.h"
#include "color.h"
#include "m3.h"
#include "input.h"

const screen_coord_t A_coord[4] = {205,70,10};
const screen_coord_t B_coord[4] = {180,95,10};

const screen_coord_t up_coord[4] = {60,55,75,45};
const screen_coord_t down_coord[4] = {89,55,104,45};
const screen_coord_t left_coord[4] = {77,43,87,28};
const screen_coord_t right_coord[4] = {77,72,87,57};

const screen_coord_t start_coord[4] = {60,130,70,110};
const screen_coord_t select_coord[4] = {80,130,90,110};

const screen_coord_t L_coord[4] = {15,60,30,30};
const screen_coord_t R_coord[4] = {15,210,30,180};

int main(void) {

  u32 count=0;
  //  u32 test=0;

  color_t clean = RGB15_BLACK;
  color_t up = RGB15_RED;
  color_t hit = RGB15_BLUE;
  color_t released = RGB15_PURPLE;
  color_t down = RGB15_GREEN;

  input_status_t previous_change  = {0,0,0,0,0,0,0,0,0,0};

  busy_wait_vsync();

  display_control_init();

  REG_DISPLAY_CONTROL.mode = 3;
  REG_DISPLAY_CONTROL.render_background2 = TRUE;

  m3_rect(L_coord[0],L_coord[1],L_coord[2],L_coord[3],up);
  m3_rect(R_coord[0],R_coord[1],R_coord[2],R_coord[3],up);

  m3_rect(start_coord[0],start_coord[1],start_coord[2],start_coord[3],up);
  m3_rect(select_coord[0],select_coord[1],select_coord[2],select_coord[3],up);

  m3_rect(up_coord[0],up_coord[1],up_coord[2],up_coord[3],up);
  m3_rect(down_coord[0],down_coord[1],down_coord[2],down_coord[3],up);
  m3_rect(left_coord[0],left_coord[1],left_coord[2],left_coord[3],up);
  m3_rect(right_coord[0],right_coord[1],right_coord[2],right_coord[3],up);

  m3_circle(A_coord[0],A_coord[1],A_coord[2],up);
  m3_circle(B_coord[0],B_coord[1],B_coord[2],up);

  while(1) {

    count = (count + 1) % 10;
    busy_wait_vsync();
    if(0 == count) {

      input_poll();
      if(*((u32 *)&input_changed_status)) {

	*((u32 *)&previous_change) = *((u32 *)&input_changed_status);
	if(input_hit_status.A) {

	  m3_circle(A_coord[0],A_coord[1],A_coord[2],hit);
	  
	}
	else if(input_released_status.A) {
	  
	  m3_filled_circle(A_coord[0],A_coord[1],A_coord[2],clean);
	  m3_circle(A_coord[0],A_coord[1],A_coord[2],released);
	  
	}
	if(input_hit_status.B) {

	  m3_circle(B_coord[0],B_coord[1],B_coord[2],hit);
	  
	}
	else if(input_released_status.B) {
	  
	  m3_filled_circle(B_coord[0],B_coord[1],B_coord[2],clean);
	  m3_circle(B_coord[0],B_coord[1],B_coord[2],released);
	  
	}
	if(input_hit_status.L) {

	  m3_rect(L_coord[0],L_coord[1],L_coord[2],L_coord[3],hit);
	  
	}
	else if(input_released_status.L) {
	  
	  m3_filled_rect(L_coord[0],L_coord[1],L_coord[2],L_coord[3],clean);
	  m3_rect(L_coord[0],L_coord[1],L_coord[2],L_coord[3],released);
	  
	}
	if(input_hit_status.R) {

	  m3_rect(R_coord[0],R_coord[1],R_coord[2],R_coord[3],hit);
	  
	}
	else if(input_released_status.R) {
	  
	  m3_filled_rect(R_coord[0],R_coord[1],R_coord[2],R_coord[3],clean);
	  m3_rect(R_coord[0],R_coord[1],R_coord[2],R_coord[3],released);
	  
	}
	if(input_hit_status.start) {

	  m3_rect(start_coord[0],start_coord[1],start_coord[2],start_coord[3],hit);
	  
	}
	else if(input_released_status.start) {
	  
	  m3_filled_rect(start_coord[0],start_coord[1],start_coord[2],start_coord[3],clean);
	  m3_rect(start_coord[0],start_coord[1],start_coord[2],start_coord[3],released);
	  
	}
	if(input_hit_status.select) {

	  m3_rect(select_coord[0],select_coord[1],select_coord[2],select_coord[3],hit);
	  
	}
	else if(input_released_status.select) {
	  
	  m3_filled_rect(select_coord[0],select_coord[1],select_coord[2],select_coord[3],clean);
	  m3_rect(select_coord[0],select_coord[1],select_coord[2],select_coord[3],released);
	  
	}
	if(input_hit_status.up) {

	  m3_rect(up_coord[0],up_coord[1],up_coord[2],up_coord[3],hit);
	  
	}
	else if(input_released_status.up) {
	  
	  m3_filled_rect(up_coord[0],up_coord[1],up_coord[2],up_coord[3],clean);
	  m3_rect(up_coord[0],up_coord[1],up_coord[2],up_coord[3],released);
	  
	}
	if(input_hit_status.down) {

	  m3_rect(down_coord[0],down_coord[1],down_coord[2],down_coord[3],hit);
	  
	}
	else if(input_released_status.down) {
	  
	  m3_filled_rect(down_coord[0],down_coord[1],down_coord[2],down_coord[3],clean);
	  m3_rect(down_coord[0],down_coord[1],down_coord[2],down_coord[3],released);
	  
	}
	if(input_hit_status.left) {

	  m3_rect(left_coord[0],left_coord[1],left_coord[2],left_coord[3],hit);
	  
	}
	else if(input_released_status.left) {
	  
	  m3_filled_rect(left_coord[0],left_coord[1],left_coord[2],left_coord[3],clean);
	  m3_rect(left_coord[0],left_coord[1],left_coord[2],left_coord[3],released);
	  
	}
	if(input_hit_status.right) {

	  m3_rect(right_coord[0],right_coord[1],right_coord[2],right_coord[3],hit);
	  
	}
	else if(input_released_status.right) {
	  
	  m3_filled_rect(right_coord[0],right_coord[1],right_coord[2],right_coord[3],clean);
	  m3_rect(right_coord[0],right_coord[1],right_coord[2],right_coord[3],released);
	  
	}

      }
      else {

	if(previous_change.A) {

	  if(KEY_UP == input_current_status.A) {

	    m3_circle(A_coord[0],A_coord[1],A_coord[2],up);

	  }
	  else {

	    m3_filled_circle(A_coord[0],A_coord[1],A_coord[2],down);

	  }

	}
	if(previous_change.B) {

	  if(KEY_UP == input_current_status.B) {

	    m3_circle(B_coord[0],B_coord[1],B_coord[2],up);

	  }
	  else {

	    m3_filled_circle(B_coord[0],B_coord[1],B_coord[2],down);

	  }

	}
	if(previous_change.L) {

	  if(KEY_UP == input_current_status.L) {

	    m3_rect(L_coord[0],L_coord[1],L_coord[2],L_coord[3],up);

	  }
	  else {

	    m3_filled_rect(L_coord[0],L_coord[1],L_coord[2],L_coord[3],down);

	  }

	}
	if(previous_change.R) {

	  if(KEY_UP == input_current_status.R) {

	    m3_rect(R_coord[0],R_coord[1],R_coord[2],R_coord[3],up);

	  }
	  else {

	    m3_filled_rect(R_coord[0],R_coord[1],R_coord[2],R_coord[3],down);

	  }

	}
	if(previous_change.start) {

	  if(KEY_UP == input_current_status.start) {

	    m3_rect(start_coord[0],start_coord[1],start_coord[2],start_coord[3],up);

	  }
	  else {

	    m3_filled_rect(start_coord[0],start_coord[1],start_coord[2],start_coord[3],down);

	  }

	}
	if(previous_change.select) {

	  if(KEY_UP == input_current_status.select) {

	    m3_rect(select_coord[0],select_coord[1],select_coord[2],select_coord[3],up);

	  }
	  else {

	    m3_filled_rect(select_coord[0],select_coord[1],select_coord[2],select_coord[3],down);

	  }

	}
	if(previous_change.up) {

	  if(KEY_UP == input_current_status.up) {

	    m3_rect(up_coord[0],up_coord[1],up_coord[2],up_coord[3],up);

	  }
	  else {

	    m3_filled_rect(up_coord[0],up_coord[1],up_coord[2],up_coord[3],down);

	  }

	}
	if(previous_change.down) {

	  if(KEY_UP == input_current_status.down) {

	    m3_rect(down_coord[0],down_coord[1],down_coord[2],down_coord[3],up);

	  }
	  else {

	    m3_filled_rect(down_coord[0],down_coord[1],down_coord[2],down_coord[3],down);

	  }

	}
	if(previous_change.right) {

	  if(KEY_UP == input_current_status.right) {

	    m3_rect(right_coord[0],right_coord[1],right_coord[2],right_coord[3],up);

	  }
	  else {

	    m3_filled_rect(right_coord[0],right_coord[1],right_coord[2],right_coord[3],down);

	  }

	}
	if(previous_change.left) {

	  if(KEY_UP == input_current_status.left) {

	    m3_rect(left_coord[0],left_coord[1],left_coord[2],left_coord[3],up);

	  }
	  else {
	    
	    m3_filled_rect(left_coord[0],left_coord[1],left_coord[2],left_coord[3],down);

	  }

	}
	*((u32 *)&previous_change) = 0;

      }

    }

  }

}
