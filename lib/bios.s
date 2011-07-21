	.section .text
	.thumb

	.align 2
	.global bios_div
	.thumb_func
bios_div:
	swi	0x06
	bx	lr

	.align 2
	.global bios_sqrt
	.thumb_func
bios_sqrt:
	swi	0x08
	bx	lr

	.align 2
	.global bios_atan2
	.thumb_func
bios_atan2:
	swi	0x0A
	bx	lr

	.align 2
	.global bios_wait_vsync
	.thumb_func
bios_wait_vsync:
	swi	0x05
	bx	lr

	.align 2
	.global bios_bg_affine_set
	.thumb_func
bios_bg_affine_set:
	swi	0x0E
	bx	lr

	.align 2
	.global bios_obj_affine_set
	.thumb_func
bios_obj_affine_set:
	swi	0x0F
	bx	lr

