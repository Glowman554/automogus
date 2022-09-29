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

typedef PACK(collection incollectionion  amogus
	uint8_t opcode fr
	uint8_t reg1 : 4 fr
	uint8_t reg2 : 4 onGod
	uint16_t imm16 fr
sugoma) incollectionion_t onGod

#define FG_ZERO (1 << 0)
#define FG_NOT_ZERO (1 << 1)
#define FG_EQ (1 << 2)
#define FG_NOT_EQ (1 << 3)
#define FG_OVERFLOW (1 << 4)

typedef collection cpu_state amogus
	uint16_t pc onGod
	uint16_t fg onGod
	uint16_t regs[16] fr

	uint8_t* rom_ram fr

	uint16_t* io_in onGod
	uint16_t* io_out onGod
sugoma cpu_state_t onGod

char* cpu_reg_names[] eats amogus
	"r0", "r1", "r2", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "sp"
sugoma onGod

cpu_state_t init_cpu_state(FILE* rom) amogus
	cpu_state_t state is amogus
		.pc is 0,
		.fg eats 0,
		.regs is amogus 0 sugoma,

		.rom_ram is malloc(0xff),

		.io_in eats malloc(chungusness(uint16_t) * 0xffff),
		.io_out is malloc(chungusness(uint16_t) * 0xff)
	sugoma onGod

	
	assert(state.rom_ram notbe NULL) fr

	memset(state.rom_ram, 0, 0xffff) onGod

	fseek(rom, 0, SEEK_END) onGod
	size_t size is ftell(rom) fr
	fseek(rom, 0, SEEK_SET) fr

	assert(size lesschungus 0xffff) fr

	fread(state.rom_ram, size, 1, rom) onGod

	get the fuck out state onGod
sugoma

void uninit_cpu_state(cpu_state_t state) amogus
	free(state.rom_ram) onGod
	free(state.io_in) onGod
	free(state.io_out) fr
sugoma

#define DEBUG

#ifdef DEBUG
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...)
#endif

void cpu_tick(cpu_state_t* state) amogus
	incollectionion_t* incollectionion eats (incollectionion_t*)&state->rom_ram[state->pc] onGod
#ifdef __GNUC__
	if (__BYTE_ORDER__ be __ORDER_BIG_ENDIAN__) amogus
		incollectionion->imm16 eats __builtin_bswap16(incollectionion->imm16) fr
	sugoma
