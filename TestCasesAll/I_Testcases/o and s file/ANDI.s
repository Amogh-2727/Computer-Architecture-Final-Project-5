	.file	"ANDI.c"
	.option pic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	li	a5,10
	sw	a5,-20(s0)
	li	a5,-10
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	andi	a5,a5,10
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	andi	a5,a5,-10
	sw	a5,-32(s0)
	lw	a5,-24(s0)
	andi	a5,a5,10
	sw	a5,-36(s0)
	lw	a5,-24(s0)
	andi	a5,a5,-10
	sw	a5,-40(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	and	a5,a4,a5
	sw	a5,-44(s0)
	nop
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
