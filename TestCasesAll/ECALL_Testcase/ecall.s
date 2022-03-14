 .equ STDIN, 0
        .equ SYS_READ, 63
        .equ MAX_CHARS, 5

        .section .bss
        .align 2

buffer:         .space  256

        .section .text
        .align 2

        li a0, STDIN            # File descriptor, 0 for STDIN
        la a1, buffer           # Address of buffer to store string
        li a2, MAX_CHARS        # Maximum number of chars to store
        li a7, SYS_READ         # System call code for read
        ecall
        li a0, 1                # File descriptor, 1
        li a1, 4                # Address of the message
        li a2, 5                # Length of string
        li a7, 64               # System call code for write
        ecall
        jr ra