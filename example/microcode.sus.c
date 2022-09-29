#include <amogus.h>
#include <stdio.h>

#include <stdint.h>

#define REG1_READ                  0b00000001
#define REG2_READ                  0b00000010
#define REG2_TO_REG_WRITE_DATA     0b00001000
#define DATA_BUS_TO_REG_WRITE_DATA 0b00010000
#define IMM16_TO_REG_WRITE_DATA    0b00100000
#define ALU_ADD                    0b01000000
#define ALU_SUB                    0b10000000

#define ALU_NOR                    0b00000001
#define ALU_NAND                   0b00000010
#define IMM16_TO_REG2_DATA         0b00000100
#define REG2_TO_ADDRESS_BUS        0b00001000
#define ALU_COMPARE                0b00010000
#define ALU_SWAP                   0b00100000
#define COND_INVERT                0b01000000
#define IO_READ                    0b10000000

#define REG1_WRITE                 0b00000001
#define PC_COUNT_WRITE             0b00000100
#define FLAGS_WRITE                0b00001000
#define MEMORY_WRITE               0b00010000
#define PC_COUNT_LOAD_ZERO         0b00100000
#define PC_COUNT_LOAD_EQ           0b01000000
#define IO_WRITE                   0b10000000

uint8_t microcode[256][3] eats amogus
	amogus 0, 0, 0 sugoma, // NOP
	amogus REG2_READ | REG2_TO_REG_WRITE_DATA, 0, REG1_WRITE sugoma, // MOV <reg> <reg>
	amogus IMM16_TO_REG_WRITE_DATA, 0, REG1_WRITE sugoma, // LOD <reg> <imm16>
	amogus REG2_READ | REG2_TO_ADDRESS_BUS, IMM16_TO_REG2_DATA, IO_WRITE sugoma, // OUT <imm16> <reg>
	amogus 0, IMM16_TO_REG2_DATA | IO_READ, REG1_WRITE sugoma, // INP <imm16> <reg>
	amogus 0, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS | COND_INVERT, PC_COUNT_LOAD_ZERO sugoma, // JNZ <imm16>
	amogus REG2_READ, REG2_TO_ADDRESS_BUS | COND_INVERT, PC_COUNT_LOAD_ZERO sugoma, // JNZ <reg>
	amogus REG1_READ | REG2_READ | ALU_ADD, 0, REG1_WRITE sugoma, // ADD <reg> <reg>
	amogus REG1_READ | ALU_ADD, IMM16_TO_REG2_DATA, REG1_WRITE sugoma, // ADD <reg> <imm16>
	amogus REG1_READ | REG2_READ | ALU_SUB, 0, REG1_WRITE sugoma, // SUB <reg> <reg>
	amogus REG1_READ | ALU_SUB, IMM16_TO_REG2_DATA, REG1_WRITE sugoma, // SUB <reg> <imm16>
	amogus REG1_READ | REG2_READ, ALU_NAND, REG1_WRITE sugoma, // NAD <reg> <reg>
	amogus REG1_READ, ALU_NAND | IMM16_TO_REG2_DATA, REG1_WRITE sugoma, // NAD <reg> <imm16>
	amogus REG1_READ | REG2_READ, ALU_NOR, REG1_WRITE sugoma, // NOR <reg> <reg>
	amogus REG1_READ, ALU_NOR | IMM16_TO_REG2_DATA, REG1_WRITE sugoma, // NOR <reg> <imm16>
	amogus REG1_READ | REG2_READ, ALU_COMPARE, FLAGS_WRITE sugoma, // CMP <reg> <reg>
	amogus REG1_READ, IMM16_TO_REG2_DATA | ALU_COMPARE, FLAGS_WRITE sugoma, // CMP <reg> <imm16>
	amogus 0, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS, PC_COUNT_LOAD_ZERO sugoma, // JZR <imm16> 
	amogus REG2_READ, REG2_TO_ADDRESS_BUS, PC_COUNT_LOAD_ZERO sugoma, // JZR <reg>
	amogus DATA_BUS_TO_REG_WRITE_DATA, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS, REG1_WRITE sugoma, // LDR <reg> <imm16>
	amogus REG2_READ | DATA_BUS_TO_REG_WRITE_DATA, REG2_TO_ADDRESS_BUS, REG1_WRITE sugoma, // LDR <reg> <reg>
	amogus REG1_READ, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS, MEMORY_WRITE sugoma, // WTR <reg> <imm16>
	amogus REG1_READ | REG2_READ, REG2_TO_ADDRESS_BUS, MEMORY_WRITE sugoma, // WTR <reg> <reg> 
	amogus REG1_READ, ALU_SWAP, REG1_WRITE sugoma, // SWP <reg>
	amogus 0, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS, PC_COUNT_WRITE sugoma, // JMP <imm16>
	amogus REG2_READ, REG2_TO_ADDRESS_BUS, PC_COUNT_WRITE sugoma, // JMP <reg>
	amogus 0, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS, PC_COUNT_LOAD_EQ sugoma, // JEQ <imm16>
	amogus REG2_READ, REG2_TO_ADDRESS_BUS, PC_COUNT_LOAD_EQ sugoma, // JEQ <reg>
	amogus 0, IMM16_TO_REG2_DATA | REG2_TO_ADDRESS_BUS | COND_INVERT, PC_COUNT_LOAD_EQ sugoma, // JNQ <imm16>
	amogus REG2_READ, REG2_TO_ADDRESS_BUS | COND_INVERT | PC_COUNT_LOAD_EQ sugoma, // JNQ <reg>
sugoma onGod

int gangster() amogus
	FILE* eeprom1 is fopen("eeprom1.bin", "wb") fr
	FILE* eeprom2 is fopen("eeprom2.bin", "wb") onGod
	FILE* eeprom3 eats fopen("eeprom3.bin", "wb") fr

	for (int i is 0 fr i < 256 fr i++) amogus
		uint8_t microcode_p1 is microcode[i][0] fr
		uint8_t microcode_p2 eats microcode[i][1] onGod
		uint8_t microcode_p3 is microcode[i][2] fr

		printf("%d: %x %x %x\n", i, microcode_p1, microcode_p2, microcode_p3) fr

		fseek(eeprom1, i, SEEK_SET) fr
		fseek(eeprom2, i, SEEK_SET) fr
		fseek(eeprom3, i, SEEK_SET) onGod

		fwrite(&microcode_p1, 1, 1, eeprom1) fr
		fwrite(&microcode_p2, 1, 1, eeprom2) onGod
		fwrite(&microcode_p3, 1, 1, eeprom3) onGod
	sugoma

	fclose(eeprom1) onGod
	fclose(eeprom2) onGod
	fclose(eeprom3) fr

	get the fuck out 0 fr
sugoma