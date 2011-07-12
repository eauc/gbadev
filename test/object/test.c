#include <string.h>
#include "display.h"
#include "input.h"
#include "color.h"
#include "tiles.h"
#include "object.h"

int main(void) {

  object_block_t object_buffer = { { {0, 0} }, };
  object_attrblock_pt object_attribute_buffer = 
    (object_attrblock_pt)object_buffer;
  u32 count = 0;
  bool_t changed = FALSE;

  busy_wait_vsync();

  display_control_init();
  REG_DISPLAY_CONTROL.render_object = TRUE;

  memset(MEM_PALBLOCK,0,sizeof(palblock_t));
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][1] = RGB15_RED;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][2] = RGB15_GREEN;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+1][1] = RGB15_BLUE;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+1][2] = RGB15_PURPLE;

  memset(MEM_TILE,0,CHARBLOCK_MAX * sizeof(charblock_4bpp_t));
  memset(MEM_TILE[CHARBLOCK_OBJECT]+0,0x11,sizeof(tile_t));
  memset(MEM_TILE[CHARBLOCK_OBJECT]+3,0x22,sizeof(tile_t));

  object_init(object_buffer,OBJECT_MAX);
  object_copy(MEM_OBJECT,object_buffer,OBJECT_MAX);

  object_attribute_buffer[0].X = 50;
  object_attribute_buffer[0].Y = 30;
  object_attribute_buffer[0].size = SIZE_16;
  object_attribute_buffer[0].palblock_index = 0;
  object_attribute_buffer[0].mode = MODE_NORMAL;
  object_copy(MEM_OBJECT,object_buffer,1);

  while(1) {

    busy_wait_vsync();
    count = (count + 1) % 1;
    if(0 == count) {

      changed = FALSE;

      input_poll();
      if(input_active()) {

	object_attribute_setX(object_attribute_buffer,
			      object_attribute_buffer[0].X + 
			      input_tribool_horizontal());
	object_attribute_setY(object_attribute_buffer,
			      object_attribute_buffer[0].Y + 
			      input_tribool_vertical());
	changed = TRUE;

      }
      if(input_hit_status.A) {

	object_attribute_buffer[0].palblock_index ^= 1;
	changed = TRUE;

      }
      if(input_released_status.A) {

	object_attribute_buffer[0].palblock_index ^= 1;
	changed = TRUE;

      }
      if(input_hit_status.L) {

	object_attribute_buffer[0].horizontal_flip ^= 1;
	changed = TRUE;

      }
      if(input_released_status.L) {

	object_attribute_buffer[0].horizontal_flip ^= 1;
	changed = TRUE;

      }
      if(input_hit_status.R) {

	object_attribute_buffer[0].vertical_flip ^= 1;
	changed = TRUE;

      }
      if(input_released_status.R) {

	object_attribute_buffer[0].vertical_flip ^= 1;
	changed = TRUE;

      }
      if(changed) {

	object_copy(MEM_OBJECT,object_buffer,1);

      }

    }

  }

}
