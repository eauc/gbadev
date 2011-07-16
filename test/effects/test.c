#include <display.h>
#include <input.h>
#include <color.h>
#include <background.h>
#include <object.h>


#define SBB_0 28
screen_entry_t *bg0_map = 0;
background_offset_t bg0_offset = {0,0};

object_block_t object_buffer = { { {0, 0} }, };
object_attrblock_pt object_attribute_buffer = (object_attrblock_pt)object_buffer;

struct {

  s32 dx;
  s32 dy;

} bg = { 0, 0 };
struct {

  s32 dx;
  s32 dy;

} ob = { 0, 0, };
struct {

  s32 a;
  s32 b;
  s32 y;

} ev = { 0, 0, 16, };
struct {
  
  s32 l;
  s32 r;
  s32 t;
  s32 b;

} win = { 20, 160, 20, 120, };

u32 se_index(u32 tx,
	     u32 ty,
	     u32 pitch) {

  u32 sbb = (tx >> 5) + (ty >> 5) * (pitch >> 5);
  return sbb * 1024 + (tx & 31) + (ty & 31) * 32;

}

void init_palette(void) {

  MEM_PALBLOCK_4BPP[0][1] = RGB15_RED;
  MEM_PALBLOCK_4BPP[1][1] = RGB15_BLUE;
  MEM_PALBLOCK_4BPP[2][1] = RGB15_GREEN;
  MEM_PALBLOCK_4BPP[3][1] = RGB15(16,16,16);

  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][1] = RGB15_RED;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][2] = RGB15_GREEN;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][3] = RGB15_BLUE;
  MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_OBJECT+0][4] = RGB15_PURPLE;

}

void init_map() {

  s32 ii = 0;
  s32 jj = 0;
  screen_entry_t *sce = MEM_MAP[SBB_0];
const tile_t tiles[] = 
  {
    {
      { 
	0x01010101, 
	0x10101010,
	0x01010101, 
	0x10101010,
	0x01010101, 
	0x10101010,
	0x01010101, 
	0x10101010, 
      }
    },
    {
      { 
	0x01001001, 
	0x00000000,
	0x00000000,
	0x01001001, 
	0x00000000,
	0x00000000,
	0x01001001, 
	0x00000000,
      }
    },
    {
      { 
	0x00010001, 
	0x00000000,
	0x00000000,
	0x00000000,
	0x00010001, 
	0x00000000,
	0x00000000,
	0x00000000,
      }
    },
    {
      { 
	0x11111111, 
	0x11000011, 
	0x10000001, 
	0x10000001, 
	0x10000001, 
	0x10000001, 
	0x11000011, 
	0x11111111, 
      }
    },
  };

  REG_BACKGROUND0_CONTROL.charblock_index = 0;
  REG_BACKGROUND0_CONTROL.screenblock_index = SBB_0;
  REG_BACKGROUND0_CONTROL.size = REGULAR_SIZE_64_64;
  REG_BACKGROUND0_CONTROL.enable_mosaic = TRUE;
  REG_BACKGROUND0_OFFSET.X = 24 * 8;
  REG_BACKGROUND0_OFFSET.Y = 24 * 8;

  MEM_TILE[0][0] = tiles[0];
  MEM_TILE[0][1] = tiles[1];
  MEM_TILE[0][2] = tiles[2];
  MEM_TILE[0][3] = tiles[3];

  for(ii = 0 ;
      ii < 4 ;
      ii ++) {

    screen_entry_t temp = {{0}};
    temp.tile_index = ii;
    temp.palblock_index = ii;
    for(jj = 0 ;
	jj < 1024 ; /* 32x32 */
	jj++) {

      sce->raw_data = temp.raw_data;
      sce++;

    }

  }

}

void init_object(void) {

  int i;
  const tile_t tiles[] = 
    {
      {
	{ 
	  0x02020202, 
	  0x20202020,
	  0x02020202, 
	  0x20202020,
	  0x02020202, 
	  0x20202020,
	  0x02020202, 
	  0x20202020, 
	}
      },
      {
	{ 
	  0x03003003, 
	  0x00000000,
	  0x00000000,
	  0x03003003, 
	  0x00000000,
	  0x00000000,
	  0x03003003, 
	  0x00000000,
	}
      },
      {
	{ 
	  0x00040004, 
	  0x00000000,
	  0x00000000,
	  0x00000000,
	  0x00040004, 
	  0x00000000,
	  0x00000000,
	  0x00000000,
	}
      },
      {
	{ 
	  0x11111111, 
	  0x11000011,
	  0x10000001, 
	  0x10000001,
	  0x10000001, 
	  0x10000001,
	  0x11000011, 
	  0x11111111,
	}
      },
    };

  object_init(object_buffer,OBJECT_MAX);
  object_copy(MEM_OBJECT,object_buffer,OBJECT_MAX);

  object_attribute_buffer[0].X = 124;
  object_attribute_buffer[0].Y = 84;
  object_attribute_buffer[0].size = SIZE_32;
  object_attribute_buffer[0].shape = SHAPE_SQUARE;
  object_attribute_buffer[0].palblock_index = 0;
  object_attribute_buffer[0].base_tile_index = 0;
  object_attribute_buffer[0].mode = MODE_NORMAL;
  object_attribute_buffer[0].gfx_mode = GFX_MODE_BLEND;
  object_attribute_buffer[0].enable_mosaic = TRUE;
  object_copy(MEM_OBJECT,object_buffer,1);

  for(i = 0 ; i < 64 ; i++) {

    MEM_TILE[CHARBLOCK_OBJECT][i] = tiles[i/4];

  }

}

