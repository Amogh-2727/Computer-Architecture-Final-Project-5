	.file	"shitt.c"
	.option pic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,-16
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	srai	a5,a5,3
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	sw	a5,-24(s0)
	li	a5,0
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
