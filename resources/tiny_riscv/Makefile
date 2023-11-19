%.riscv: %.c lib.c Makefile
	./gcc -march=rv32im -mabi=ilp32 -fno-tree-loop-distribute-patterns -mno-relax -O1 $< lib.c -static -nostartfiles -nostdlib -o $@

%.dis: %.riscv Makefile
	./objdump -s -w $< > $@
	./objdump -S $< >> $@
