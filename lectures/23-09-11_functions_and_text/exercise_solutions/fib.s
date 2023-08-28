init:
        li a0, 7
        jal ra, fib
        jal zero, end

fib:
        addi sp, sp, -12
        sw ra, 8(sp)
        sw a0, 4(sp)
        li t0, 3
        blt a0, t0, base
        addi a0, a0, -1
        jal ra, fib
        sw a0, 0(sp)
        lw a0, 4(sp)
        addi a0, a0, -2
        jal ra, fib
        lw t0, 0(sp)
        add a0, t0, a0
        jal zero, return
base:
        li a0, 1
return:
        lw ra, 8(sp)
        addi sp, sp, 12
        jalr zero, ra, 0

end:
