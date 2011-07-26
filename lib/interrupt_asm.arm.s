	.section .iwram, "ax", %progbits
	.arm
	.align
	.global	interrupt_vector_reentrant_handler
interrupt_vector_reentrant_handler:
	@ r0 = &REG_INTERRUPT_ENABLE
	mov 	r0, #0x04000000
	@ ip = REG_INTERRUPT_ENABLE
	ldr	ip, [r0, #0x200]!
	@ r2 = REG_INTERRUPT_ENABLE & REG_INTERRUPT_FLAG
	and	r2, ip, ip, lsr #16
	@ REG_INTERRUPT_FLAG = r2
	strh	r2, [r0, #2]
	@ REG_INTERRUPT_FLAG_BIOS |= r2
	ldr	r3, [r0, #-208]
	orr	r3, r3, r2
	str	r3, [r0, #-208]

	ldr	r1, =interrupt_vector
	movs	r3, r2
.Lirq_search:
		@cmp	r3, #0
		beq	.Lpost_search
		movs	r3, r3, lsr #1
		addcc	r1, r1, #4
		bcc	.Lirq_search
.Lpost_search:
	ldrcs	r1, [r1]
	cmpcs	r1, #0
	bxeq	lr

	@r3 = REG_INTERRUPT_MASTER_ENABLE
	ldr	r3, [r0, #8]
	@ REG_INTERRUPT_MASTER_ENABLE = 0
	strb	r0, [r0, #8]
	@ REG_INTERRUPT_ENABLE &= ~r2
	bic	r2, ip, r2
	strh	r2, [r0]

	@ stack interrupt's {sprs, IME, IE&IF, lr}
	mrs	r2, spsr
	stmfd	sp!, {r2-r3, ip, lr}

	@ returns to user mode
	mrs	r3, cpsr
	bic	r3, r3, #0xDF
	orr	r3, r3, #0x1F
	msr	cpsr, r3

	@ stack user's {r0, lr}
	stmfd 	sp!, {r0, lr}
	@ calls vector
	mov	lr, pc
	bx	r1
	@ restore user's {r0, lr}
	ldmfd	sp!, {r0, lr}

	@ REG_INTERRUPT_MASTER_ENABLE = 0
	strb	r0, [r0, #8]
	@ returns to irq mode
	mrs	r3, cpsr
	bic	r3, r3, #0xDF
	orr	r3, r3, #0x92
	msr	cpsr, r3

	@ restore interrupt's {sprs, IME, IE&IF, lr}
	ldmfd	sp!, {r2-r3, ip, lr}
	msr	spsr, r2
	strh	ip, [r0]
	str	r3, [r0, #8]
	
	bx 	lr
	