void update_mosaic(void) {

  mosaic_control_t temp = { 0, 0, 0, 0 };

  bg.dx = MAX(MIN(bg.dx,3),0);
  bg.dy = MAX(MIN(bg.dy,3),0);
  ob.dx = MAX(MIN(ob.dx,3),0);
  ob.dy = MAX(MIN(ob.dy,3),0);

  temp.background_x = bg.dx;
  temp.background_y = bg.dy;
  temp.object_x = ob.dx;
  temp.object_y = ob.dy;

  REG_MOSAIC_CONTROL = temp;

}

void update_blend(void) {

  blend_alpha_t temp_a = { 0, 0, };
  blend_fade_t temp_y = { 0, };

  ev.a = MAX(MIN(ev.a,16),0);
  ev.b = MAX(MIN(ev.b,16),0);
  ev.y = MAX(MIN(ev.y,16),0);

  temp_a.A_blend = ev.a;
  temp_a.B_blend = ev.b;
  temp_y.fade = ev.y;

  REG_BLEND_ALPHA = temp_a;
  REG_BLEND_FADE = temp_y;

}

void update_window(void) {

  win.l = MAX(MIN(win.l,240),0);
  win.r = MAX(MIN(win.r,240),0);
  win.t = MAX(MIN(win.t,160),0);
  win.b = MAX(MIN(win.b,160),0);

  REG_WINDOW0_LR_BOUND.low = win.l;
  REG_WINDOW0_LR_BOUND.high = win.r;
  REG_WINDOW0_TB_BOUND.low = win.t;
  REG_WINDOW0_TB_BOUND.high = win.b;

}

int main(void) {

  busy_wait_vsync();

  memset(MEM_TILE,0,CHARBLOCK_MAX * sizeof(charblock_4bpp_t));

  init_palette();
  init_map();
  init_object();

  display_control_init();
  REG_DISPLAY_CONTROL.render_background0 = TRUE;
  REG_DISPLAY_CONTROL.object_mapping_mode = MAPPING_1D;
  REG_DISPLAY_CONTROL.render_object = TRUE;
  REG_DISPLAY_CONTROL.render_window0 = TRUE;
  REG_BLEND_CONTROL.B_background0 = 1;
  REG_BLEND_CONTROL.A_object = 1;
  REG_BLEND_CONTROL.mode = BLEND_STANDARD;
  REG_WINDOW_I_CONTROL.win0_background0 = TRUE;
  REG_WINDOW_I_CONTROL.win0_object = TRUE;

  while(1) {

    busy_wait_vsync();

    input_poll();

    if(input_hit_status.start) {

      bg.dx = 0;
      bg.dy = 0;
      ob.dx = 0;
      ob.dy = 0;
      ev.a = 0;
      ev.b = 0;
      ev.y = 0;

    }
    if(input_hit_status.A) {

      REG_BLEND_CONTROL.mode = (REG_BLEND_CONTROL.mode + 1) % 4;

    }
    if(input_hit_status.A) {

      REG_BLEND_CONTROL.mode = (REG_BLEND_CONTROL.mode + 1) % 4;

    }
    if(KEY_DOWN == input_current_status.B) {

      if(KEY_DOWN == input_current_status.right) {

	win.l++;

      }
      else if(KEY_DOWN == input_current_status.left) {

	win.l--;

      }
      if(KEY_DOWN == input_current_status.down) {

	win.t++;

      }
      else if(KEY_DOWN == input_current_status.up) {

	win.t--;

      }
      if(input_hit_status.L) {

	REG_WINDOW_I_CONTROL.win0_background0 = 
	  (REG_WINDOW_I_CONTROL.win0_background0 + 1) %2;

      }
      if(input_hit_status.R) {

	REG_WINDOW_I_CONTROL.win0_object = 
	  (REG_WINDOW_I_CONTROL.win0_object + 1) %2;

      }

    }
    else if(KEY_DOWN == input_current_status.select) {

      if(KEY_DOWN == input_current_status.right) {

	ev.a++;

      }
      else if(KEY_DOWN == input_current_status.left) {

	ev.a--;

      }
      if(KEY_DOWN == input_current_status.down) {

	ev.b++;

      }
      else if(KEY_DOWN == input_current_status.up) {

	ev.b--;

      }
      if(KEY_DOWN == input_current_status.L) {

	ev.y++;

      }
      else if(KEY_DOWN == input_current_status.R) {

	ev.y--;

      }

    }
    else {

      if(input_hit_status.right) {

	bg.dx++;
	ob.dx++;

      }
      else if(input_hit_status.left) {

	bg.dx--;
	ob.dx--;

      }
      if(input_hit_status.down) {

	bg.dy++;
	ob.dy++;

      }
      else if(input_hit_status.up) {

	bg.dy--;
	ob.dy--;

      }

    }
    update_window();
    update_blend();
    update_mosaic();

  }
  return 0;

}
