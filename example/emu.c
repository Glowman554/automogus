#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((packed))
#endif
#ifdef _MSC_VER
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

typedef PACK(struct instruction  {
	uint8_t opcode;
	uint8_t reg1 : 4;
	uint8_t reg2 : 4;
	uint16_t imm16;
}) instruction_t;

#define FG_ZERO (1 << 0)
#define FG_NOT_ZERO (1 << 1)
#define FG_EQ (1 << 2)
#define FG_NOT_EQ (1 << 3)
#define FG_OVERFLOW (1 << 4)

typedef struct cpu_state {
	uint16_t pc;
	uint16_t fg;
	uint16_t regs[16];

	uint8_t* rom_ram;

	uint16_t* io_in;
	uint16_t* io_out;
} cpu_state_t;

char* cpu_reg_names[] = {
	"r0", "r1", "r2", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "unk", "sp"
};

cpu_state_t init_cpu_state(FILE* rom) {
	cpu_state_t state = {
		.pc = 0,
		.fg = 0,
		.regs = { 0 },

		.rom_ram = malloc(0xff),

		.io_in = malloc(sizeof(uint16_t) * 0xffff),
		.io_out = malloc(sizeof(uint16_t) * 0xff)
	};

	
	assert(state.rom_ram != NULL);

	memset(state.rom_ram, 0, 0xffff);

	fseek(rom, 0, SEEK_END);
	size_t size = ftell(rom);
	fseek(rom, 0, SEEK_SET);

	assert(size <= 0xffff);

	fread(state.rom_ram, size, 1, rom);

	return state;
}

void uninit_cpu_state(cpu_state_t state) {
	free(state.rom_ram);
	free(state.io_in);
	free(state.io_out);
}

#define DEBUG

#ifdef DEBUG
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...)
#endif

void cpu_tick(cpu_state_t* state) {
	instruction_t* instruction = (instruction_t*)&state->rom_ram[state->pc];
#ifdef __GNUC__
	if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) {
		instruction->imm16 = __builtin_bswap16(instruction->imm16);
	}
#endif

	debugf("0x%x: 0x%x 0x%x 0x%x 0x%x (0x%lx)\n" , state->pc,  instruction->opcode, instruction->reg1, instruction->reg2, instruction->imm16, (uint64_t) instruction);

	switch (instruction->opcode)
	{
	case 0x00:
		break;

	case 0x01:
		debugf("mov %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->regs[instruction->reg1] = state->regs[instruction->reg2];
		break;

	case 0x02:
		debugf("lod %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->regs[instruction->reg1] = instruction->imm16;
		break;

	case 0x03:
		debugf("out 0x%x, %s\n", instruction->imm16, cpu_reg_names[instruction->reg2]);
		state->io_out[instruction->imm16] = state->regs[instruction->reg2];
		break;

	case 0x04:
		debugf("inp 0x%x, %s\n", instruction->imm16, cpu_reg_names[instruction->reg1]);
		state->regs[instruction->reg1] = state->io_out[instruction->imm16];
		break;

	case 0x05:
		debugf("jnz 0x%x\n", instruction->imm16);
		if ((state->fg & FG_NOT_ZERO) != 0) {
			debugf("exec jmp\n");
			state->pc = instruction->imm16;
			return;
		}
		break;

	case 0x06:
		debugf("jnz %s\n", cpu_reg_names[instruction->reg2]);
		if ((state->fg & FG_NOT_ZERO) != 0) {
			debugf("exec jmp\n");
			state->pc = state->regs[instruction->reg2];
			return;
		}
		break;

	case 0x07:
		debugf("add %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->regs[instruction->reg1] += state->regs[instruction->reg2];
		break;

	case 0x08:
		debugf("add %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->regs[instruction->reg1] += instruction->imm16;
		break;

	case 0x09:
		debugf("sub %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->regs[instruction->reg1] -= state->regs[instruction->reg2];
		break;

	case 0x0a:
		debugf("sub %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->regs[instruction->reg1] -= instruction->imm16;
		break;

	case 0x0b:
		debugf("nad %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->regs[instruction->reg1] = ~(state->regs[instruction->reg1] & state->regs[instruction->reg2]);
		break;

	case 0x0c:
		debugf("nad %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->regs[instruction->reg1] = ~(state->regs[instruction->reg1] & instruction->imm16);
		break;

	case 0x0d:
		debugf("nor %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->regs[instruction->reg1] = ~(state->regs[instruction->reg1] | state->regs[instruction->reg2]);
		break;

	case 0x0e:
		debugf("nor %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->regs[instruction->reg1] = ~(state->regs[instruction->reg1] | instruction->imm16);
		break;

	case 0x0f:
		debugf("cmp %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->fg = 0;

		if (state->regs[instruction->reg1] == state->regs[instruction->reg2]) {
			state->fg |= FG_EQ;
			debugf("FG_EQ\n");
		}
		else {
			state->fg |= FG_NOT_EQ;
			debugf("FG_NOT_EQ\n");
		}

		if (state->regs[instruction->reg1] == 0) {
			state->fg |= FG_ZERO;
			debugf("FG_ZERO\n");
		}
		else {
			state->fg |= FG_NOT_ZERO;
			debugf("FG_NOT_ZERO\n");
		}
		break;

	case 0x10:
		debugf("cmp %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->fg = 0;

		if (state->regs[instruction->reg1] == instruction->imm16) {
			state->fg |= FG_EQ;
			debugf("FG_EQ\n");
		}
		else {
			state->fg |= FG_NOT_EQ;
			debugf("FG_NOT_EQ\n");
		}

		if (state->regs[instruction->reg1] == 0) {
			state->fg |= FG_ZERO;
			debugf("FG_ZERO\n");
		}
		else {
			state->fg |= FG_NOT_ZERO;
			debugf("FG_NOT_ZERO\n");
		}
		break;

	case 0x11:
		debugf("jzr 0x%x\n", instruction->imm16);
		if ((state->fg & FG_ZERO) != 0) {
			debugf("exec jmp\n");
			state->pc = instruction->imm16;
			return;
		}
		break;

	case 0x12:
		debugf("jzr %s\n", cpu_reg_names[instruction->reg2]);
		if ((state->fg & FG_ZERO) != 0) {
			debugf("exec jmp\n");
			state->pc = state->regs[instruction->reg2];
			return;
		}
		break;

	case 0x13:
		debugf("ldr %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->regs[instruction->reg1] = state->rom_ram[instruction->imm16];
		break;

	case 0x14:
		debugf("ldr %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->regs[instruction->reg1] = state->rom_ram[state->regs[instruction->reg2]];
		break;

	case 0x15:
		debugf("wtr %s, 0x%x\n", cpu_reg_names[instruction->reg1], instruction->imm16);
		state->rom_ram[instruction->imm16] = state->regs[instruction->reg1];
		break;

	case 0x16:
		debugf("wtr %s, %s\n", cpu_reg_names[instruction->reg1], cpu_reg_names[instruction->reg2]);
		state->rom_ram[state->regs[instruction->reg2]] = state->regs[instruction->reg1];
		break;

	case 0x17:
		debugf("swp %s\n", cpu_reg_names[instruction->reg1]);
		state->regs[instruction->reg1] = ((state->regs[instruction->reg1] & 0x00FF) << 8) | ((state->regs[instruction->reg1] & 0xFF00) >> 8);
		break;

	case 0x18:
		debugf("jmp 0x%x\n", instruction->imm16);
		state->pc = instruction->imm16;
		return;

	case 0x19:
		debugf("jmp %s\n", cpu_reg_names[instruction->reg2]);
		state->pc = state->regs[instruction->reg2];
		return;

	case 0x1a:
		debugf("jeq 0x%x\n", instruction->imm16);
		if ((state->fg & FG_EQ) != 0) {
			debugf("exec jmp\n");
			state->pc = instruction->imm16;
			return;
		}
		break;

	case 0x1b:
		debugf("jeq %s\n", cpu_reg_names[instruction->reg2]);
		if ((state->fg & FG_EQ) != 0) {
			debugf("exec jmp\n");
			state->pc = state->regs[instruction->reg2];
			return;
		}
		break;

	case 0x1c:
		debugf("jnq 0x%x\n", instruction->imm16);
		if ((state->fg & FG_NOT_EQ) != 0) {
			debugf("exec jmp\n");
			state->pc = instruction->imm16;
			return;
		}
		break;

	case 0x1d:
		debugf("jnq %s\n", cpu_reg_names[instruction->reg2]);
		if ((state->fg & FG_NOT_EQ) != 0) {
			debugf("exec jmp\n");
			state->pc = state->regs[instruction->reg2];
			return;
		}
		break;
	}

	state->pc += sizeof(instruction_t);
}

void cpu_dump_state(cpu_state_t* state) {
	printf("---- CPU STATE ----\n");

	printf("PC: 0x%x\n", state->pc);

	printf("FG: ");
	if ((state->fg & FG_EQ) != 0) {
		printf("FG_EQ ");
	}
	if ((state->fg & FG_NOT_EQ) != 0) {
		printf("FG_NOT_EQ ");
	}
	if ((state->fg & FG_ZERO) != 0) {
		printf("FG_ZERO ");
	}
	if ((state->fg & FG_NOT_ZERO) != 0) {
		printf("FG_NOT_ZERO ");
	}
	if ((state->fg & FG_OVERFLOW) != 0) {
		printf("FG_FG_OVERFLOW ");
	}
	printf("\n");

	for (int i = 0; i < 3; i++) {
		printf("%s: 0x%x, ", cpu_reg_names[i], state->regs[i]);
	}
	
	printf("%s: 0x%x\n", cpu_reg_names[12], state->regs[12]);

	printf("-------------------\n");
	printf("\n\n");

}

int parse_number(char* input) {
	bool hex = false;
	bool bin = false;
	bool dec = false;

	int start_offset = 0;

	if (input[0] == '0') {
		if (input[1] == 'x') {
			hex = true;
			start_offset = 2;
		}
		else if (input[1] == 'b') {
			bin = true;
			start_offset = 2;
		}
		else {
			dec = true;
		}
	}
	else {
		dec = true;
	}

	int number_system_base = 0;

	if (hex) {
		number_system_base = 16;
	}
	else if (bin) {
		number_system_base = 2;
	}
	else {
		number_system_base = 10;
	}

	int _number = 0;
	int idx = start_offset;

	while (input[idx] != '\0') {
		if (input[idx] >= '0' && input[idx] <= '9') {
			_number = _number * number_system_base + (input[idx] - '0');
		}
		else if (input[idx] >= 'a' && input[idx] <= 'f') {
			_number = _number * number_system_base + (input[idx] - 'a' + 10);
		}
		else if (input[idx] >= 'A' && input[idx] <= 'F') {
			_number = _number * number_system_base + (input[idx] - 'A' + 10);
		}
		else {
			break;
		}

		idx++;
	}

	return _number;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s <rom_file> <end_at_addr>\n", argv[0]);
		return -1;
	}

	FILE* f = fopen(argv[1], "r");
	assert(f != NULL);
	cpu_state_t state = init_cpu_state(f);

	uint32_t pc_end_addr = parse_number(argv[2]); // set to number bigger then 0xffff to never end

	fclose(f);

	while (1) {
		cpu_tick(&state);
		cpu_dump_state(&state);

		if (state.pc >= pc_end_addr) {
			break;
		}
		/*
	#ifdef __GNUC__
		sleep(1);
	#endif
	#ifdef _MSC_VER
		_sleep(100);
	#endif
		*/
	}
	return 0;
}