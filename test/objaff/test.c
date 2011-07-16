#include <string.h>
#include <display.h>
#include <input.h>
#include <color.h>
#include <tiles.h>
#include <object.h>
#include <affine.h>

int main(void) {

  object_block_t object_buffer = { { {0, 0} }, };
  object_affattrblock_pt object_affine_attribute_buffer = 
    (object_affattrblock_pt)object_buffer;
  object_affblock_pt object_affine_buffer = 
    (object_affblock_pt)object_buffer;
  affine_t current_affine = identity;
  affine_t diff_affine = {
    .rotation = 1<<7,
    .scale = {
      .x = fixe(0,10),
      .y = fixe(0,10),
    },
    .shear = {
      .x = fixe(0,10),
      .y = fixe(0,10),
    },
  };
  u32 count = 0;
  bool_t changed = FALSE;

  current_affine.screen_anchor.x = 120 << 8;
  current_affine.screen_anchor.y = 80 << 8;
  current_affine.map_anchor.x = 8 << 8;
  current_affine.map_anchor.y = 8 << 8;

  busy_wait_vsync();

  display_control_init();
  REG_DISPLAY_CONTROL.render_object = TRUE;

  memset(MEM_PALBLOCK,0,sizeof(palblock_t));
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][1] = RGB15_RED;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][2] = RGB15_GREEN;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][3] = RGB15_BLUE;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][4] = RGB15_PURPLE;

  memset(MEM_TILE,0,CHARBLOCK_MAX * sizeof(charblock_4bpp_t));
  memset(MEM_TILE[CHARBLOCK_OBJECT]+0,0x11,sizeof(tile_t));
  memset(MEM_TILE[CHARBLOCK_OBJECT]+1,0x33,sizeof(tile_t));
  memset(MEM_TILE[CHARBLOCK_OBJECT]+2,0x44,sizeof(tile_t));
  memset(MEM_TILE[CHARBLOCK_OBJECT]+3,0x22,sizeof(tile_t));

  object_init(object_buffer,OBJECT_MAX);

  object_affine_attribute_buffer[0].X = 50;
  object_affine_attribute_buffer[0].Y = 30;
  object_affine_attribute_buffer[0].size = SIZE_16;
  object_affine_attribute_buffer[0].palblock_index = 0;
  object_affine_attribute_buffer[0].affine_index = 0;
  object_affine_attribute_buffer[0].mode = MODE_AFFINE_DOUBLE;

  affine_to_object(object_affine_attribute_buffer+0,
		   object_affine_buffer+0,
  		   &current_affine);

  /* s32 t = 1025; */
  /* object_affine_buffer[0].attr0 = cosinus(t); */
  /* object_affine_buffer[0].attr1 = -sinus(t); */
  /* object_affine_buffer[0].attr2 = sinus(t); */
  /* object_affine_buffer[0].attr3 = cosinus(t); */

  object_copy(MEM_OBJECT,object_buffer,OBJECT_MAX);

  while(1) {

    busy_wait_vsync();
    count = (count + 1) % 1;
    if(0 == count) {

      changed = FALSE;

      input_poll();
      if(input_released_status.start) {

	current_affine = identity;
	changed = TRUE;

      }
      if(input_released_status.A) {

	if(MODE_AFFINE == object_affine_attribute_buffer[0].mode) {

	  object_affine_attribute_buffer[0].mode = MODE_AFFINE_DOUBLE;

	}
	else {

	  object_affine_attribute_buffer[0].mode = MODE_AFFINE;

	}
	changed = TRUE;

      }
      if(KEY_DOWN == input_current_status.L) {

	current_affine.rotation += diff_affine.rotation;
	changed = TRUE;

      }
      else if(KEY_DOWN == input_current_status.R) {

	current_affine.rotation -= diff_affine.rotation;
	changed = TRUE;

      }
      if(KEY_DOWN == input_current_status.select) {

	if(KEY_DOWN == input_current_status.up) {

	  current_affine.shear.y += diff_affine.shear.y;
	  changed = TRUE;

	}
	else if(KEY_DOWN == input_current_status.down) {

	  current_affine.shear.y -= diff_affine.shear.y;
	  changed = TRUE;

	}
	if(KEY_DOWN == input_current_status.left) {

	  current_affine.shear.x -= diff_affine.shear.x;
	  changed = TRUE;

	}
	else if(KEY_DOWN == input_current_status.right) {

	  current_affine.shear.x += diff_affine.shear.x;
	  changed = TRUE;

	}

      }
      else {

	if(KEY_DOWN == input_current_status.up) {

	  current_affine.scale.y += diff_affine.scale.y;
	  changed = TRUE;

	}
	else if(KEY_DOWN == input_current_status.down) {

	  current_affine.scale.y -= diff_affine.scale.y;
	  changed = TRUE;

	}
	if(KEY_DOWN == input_current_status.left) {

	  current_affine.scale.x -= diff_affine.scale.x;
	  changed = TRUE;

	}
	else if(KEY_DOWN == input_current_status.right) {

	  current_affine.scale.x += diff_affine.scale.x;
	  changed = TRUE;

	}

      }
      if(changed) {

	affine_to_object(object_affine_attribute_buffer+0,
			 object_affine_buffer+0,
			 &current_affine);
	object_copy(MEM_OBJECT,object_buffer,4);

      }

    }

  }

}
