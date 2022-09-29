function sus {
	echo "sussing $1 -> $2"
	./automogus.elf $1 $2 || exit 1
	gcc $2 -o $3 -I. || exit 1
}

gcc automogus.c -o automogus.elf -I. -g

sus example/emu.c example/emu.sus.c example/emu.elf
sus example/fib.c example/fib.sus.c example/fib.elf
sus example/microcode.c example/microcode.sus.c example/microcode.elf