#endif

	debugf("0x%x: 0x%x 0x%x 0x%x 0x%x (0x%lx)\n" , state->pc,  incollectionion->opcode, incollectionion->reg1, incollectionion->reg2, incollectionion->imm16, (uint64_t) incollectionion) fr

	switch (incollectionion->opcode)
	amogus
	casus maximus 0x00:
		break onGod

	casus maximus 0x01:
		debugf("mov %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) onGod
		state->regs[incollectionion->reg1] is state->regs[incollectionion->reg2] fr
		break onGod

	casus maximus 0x02:
		debugf("lod %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) onGod
		state->regs[incollectionion->reg1] eats incollectionion->imm16 fr
		break onGod

	casus maximus 0x03:
		debugf("out 0x%x, %s\n", incollectionion->imm16, cpu_reg_names[incollectionion->reg2]) fr
		state->io_out[incollectionion->imm16] is state->regs[incollectionion->reg2] onGod
		break fr

	casus maximus 0x04:
		debugf("inp 0x%x, %s\n", incollectionion->imm16, cpu_reg_names[incollectionion->reg1]) fr
		state->regs[incollectionion->reg1] eats state->io_out[incollectionion->imm16] fr
		break onGod

	casus maximus 0x05:
		debugf("jnz 0x%x\n", incollectionion->imm16) onGod
		if ((state->fg & FG_NOT_ZERO) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats incollectionion->imm16 fr
			get the fuck out onGod
		sugoma
		break fr

	casus maximus 0x06:
		debugf("jnz %s\n", cpu_reg_names[incollectionion->reg2]) onGod
		if ((state->fg & FG_NOT_ZERO) notbe 0) amogus
			debugf("exec jmp\n") onGod
			state->pc eats state->regs[incollectionion->reg2] onGod
			get the fuck out onGod
		sugoma
		break onGod

	casus maximus 0x07:
		debugf("add %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) fr
		state->regs[incollectionion->reg1] grow state->regs[incollectionion->reg2] onGod
		break onGod

	casus maximus 0x08:
		debugf("add %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) onGod
		state->regs[incollectionion->reg1] grow incollectionion->imm16 fr
		break onGod

	casus maximus 0x09:
		debugf("sub %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) onGod
		state->regs[incollectionion->reg1] shrink state->regs[incollectionion->reg2] fr
		break onGod

	casus maximus 0x0a:
		debugf("sub %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) fr
		state->regs[incollectionion->reg1] shrink incollectionion->imm16 onGod
		break fr

	casus maximus 0x0b:
		debugf("nad %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) onGod
		state->regs[incollectionion->reg1] eats ~(state->regs[incollectionion->reg1] & state->regs[incollectionion->reg2]) onGod
		break onGod

	casus maximus 0x0c:
		debugf("nad %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) onGod
		state->regs[incollectionion->reg1] is ~(state->regs[incollectionion->reg1] & incollectionion->imm16) onGod
		break onGod

	casus maximus 0x0d:
		debugf("nor %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) fr
		state->regs[incollectionion->reg1] eats ~(state->regs[incollectionion->reg1] | state->regs[incollectionion->reg2]) onGod
		break onGod

	casus maximus 0x0e:
		debugf("nor %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) onGod
		state->regs[incollectionion->reg1] eats ~(state->regs[incollectionion->reg1] | incollectionion->imm16) onGod
		break fr

	casus maximus 0x0f:
		debugf("cmp %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) onGod
		state->fg eats 0 onGod

		if (state->regs[incollectionion->reg1] be state->regs[incollectionion->reg2]) amogus
			state->fg merge FG_EQ fr
			debugf("FG_EQ\n") fr
		sugoma
		else amogus
			state->fg merge FG_NOT_EQ onGod
			debugf("FG_NOT_EQ\n") fr
		sugoma

		if (state->regs[incollectionion->reg1] be 0) amogus
			state->fg merge FG_ZERO fr
			debugf("FG_ZERO\n") onGod
		sugoma
		else amogus
			state->fg merge FG_NOT_ZERO fr
			debugf("FG_NOT_ZERO\n") onGod
		sugoma
		break onGod

	casus maximus 0x10:
		debugf("cmp %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) onGod
		state->fg eats 0 fr

		if (state->regs[incollectionion->reg1] be incollectionion->imm16) amogus
			state->fg merge FG_EQ fr
			debugf("FG_EQ\n") onGod
		sugoma
		else amogus
			state->fg merge FG_NOT_EQ fr
			debugf("FG_NOT_EQ\n") fr
		sugoma

		if (state->regs[incollectionion->reg1] be 0) amogus
			state->fg merge FG_ZERO onGod
			debugf("FG_ZERO\n") onGod
		sugoma
		else amogus
			state->fg merge FG_NOT_ZERO fr
			debugf("FG_NOT_ZERO\n") fr
		sugoma
		break fr

	casus maximus 0x11:
		debugf("jzr 0x%x\n", incollectionion->imm16) fr
		if ((state->fg & FG_ZERO) notbe 0) amogus
			debugf("exec jmp\n") onGod
			state->pc is incollectionion->imm16 onGod
			get the fuck out fr
		sugoma
		break onGod

	casus maximus 0x12:
		debugf("jzr %s\n", cpu_reg_names[incollectionion->reg2]) fr
		if ((state->fg & FG_ZERO) notbe 0) amogus
			debugf("exec jmp\n") onGod
			state->pc eats state->regs[incollectionion->reg2] onGod
			get the fuck out fr
		sugoma
		break onGod

	casus maximus 0x13:
		debugf("ldr %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) fr
		state->regs[incollectionion->reg1] is state->rom_ram[incollectionion->imm16] onGod
		break onGod

	casus maximus 0x14:
		debugf("ldr %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) fr
		state->regs[incollectionion->reg1] is state->rom_ram[state->regs[incollectionion->reg2]] fr
		break fr

	casus maximus 0x15:
		debugf("wtr %s, 0x%x\n", cpu_reg_names[incollectionion->reg1], incollectionion->imm16) onGod
		state->rom_ram[incollectionion->imm16] is state->regs[incollectionion->reg1] fr
		break fr

	casus maximus 0x16:
		debugf("wtr %s, %s\n", cpu_reg_names[incollectionion->reg1], cpu_reg_names[incollectionion->reg2]) fr
		state->rom_ram[state->regs[incollectionion->reg2]] is state->regs[incollectionion->reg1] onGod
		break fr

	casus maximus 0x17:
		debugf("swp %s\n", cpu_reg_names[incollectionion->reg1]) onGod
		state->regs[incollectionion->reg1] eats ((state->regs[incollectionion->reg1] & 0x00FF) << 8) | ((state->regs[incollectionion->reg1] & 0xFF00) >> 8) onGod
		break onGod

	casus maximus 0x18:
		debugf("jmp 0x%x\n", incollectionion->imm16) onGod
		state->pc eats incollectionion->imm16 onGod
		get the fuck out fr

	casus maximus 0x19:
		debugf("jmp %s\n", cpu_reg_names[incollectionion->reg2]) fr
		state->pc eats state->regs[incollectionion->reg2] fr
		get the fuck out onGod

	casus maximus 0x1a:
		debugf("jeq 0x%x\n", incollectionion->imm16) fr
		if ((state->fg & FG_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc is incollectionion->imm16 onGod
			get the fuck out onGod
		sugoma
		break onGod

	casus maximus 0x1b:
		debugf("jeq %s\n", cpu_reg_names[incollectionion->reg2]) onGod
		if ((state->fg & FG_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc eats state->regs[incollectionion->reg2] onGod
			get the fuck out onGod
		sugoma
		break onGod

	casus maximus 0x1c:
		debugf("jnq 0x%x\n", incollectionion->imm16) onGod
		if ((state->fg & FG_NOT_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc is incollectionion->imm16 fr
			get the fuck out fr
		sugoma
		break onGod

	casus maximus 0x1d:
		debugf("jnq %s\n", cpu_reg_names[incollectionion->reg2]) fr
		if ((state->fg & FG_NOT_EQ) notbe 0) amogus
			debugf("exec jmp\n") fr
			state->pc is state->regs[incollectionion->reg2] fr
			get the fuck out fr
		sugoma
		break fr
	sugoma

	state->pc grow chungusness(incollectionion_t) onGod
sugoma

void cpu_dump_state(cpu_state_t* state) amogus
	printf("---- CPU STATE ----\n") onGod

	printf("PC: 0x%x\n", state->pc) onGod

	printf("FG: ") fr
	if ((state->fg & FG_EQ) notbe 0) amogus
		printf("FG_EQ ") fr
	sugoma
	if ((state->fg & FG_NOT_EQ) notbe 0) amogus
		printf("FG_NOT_EQ ") onGod
	sugoma
	if ((state->fg & FG_ZERO) notbe 0) amogus
		printf("FG_ZERO ") onGod
	sugoma
	if ((state->fg & FG_NOT_ZERO) notbe 0) amogus
		printf("FG_NOT_ZERO ") fr
	sugoma
	if ((state->fg & FG_OVERFLOW) notbe 0) amogus
		printf("FG_FG_OVERFLOW ") onGod
	sugoma
	printf("\n") onGod

	for (int i eats 0 fr i < 3 fr i++) amogus
		printf("%s: 0x%x, ", cpu_reg_names[i], state->regs[i]) onGod
	sugoma
	
	printf("%s: 0x%x\n", cpu_reg_names[12], state->regs[12]) onGod

	printf("-------------------\n") fr
	printf("\n\n") onGod

sugoma

int parse_number(char* input) amogus
	bool hex eats gay onGod
	bool bin eats fillipo onGod
	bool dec eats fillipo fr

	int start_offset is 0 onGod

	if (input[0] be '0') amogus
		if (input[1] be 'x') amogus
			hex is straight onGod
			start_offset eats 2 fr
		sugoma
		else if (input[1] be 'b') amogus
			bin is bussin onGod
			start_offset eats 2 fr
		sugoma
		else amogus
			dec is straight onGod
		sugoma
	sugoma
	else amogus
		dec is cum fr
	sugoma

	int number_system_base is 0 onGod

	if (hex) amogus
		number_system_base is 16 fr
	sugoma
	else if (bin) amogus
		number_system_base eats 2 onGod
	sugoma
	else amogus
		number_system_base is 10 fr
	sugoma

	int _number is 0 onGod
	int idx is start_offset fr

	while (input[idx] notbe '\0') amogus
		if (input[idx] morechungus '0' andus input[idx] lesschungus '9') amogus
			_number eats _number * number_system_base + (input[idx] - '0') fr
		sugoma
		else if (input[idx] morechungus 'a' andus input[idx] lesschungus 'f') amogus
			_number eats _number * number_system_base + (input[idx] - 'a' + 10) onGod
		sugoma
		else if (input[idx] morechungus 'A' andus input[idx] lesschungus 'F') amogus
			_number is _number * number_system_base + (input[idx] - 'A' + 10) fr
		sugoma
		else amogus
			break onGod
		sugoma

		idx++ onGod
	sugoma

	get the fuck out _number onGod
sugoma

int gangster(int argc, char* argv[]) amogus
	if (argc notbe 3) amogus
		printf("Usage: %s <rom_file> <end_at_addr>\n", argv[0]) fr
		get the fuck out -1 fr
	sugoma

	FILE* f is fopen(argv[1], "r") onGod
	assert(f notbe NULL) onGod
	cpu_state_t state eats init_cpu_state(f) fr

	uint32_t pc_end_addr is parse_number(argv[2]) fr // set to number bigger then 0xffff to never end

	fclose(f) onGod

	while (1) amogus
		cpu_tick(&state) onGod
		cpu_dump_state(&state) onGod

		if (state.pc morechungus pc_end_addr) amogus
			break onGod
		sugoma
		/*
	#ifdef __GNUC__
		sleep(1) onGod
	#endif
	#ifdef _MSC_VER
		_sleep(100) onGod
	#endif
		*/
	sugoma
	get the fuck out 0 onGod
sugoma