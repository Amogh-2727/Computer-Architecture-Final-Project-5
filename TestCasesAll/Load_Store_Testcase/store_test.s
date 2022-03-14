        lui a7,912092
        addi a7,a7,-273
        sb a7,100(zero)
        lbu a0,100(zero)
        sh a7,100(zero)        
        lhu a1,100(zero)
        sw a7,100(zero)        
        lw a2,100(zero)               
        sw a5,-4(zero)       #out of bounds     
        jr ra

        #expected output
        #sb - 0xef
        #sh - 0xbeef
        #sw - 0xdeadbeef
        #sw -4(0) - out of bounds