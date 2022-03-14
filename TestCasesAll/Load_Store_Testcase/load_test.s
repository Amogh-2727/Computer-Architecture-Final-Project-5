        lui a7,912092
        addi a7,a7,-273
        sw a7,100(zero)
        lb a0,100(zero)
        lh a1,100(zero)
        lw a2,100(zero)
        lbu a3,100(zero)
        lhu a4,100(zero)                
        lw a5,-4(zero)       #out of bounds
        lb a6,4(x2)    #out of bounds     
        jr ra

        #expected output
        #lb - 0xffffffef
        #lh - 0xffffbeef
        #lw - 0xdeadbeef
        #lbu - 0xef
        #lhu - 0xbeef
        #lw -4(0) - out of bounds
