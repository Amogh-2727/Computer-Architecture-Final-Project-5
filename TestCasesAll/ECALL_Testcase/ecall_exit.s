        .equ SYS_EXIT, 94

        .section .text
        .align 2

        li a0, 0                # Return code, no error
        li a7, SYS_EXIT         # System call code for write
        ecall
        jr ra