.data
array1:
        .byte 1
        .byte 2
        .byte 3
        .byte 4
        .byte 5
        .byte 6

array2:
        .byte 1
        .byte 2
        .byte 3
        .byte 4
        .byte 5
        .byte 7

.text
init:
        la a0, array1
        la a1, array1
        li a2, 6
        jal ra, memeq
        jal zero, end

# Since memeq is a leaf procedure we do not need to mess with the stack.
# we can change caller-saves (particularly the 't' registers) as we please.
memeq:
        # storing i in t0
        li t0, 0
memeq_loop:
        beq t0, a2, memeq_equal
        # we load the two bytes to compare into t1 and t2
        add t1, a0, t0
        lb t1, 0(t1)
        add t2, a1, t0
        lb t2, 0(t2)
        bne t1, t2, memeq_not_equal
        addi t0, t0, 1
        jal zero, memeq_loop
memeq_not_equal:
        li a0, 0
        jal zero, memeq_return
memeq_equal:
        li a0, 1
memeq_return:
        jalr zero, ra, 0

end:
