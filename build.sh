function sus {
	echo sussing $1
	deno run -A automogus.js $1
	gcc $2 -o $3 -I.
}

sus example/emu.c example/emu.sus.c example/emu.elf
sus example/fib.c example/fib.sus.c example/fib.elf
sus example/microcode.c example/microcode.sus.c example/microcode.elf