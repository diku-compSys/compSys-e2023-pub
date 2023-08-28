# RARS always begins execution from the top, so we insert a bit of
# testing code that calls our 'fact' procedure with a reasonable
# argument.  We will have to check the result by inspecting the final
# value of 'a0' in the RARS IDE.  By using "environment calls" we
# could also make RARS print it to the screen.

init:
        li a0, 10     # Load 10 into a0
        jal ra, fact  # Call fact procedure
        jal zero, end # Jump to the end, which will make RARS stop.

# The 'mul' procedure multiplies a0 and a1 and leaves the result in
# a0.  Assumes non-negative input.
mul:
        mv a2, a0
        mv a0, zero
mul_loop:
        beq a2, zero, mul_end
        add a0, a0, a1
        addi a2, a2, -1
        jal zero, mul_loop
mul_end:
        jalr zero, ra, 0

# The 'fact' procedure takes a value 'n' in a0 and produces 'n!' in
# a0.  Implemented as a recursive function to demonstrate proper stack
# discipline.
fact:

        # The first thing we should do when entering a procedure is to
        # modify the stack pointer to reserve all the space we will
        # need.  In principle we can also change it later, but that
        # tends to lead to code that is much more difficult to
        # understand.  For this procedure we will need two words (8
        # bytes): one word for the return address 'ra', and another
        # for 'a0', as these are caller-saves registers that will be
        # overwritten in the recursive call.
        addi sp, sp, -8

        # Now we store ra and a0.  Make sure to use different offsets!
        # It is OK to read and write to the stack multiple times in
        # the procedure code.  Think of the stack as scratch space for
        # intermediate data.
        sw ra, 4(sp)
        sw a0, 0(sp)

        # Now we check whether 'n' is zero; the base case in the
        # recursion.  If so we want to return 1 immediately, without
        # recursing.
        beq a0, zero, fact_base

        # We made it past the branch, so n>0.  Now put 'n-1' in a0 and
        # recursively call 'fact'.  Recall that the original value of
        # 'n' is saved on the stack - we will need it later.
        addi a0, a0, -1
        jal ra, fact

        # Restore the original value of 'n' and put it in a1.
        lw a1, 0(sp)

        # a0 stores the result of the recursive call (that is,
        # 'fact(n-1)'), while a1 stores 'n'.  We can multiply these
        # and leave the product in a0 by invoking the 'mul' procedure.
        jal ra, mul

        # Now we just have to skip the code for the base case.
        jal zero, fact_return

fact_base:
        # If this is reached, then n==0.  We load the return value 1
        # into a0.
        li a0, 1

fact_return:
        # Here we return from the function.  This involves loading the
        # return address from where we stored it on the stack, and
        # restoring the stack pointer to the position it had when the
        # procedure was entered.  I find it eases readability when all
        # stack pointer manipulation is done at the very beginning and
        # very end of the procedure.
        lw ra, 4(sp)
        addi sp, sp, 8

        # Return to caller.
        jalr zero, ra, 0

end:
