#include <affine.h>

affine_t const identity = { { 0, 0 },
			    { 0, 0 },
			    0, 
			    { fixe(1,0), fixe(1,0) }, 
			    { 0, 0 } };
affine_matrix_t const matrix_identity = { fixe(1,0), fixe(0,0), 
					  fixe(0,0), fixe(1,0) };
