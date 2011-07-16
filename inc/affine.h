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

  sfixe a;
  sfixe b;
  sfixe c;
  sfixe d;

} affine_matrix_t;

extern affine_t const identity;
extern affine_matrix_t const matrix_identity;

INLINE void affine_matrix_rot(angle rot,
			      affine_matrix_t *base) {
  
  sfixe _cos_rot = cosinus(rot);
  sfixe _sin_rot = sinus(rot);
  affine_matrix_t temp = { 
    smul(base->a, _cos_rot) - smul(base->c, _sin_rot),
    smul(base->b, _cos_rot) - smul(base->d, _sin_rot),
    smul(base->a, _sin_rot) + smul(base->c, _cos_rot),
    smul(base->b, _sin_rot) + smul(base->d, _cos_rot),
  };

  *base = temp;
  
}

INLINE void affine_matrix_scale(sfixe dx,sfixe dy,
				affine_matrix_t *base) {

  base->a = fmul(base->a, dx);
  base->b = fmul(base->b, dx);
  base->c = fmul(base->c, dy);
  base->d = fmul(base->d, dy);

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

INLINE void affine_matrix_to_object(object_affine_t *obj_affine,
				    affine_matrix_t *affine_mat) {

  obj_affine->attr0 = affine_mat->a;
  obj_affine->attr1 = affine_mat->b;
  obj_affine->attr2 = affine_mat->c;
  obj_affine->attr3 = affine_mat->d;

}

INLINE void affine_matrix_to_background(background_affine_t *bgd_affine,
					affine_matrix_t *affine_mat) {

  bgd_affine->attr0 = affine_mat->a;
  bgd_affine->attr1 = affine_mat->b;
  bgd_affine->attr2 = affine_mat->c;
  bgd_affine->attr3 = affine_mat->d;

}

INLINE void affine_to_matrix(affine_matrix_t *affine_mat,
			     affine_t *affine) {

  *affine_mat = matrix_identity;

  affine_matrix_rot(affine->rotation,
  		    affine_mat);
  affine_matrix_scale(affine->scale.x,
		      affine->scale.y,
		      affine_mat);
  affine_matrix_shear(affine->shear.x,
  		      affine->shear.y,
  		      affine_mat);

}

INLINE void invert_matrix(affine_matrix_t *inv,
			  affine_matrix_t *mat) {

  sfixe det = fmul(mat->a, mat->d) - fmul(mat->b, mat->c);
  inv->a = fdiv(mat->d,det);
  inv->b = - fdiv(mat->b,det);
  inv->c = - fdiv(mat->c,det);
  inv->d = fdiv(mat->a,det);

}

INLINE void affine_to_object(object_affine_attribute_t *obj_attr,
			     object_affine_t *obj_affine,
			     affine_t *affine) {

  affine_matrix_t temp = matrix_identity;
  affine_matrix_t temp_inv = matrix_identity;
  s32 module = (MODE_AFFINE_DOUBLE == obj_attr->mode) ? 0 : 1;
  u32 size_x = object_sizes[obj_attr->size][obj_attr->shape][0];
  u32 size_y = object_sizes[obj_attr->size][obj_attr->shape][1];
  s32 screen_anchor_x = fint(affine->screen_anchor.x) - (size_x >> module);
  s32 screen_anchor_y = fint(affine->screen_anchor.y) - (size_y >> module);
  s32 map_anchor_x = fint(affine->map_anchor.x) - (size_x >> 1);
  s32 map_anchor_y = fint(affine->map_anchor.y) - (size_y >> 1);

  affine_to_matrix(&temp,
		   affine);
  invert_matrix(&temp_inv,
		&temp);

  obj_attr->X = screen_anchor_x
    - (fmul(temp_inv.a, map_anchor_x) + fmul(temp_inv.b, map_anchor_y));
  obj_attr->Y = screen_anchor_y
    - (fmul(temp_inv.c, map_anchor_x) + fmul(temp_inv.d, map_anchor_y));

  affine_matrix_to_object(obj_affine,
			  &temp);

}

INLINE void affine_to_background(background_affine_t *bkg_affine,
				 affine_t *affine) {

  affine_matrix_t temp = matrix_identity;

  affine_to_matrix(&temp,
		   affine);

  affine_matrix_to_background(bkg_affine,
			      &temp);

  bkg_affine->dx = affine->map_anchor.x - 
    (fmul(temp.a,affine->screen_anchor.x) + fmul(temp.b,affine->screen_anchor.y));
  bkg_affine->dy = affine->map_anchor.y - 
    (fmul(temp.c,affine->screen_anchor.x) + fmul(temp.d,affine->screen_anchor.y));

}

#endif
