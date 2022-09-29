deno run -A automogus.js example/emu.c
gcc example/emu.sus.c -o example/emu.elf -I.

deno run -A automogus.js example/fib.c
gcc example/fib.sus.c -o example/fib.elf -I.
