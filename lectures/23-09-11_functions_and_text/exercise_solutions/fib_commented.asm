# fib(n) = if n < 2 then 1 else fib(n-1) + fib(n-2)


init:
	li, a0, 20 #Load 5 into arg register a0, i.e. n, return value also placed in a0
	jal ra, fib
	jal zero, end
	
fib:
	addi sp, sp, -12 #Store caller saves regs a0 and ra
	sw ra, 8(sp) #Remember stack grows from top to bottom, i.e. sp points to top elem of stack
	sw a0, 4(sp) #Store value of n
	li x5, 2 #Temporary callee
	blt, a0, x5, fib_base #If n < 2 then go to base case
	addi a0, a0, -1 #Param now set to n-1
	
	jal ra, fib #Recursive call to to fib with a0 param now (n-1)
	sw a0, 0(sp) #Save result of 1st recursive call in memory
	lw a0, 4(sp) #Load again n into memory
	addi, a0, a0, -2
	jal ra, fib #Call fib with parameter n-2
	lw x5, 0(sp) #Load result of 1st recursive call into temp reg
	add, a0, a0, x5 #Add results from fib(n-1) + fib(n-2)
	jal x0, fib_return #Exit procedure

fib_base:
	li a0, 1 #Base case, return 0
	
fib_return:
	lw ra, 8(sp) #Restore stack pointer 
	addi sp, sp, 12 #Reset stack pointer
	jalr x0, ra, 0 #Jump to ra and Remember cannot link to zero

end:
	#Done
