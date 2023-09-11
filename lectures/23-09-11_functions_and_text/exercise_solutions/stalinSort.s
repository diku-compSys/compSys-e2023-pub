.data
array:
	.word 2
	.word 10
	.word 3
	.word 6
	.word 11
	.word 5
	.word 100

.text 
init:
	la a0, array
	li a1, 7
	jal ra, Stalin
	jal zero, end

Stalin:

    bge zero, a1, stalinZero
    lw t0, 0(a0)            # t0 = prev
    li t1, 1                # t1 = i
    li t2 , 0               # t2 = j
stalinLoop:
    addi t2,t2 1 	        # t2 = j ++		  
    bge t2, a1, loopend     # j > n
    slli t3, t2, 2	        # t3 = j * 4
    add t3, t3, a0	        # t3 =&A[j]
    lw  t3, 0(t3)	        # t3 = A[J]
    bgt t0, t3, stalinLoop  # prev > t3
    add t0, t3, zero	    # t0 = A[J] (prev = A[J])
    slli t3, t1, 2	        # t3 = i *4
    add t3, t3, a0	        # t3 = &A[i]
    sw t0, 0(t3)	        # A[i] = A[j](A[j] = prev]	
    addi t1, t1, 1          # t1 = i++
    jal zero, stalinLoop
loopend:
    add a0, t1, zero 	    # A0 = i (return i)
    jal zero, return


stalinZero:
    li a0, 0	            # A0 = 0 (n <= 0)

return:
    jalr zero, ra, 0

end: