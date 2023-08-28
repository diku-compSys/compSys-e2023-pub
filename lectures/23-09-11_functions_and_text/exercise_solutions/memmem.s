.data
haystack:
	.byte 1
	.byte 2
	.byte 3
	.byte 4
	.byte 5
	.byte 6
	
needle1:
	.byte 4
	.byte 5
	.byte 7

needle2:
	.byte 1
	.byte 2
	.byte 3

needle3:
	.byte 4
	.byte 5
	.byte 6

.text
init:
	la a0, haystack
	li a1, 6
	la a2, needle3
	li a3, 3
	jal ra, memmem
	jal zero, end
	
# We need memeq as a helper function.
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

memmem:
	addi sp, sp, -24
	sw ra, 0(sp)
	sw s0, 4(sp)
	sw s1, 8(sp)
	sw s2, 12(sp)
	sw s3, 16(sp)
	sw s4, 20(sp)
	# We copy all 'a' registers to 's' because we will need the 'a' registers for calling memeq.
	mv s0, a0 # s0 = haystack
	mv s1, a1 # s1 = haystacklen
	mv s2, a2 # s2 = needle
	mv s3, a3 # s3 = needlelen
	# storing i in s4
	li s4, 0
memmem_loop:
	sub t0, s1, s3 # t0 = haystacklen - needlelen
	blt t0, s4, memmem_not_found # exit if haystacklen - needlelen < i
	# now we have to call memeq
	add a0, s0, s4 # a0 = haystack + i
	mv a1, s2 # a1 = needle
	mv a2, s3 # a2 = needlelen
	jal ra, memeq
	# check if we had a match
	bne a0, zero, memmem_found
	addi s4, s4, 1
	jal zero, memmem_loop
memmem_found:
	add a0, s0, s4 # Return haystack + i
	jal zero, memmem_return
memmem_not_found:
	li a0, 0
memmem_return:
	lw s4, 20(sp)
	lw s3, 16(sp)
	lw s2, 12(sp)
	lw s1, 8(sp)
	lw s0, 4(sp)
	lw ra, 0(sp)
	addi sp, sp, 24
	jalr zero, ra, 0

end:
