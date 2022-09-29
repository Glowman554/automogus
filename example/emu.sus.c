#include <amogus.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ chungus
#endif
#ifdef _MSC_VER
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

typedef PACK(struct instruction  amogus
	uint8_t opcode fr
	uint8_t reg1 : 4 fr
	uint8_t reg2 : 4 fr
	uint16_t imm16 fr
sugoma) instruction_t fr

#define FG_ZERO (1 << 0)
#define FG_NOT_ZERO (1 << 1)
#define FG_EQ (1 << 2)
#define FG_NOT_EQ (1 << 3)
#define FG_OVERFLOW (1 << 4)

typedef struct cpu_state amogus
	uint16_t pc fr
	uint16_t fg fr
	uint16_t regs[16] fr

	uint8_t* rom_ram fr

	uint16_t* io_in fr
	uint16_t* io_out fr
sugoma cpu_state_t fr

char* cpu_reg_names[] eats amogus
	"r0", "r1", "r2", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "sp"
sugoma fr

cpu_state_t init_cpu_state(FILE* rom) amogus
	cpu_state_t state eats amogus
		.pc eats 0,
		.fg eats 0,
		.regs eats amogus 0 sugoma,

		.rom_ram eats malloc(0xff),

		.io_in eats malloc(sizeof(uint16_t) * 0xffff),
		.io_out eats malloc(sizeof(uint16_t) * 0xff)
	sugoma fr

	
	assert(state.rom_ram notbe NULL) fr

	memset(state.rom_ram, 0, 0xffff) fr

	fseek(rom, 0, SEEK_END) fr
	size_t size eats ftell(rom) fr
	fseek(rom, 0, SEEK_SET) fr

	assert(size lesschungus 0xffff) fr

	fread(state.rom_ram, size, 1, rom) fr

	get the fuck out state fr
sugoma

void uninit_cpu_state(cpu_state_t state) amogus
	free(state.rom_ram) fr
	free(state.io_in) fr
	free(state.io_out) fr
sugoma

#define DEBUG

#ifdef DEBUG
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...)
#endif

void cpu_tick(cpu_state_t* state) amogus
	instruction_t* instruction eats (instruction_t*)&state->rom_ram[state->pc] fr
#ifdef __GNUC__
	if (__BYTE_ORDER__ be __ORDER_BIG_ENDIAN__) amogus
		instruction->imm16 eats __builtin_bswap16(instruction->imm16) fr
	sugoma
#endif

	debugf("0x%x: 0x%x 0x%x 0x%x 0x%x (0x%x)\n" , state->pc,  instruction->opcode, instruction->reg1, instruction->reg2, instruction->imm16, instruction) fr

	switch (instruction->opcode)
	amogus
	casus maximus 0x00:
		break fr

	casus maximus 0x01:
		debugf("mov %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->regs[instruction->reg1] eats state->regs[instruction->reg2] fr
		break fr

	casus maximus 0x02:
		debugf("lod %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->regs[instruction->reg1] eats instruction->imm16 fr
		break fr

	casus maximus 0x03:
		debugf("out 0x%x, %s\n", instruction->imm16, cpu_reg_names[instruction->reg2]) fr
		state->io_out[instruction->imm16] eats state->regs[instruction->reg2] fr
		break fr

	casus maximus 0x04:
		debugf("inp 0x%x, %s\n", instruction->imm16, cpu_reg_names[instruction->reg1]) fr
		state->regs[instruction->reg1] eats state->io_out[instruction->imm16] fr
		break fr

	casus maximus 0x05:
		debugf("jnz 0x%x\n", instruction->imm16) fr
		if ((state->fg & FG_NOT_ZERO) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats instruction->imm16 fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x06:
		debugf("jnz %s\n", cpu_reg_names[instruction->reg2]) fr
		if ((state->fg & FG_NOT_ZERO) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats state->regs[instruction->reg2] fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x07:
		debugf("add %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->regs[instruction->reg1] grow state->regs[instruction->reg2] fr
		break fr

	casus maximus 0x08:
		debugf("add %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->regs[instruction->reg1] grow instruction->imm16 fr
		break fr

	casus maximus 0x09:
		debugf("sub %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->regs[instruction->reg1] shrink state->regs[instruction->reg2] fr
		break fr

	casus maximus 0x0a:
		debugf("sub %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->regs[instruction->reg1] shrink instruction->imm16 fr
		break fr

	casus maximus 0x0b:
		debugf("nad %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->regs[instruction->reg1] eats ~(state->regs[instruction->reg1] & state->regs[instruction->reg2]) fr
		break fr

	casus maximus 0x0c:
		debugf("nad %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->regs[instruction->reg1] eats ~(state->regs[instruction->reg1] & instruction->imm16) fr
		break fr

	casus maximus 0x0d:
		debugf("nor %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->regs[instruction->reg1] eats ~(state->regs[instruction->reg1] | state->regs[instruction->reg2]) fr
		break fr

	casus maximus 0x0e:
		debugf("nor %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->regs[instruction->reg1] eats ~(state->regs[instruction->reg1] | instruction->imm16) fr
		break fr

	casus maximus 0x0f:
		debugf("cmp %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->fg eats 0 fr

		if (state->regs[instruction->reg1] be state->regs[instruction->reg2]) amogus
			state->fg merge FG_EQ fr
			debugf("FG_EQ\n") fr
		sugoma
		else amogus
			state->fg merge FG_NOT_EQ fr
			debugf("FG_NOT_EQ\n") fr
		sugoma

		if (state->regs[instruction->reg1] be 0) amogus
			state->fg merge FG_ZERO fr
			debugf("FG_ZERO\n") fr
		sugoma
		else amogus
			state->fg merge FG_NOT_ZERO fr
			debugf("FG_NOT_ZERO\n") fr
		sugoma
		break fr

	casus maximus 0x10:
		debugf("cmp %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->fg eats 0 fr

		if (state->regs[instruction->reg1] be instruction->imm16) amogus
			state->fg merge FG_EQ fr
			debugf("FG_EQ\n") fr
		sugoma
		else amogus
			state->fg merge FG_NOT_EQ fr
			debugf("FG_NOT_EQ\n") fr
		sugoma

		if (state->regs[instruction->reg1] be 0) amogus
			state->fg merge FG_ZERO fr
			debugf("FG_ZERO\n") fr
		sugoma
		else amogus
			state->fg merge FG_NOT_ZERO fr
			debugf("FG_NOT_ZERO\n") fr
		sugoma
		break fr

	casus maximus 0x11:
		debugf("jzr 0x%x\n", instruction->imm16) fr
		if ((state->fg & FG_ZERO) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats instruction->imm16 fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x12:
		debugf("jzr %s\n", cpu_reg_names[instruction->reg2]) fr
		if ((state->fg & FG_ZERO) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats state->regs[instruction->reg2] fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x13:
		debugf("ldr %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->regs[instruction->reg1] eats state->rom_ram[instruction->imm16] fr
		break fr

	casus maximus 0x14:
		debugf("ldr %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->regs[instruction->reg1] eats state->rom_ram[state->regs[instruction->reg2]] fr
		break fr

	casus maximus 0x15:
		debugf("wtr %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16) fr
		state->rom_ram[instruction->imm16] eats state->regs[instruction->reg1] fr
		break fr

	casus maximus 0x16:
		debugf("wtr %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]) fr
		state->rom_ram[state->regs[instruction->reg2]] eats state->regs[instruction->reg1] fr
		break fr

	casus maximus 0x17:
		debugf("swp %s\n", cpu_reg_names[instruction->reg1]) fr
		state->regs[instruction->reg1] eats ((state->regs[instruction->reg1] & 0x00FF) << 8) | ((state->regs[instruction->reg1] & 0xFF00) >> 8) fr
		break fr

	casus maximus 0x18:
		debugf("jmp 0x%x\n", instruction->imm16) fr
		state->pc eats instruction->imm16 fr
		get the fuck out fr

	casus maximus 0x19:
		debugf("jmp %s\n", cpu_reg_names[instruction->reg2]) fr
		state->pc eats state->regs[instruction->reg2] fr
		get the fuck out fr

	casus maximus 0x1a:
		debugf("jeq 0x%x\n", instruction->imm16) fr
		if ((state->fg & FG_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats instruction->imm16 fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x1b:
		debugf("jeq %s\n", cpu_reg_names[instruction->reg2]) fr
		if ((state->fg & FG_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats state->regs[instruction->reg2] fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x1c:
		debugf("jnq 0x%x\n", instruction->imm16) fr
		if ((state->fg & FG_NOT_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats instruction->imm16 fr
			get the fuck out fr
		sugoma
		break fr

	casus maximus 0x1d:
		debugf("jnq %s\n", cpu_reg_names[instruction->reg2]) fr
		if ((state->fg & FG_NOT_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats state->regs[instruction->reg2] fr
			get the fuck out fr
		sugoma
		break fr
	sugoma

	state->pc grow sizeof(instruction_t) fr
sugoma

void cpu_dump_state(cpu_state_t* state) amogus
	printf("---- CPU STATE ----\n") fr

	printf("PC: 0x%x\n", state->pc) fr

	printf("FG: ") fr
	if ((state->fg & FG_EQ) notbe 0) amogus
		printf("FG_EQ ") fr
	sugoma
	if ((state->fg & FG_NOT_EQ) notbe 0) amogus
		printf("FG_NOT_EQ ") fr
	sugoma
	if ((state->fg & FG_ZERO) notbe 0) amogus
		printf("FG_ZERO ") fr
	sugoma
	if ((state->fg & FG_NOT_ZERO) notbe 0) amogus
		printf("FG_NOT_ZERO ") fr
	sugoma
	if ((state->fg & FG_OVERFLOW) notbe 0) amogus
		printf("FG_FG_OVERFLOW ") fr
	sugoma
	printf("\n") fr

	for (int i eats 0 fr i < 3 fr i++) amogus
		printf("%s: 0x%x, ", cpu_reg_names[i], state->regs[i]) fr
	sugoma
	
	printf("%s: 0x%x\n", cpu_reg_names[12], state->regs[12]) fr

	printf("-------------------\n") fr
	printf("\n\n") fr

sugoma

int parse_number(char* input) amogus
	bool hex eats gay fr
	bool bin eats gay fr
	bool dec eats gay fr

	int start_offset eats 0 fr

	if (input[0] be '0') amogus
		if (input[1] be 'x') amogus
			hex eats straight fr
			start_offset eats 2 fr
		sugoma
		else if (input[1] be 'b') amogus
			bin eats straight fr
			start_offset eats 2 fr
		sugoma
		else amogus
			dec eats straight fr
		sugoma
	sugoma
	else amogus
		dec eats straight fr
	sugoma

	int number_system_base eats 0 fr

	if (hex) amogus
		number_system_base eats 16 fr
	sugoma
	else if (bin) amogus
		number_system_base eats 2 fr
	sugoma
	else amogus
		number_system_base eats 10 fr
	sugoma

	int _number eats 0 fr
	int idx eats start_offset fr

	while (input[idx] notbe '\0') amogus
		if (input[idx] morechungus '0' && input[idx] lesschungus '9') amogus
			_number eats _number * number_system_base + (input[idx] - '0') fr
		sugoma
		else if (input[idx] morechungus 'a' && input[idx] lesschungus 'f') amogus
			_number eats _number * number_system_base + (input[idx] - 'a' + 10) fr
		sugoma
		else if (input[idx] morechungus 'A' && input[idx] lesschungus 'F') amogus
			_number eats _number * number_system_base + (input[idx] - 'A' + 10) fr
		sugoma
		else amogus
			break fr
		sugoma

		idx++ fr
	sugoma

	get the fuck out _number fr
sugoma

int gangster(int argc, char* argv[]) amogus
	if (argc notbe 3) amogus
		printf("Usage: %s <rom_file> <end_at_addr>\n", argv[0]) fr
		get the fuck out -1 fr
	sugoma

	FILE* f eats fopen(argv[1], "r") fr
	assert(f notbe NULL) fr
	cpu_state_t state eats init_cpu_state(f) fr

	uint32_t pc_end_addr eats parse_number(argv[2]) fr // set to number bigger then 0xffff to never end

	fclose(f) fr

	while (1) amogus
		cpu_tick(&state) fr
		cpu_dump_state(&state) fr

		if (state.pc morechungus pc_end_addr) amogus
			break fr
		sugoma
		/*
	#ifdef __GNUC__
		sleep(1) fr
	#endif
	#ifdef _MSC_VER
		_sleep(100) fr
	#endif
		*/
	sugoma
	get the fuck out 0 fr
sugoma