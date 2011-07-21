#ifndef AFFINE_H_
#define AFFINE_H_

#include <fixed.h>
#include <angle.h>
#include <background.h>
#include <object.h>

typedef struct affine_tag {

  struct {

    sfixe x;
    sfixe y;
    
  } screen_anchor;
  struct {

    sfixe x;
    sfixe y;
    
  } map_anchor;
  angle rotation;
  struct {

    sfixe x;
    sfixe y;

  } scale;
  struct {

    sfixe x;
    sfixe y;
    
  } shear;

} affine_t;

typedef struct affine_matrix_tag {

  s16 a;
  s16 b;
  s16 c;
  s16 d;

} affine_matrix_t;

extern affine_t const identity;
extern affine_matrix_t const matrix_identity;

INLINE void affine_to_bios_obj(bios_obj_affine_t *bios_aff,
			       affine_t *affine) {

  bios_aff->scale_x = affine->scale.x;
  bios_aff->scale_y = affine->scale.y;
  bios_aff->rotation = angle_format(affine->rotation);

}

INLINE void affine_matrix_shear(sfixe hx,sfixe hy,
				affine_matrix_t *base) {

  affine_matrix_t temp = {
    base->a + fmul(base->c, hx),
    base->b + fmul(base->d, hx),
    fmul(base->a, hy) + base->c,
    fmul(base->b, hy) + base->d,
  };
  
  *base = temp;

}

INLINE void invert_matrix(affine_matrix_t *inv,
			  affine_matrix_t *mat) {

  sfixe det = fmul(mat->a, mat->d) - fmul(mat->b, mat->c);
  inv->a = fdiv(mat->d,det);
  inv->b = - fdiv(mat->b,det);
  inv->c = - fdiv(mat->c,det);
  inv->d = fdiv(mat->a,det);

}

INLINE void affine_to_object(object_affine_attribute_t *dst_attr,
			     object_affine_t *dst,
			     affine_t *src,
			     u32 nb_elements) {
  
  u32 i;
  affine_matrix_t matrix[1];
  bios_obj_affine_t temp[1];

  affine_to_bios_obj(temp,
		     src);

  bios_obj_affine_set(temp,
		      matrix,
		      1, 2);

  if(0 != src->shear.x ||
     0 != src->shear.y) {

    affine_matrix_shear(src->shear.x, src->shear.y,
			matrix);

  }

  dst->attr0 = matrix->a;
  dst->attr1 = matrix->b;
  dst->attr2 = matrix->c;
  dst->attr3 = matrix->d;

  for(i = 0 ; i < nb_elements ; i++) {

    s32 module = (MODE_AFFINE_DOUBLE == dst_attr[i].mode) ? 0 : 1;
    u32 size_x = object_sizes[dst_attr[i].size][dst_attr[i].shape][0];
    u32 size_y = object_sizes[dst_attr[i].size][dst_attr[i].shape][1];
    s32 screen_anchor_x = fint(src->screen_anchor.x) - (size_x >> module);
    s32 screen_anchor_y = fint(src->screen_anchor.y) - (size_y >> module);

    dst_attr[i].X = screen_anchor_x;
    dst_attr[i].Y = screen_anchor_y;

    if(0 != src->map_anchor.x ||
       0 != src->map_anchor.y) {

      affine_matrix_t matrix_inv = matrix_identity;
      s32 map_anchor_x = fint(src->map_anchor.x) - (size_x >> 1);
      s32 map_anchor_y = fint(src->map_anchor.y) - (size_y >> 1);

      invert_matrix(&matrix_inv,
		    matrix);
      dst_attr[i].X -= (fmul(matrix_inv.a, map_anchor_x)
		      + fmul(matrix_inv.b, map_anchor_y));
      dst_attr[i].Y -= (fmul(matrix_inv.c, map_anchor_x)
		      + fmul(matrix_inv.d, map_anchor_y));

    }
  
  }

}

INLINE void affine_to_bios_bg(bios_bg_affine_t *bios_aff,
			      affine_t *affine) {

  bios_aff->map_anchor_x = affine->map_anchor.x;
  bios_aff->map_anchor_y = affine->map_anchor.y;
  bios_aff->screen_anchor_x = (affine->screen_anchor.x) >> FIXE_FORMAT;
  bios_aff->screen_anchor_y = (affine->screen_anchor.y) >> FIXE_FORMAT;
  bios_aff->scale_x = affine->scale.x;
  bios_aff->scale_y = affine->scale.y;
  bios_aff->rotation = angle_format(affine->rotation);

}

INLINE void affine_to_background(background_affine_t *dst,
				 affine_t *src,
				 u32 num_elements) {

  u32 i;
  bios_bg_affine_t temp[num_elements];

  for(i = 0 ; i < num_elements ; i++) {

    affine_to_bios_bg(temp + i,
		      src + i);

  }
  bios_bg_affine_set(temp,
		     dst,
		     num_elements);

}

#endif
