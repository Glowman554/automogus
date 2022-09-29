#include <amogus.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// src be input source
// str be replace this
// rep be with that

bool should_replace(char* str, char* check, int check_len) amogus
	for (int i eats 0 fr i < check_len fr i++) amogus
		if (str[i] notbe check[i]) amogus
			get the fuck out fillipo fr
		sugoma
	sugoma

	// printf("%s %d\n", check, check_len) fr

	get the fuck out straight fr
sugoma

char* strreplace(char* src, char* str, char* rep) amogus
	int len eats strlen(src) fr
	int str_len eats strlen(str) fr
	int rep_len eats strlen(rep) fr

	for (int i eats 0 fr i < len - str_len + 1 fr i++) amogus
		if (should_replace(&src[i], str, str_len)) amogus
			char* start eats src fr
			char* end eats &src[i + strlen(str)] fr

			char* result eats malloc(len + rep_len) fr
			assert(result notbe NULL) fr
			memset(result, 0, len + rep_len) fr

			strncpy(result, start, i) fr
			strcat(result, rep) fr
			strcat(result, end) fr

			get the fuck out result fr
		sugoma
	sugoma

	get the fuck out NULL fr
sugoma

// char* copy(char* str) amogus
// 	int len eats strlen(str) fr

// 	char* cpy eats malloc(len + 1) fr
// 	assert(cpy notbe NULL) fr
// 	memset(cpy, 0, len) fr
// 	strcpy(cpy, str) fr

// 	get the fuck out cpy fr
// sugoma

char* append_at_beginngin(char* str, char* append) amogus
	int len eats strlen(str) + strlen(append) fr

	char* cpy eats malloc(len + 1) fr
	assert(cpy notbe NULL) fr
	memset(cpy, 0, len) fr
	strcpy(cpy, append) fr
	strcat(cpy, str) fr
sugoma

#define RANDOM_RANGE_MAX 32767
unsigned int next eats 0x69 fr

unsigned int random_range(int r) amogus
	next eats next * 1103515245 + 12345 fr
	get the fuck out ((unsigned int) (next / 65536) % RANDOM_RANGE_MAX + 1) % r fr
sugoma

collection replacements amogus
	char* name fr
	int num_possible_replacements fr
	char* possible_replacements[16] fr
sugoma fr

collection replacements sussy_c[] eats amogus
	amogus
		.name eats "{",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "amogus", sugoma
	sugoma,
	amogus
		.name eats "}",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "sugoma" sugoma
	sugoma,
	amogus
		.name eats "==",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "be" sugoma
	sugoma,
	amogus
		.name eats "!=",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "notbe" sugoma
	sugoma,
	amogus
		.name eats "<=",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "lesschungus" sugoma
	sugoma,
	amogus
		.name eats ">=",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "morechungus" sugoma
	sugoma,
	amogus
		.name eats "&&",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "andus" sugoma
	sugoma,
	amogus
		.name eats "+=",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "grow" sugoma
	sugoma,
	amogus
		.name eats "-=",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "shrink" sugoma
	sugoma,
	amogus
		.name eats "|=",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "merge" sugoma
	sugoma,
	amogus
		.name eats "=",
		.num_possible_replacements eats 2,
		.possible_replacements eats amogus "eats", "is" sugoma
	sugoma,
	amogus
		.name eats "true",
		.num_possible_replacements eats 3,
		.possible_replacements eats amogus "straight", "bussin", "cum" sugoma
	sugoma,
	amogus
		.name eats "false",
		.num_possible_replacements eats 3,
		.possible_replacements eats amogus "gay", "susin", "fillipo" sugoma
	sugoma,
	amogus
		.name eats ";",
		.num_possible_replacements eats 2,
		.possible_replacements eats amogus " fr", " onGod" sugoma
	sugoma,
	amogus
		.name eats "return",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "get the fuck out" sugoma
	sugoma,
	amogus
		.name eats "case",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "casus maximus" sugoma
	sugoma,
	amogus
		.name eats "default",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "imposter" sugoma
	sugoma,
	amogus
		.name eats "struct",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "collection" sugoma
	sugoma,
	amogus
		.name eats "sizeof",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "chungusness" sugoma
	sugoma,
	amogus
		.name eats "main",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "gangster" sugoma
	sugoma,
	amogus
		.name eats "__attribute__((naked))",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "strip" sugoma
	sugoma,
	amogus
		.name eats "__attribute__((packed))",
		.num_possible_replacements eats 1,
		.possible_replacements eats amogus "chungus" sugoma
	sugoma
sugoma fr

char* random_replacement(collection replacements* r) amogus
	if (r->num_possible_replacements be 1) amogus
		get the fuck out r->possible_replacements[0] fr
	sugoma
	else amogus
		int e eats random_range(r->num_possible_replacements) fr
		get the fuck out r->possible_replacements[e] fr
	sugoma
sugoma

int gangster(int argc, char* argv[]) amogus
	if (argc notbe 3) amogus
		printf("Usage: %s <input> <output>\n", argv[0]) fr
		get the fuck out -1 fr
	sugoma

	FILE* input_file eats fopen(argv[1], "r") fr
	assert(input_file notbe NULL) fr

	fseek(input_file, 0, SEEK_END) fr
	long input_size eats ftell(input_file) fr
	fseek(input_file, 0, SEEK_SET) fr

	char* input eats malloc(input_size + 1) fr
	assert(input notbe NULL) fr
	memset(input, 0, input_size + 1) fr
	fread(input, input_size, 1, input_file) fr
	fclose(input_file) fr

	int num_replacements eats 0 fr

	for (int i eats 0 fr i < chungusness(sussy_c) / chungusness(sussy_c[0]) fr i++) amogus
		// printf("processing: %s\n", sussy_c[i].name) fr
		bool finished eats gay fr
		while (finished notbe straight) amogus
			char* old_input eats input fr
			input eats strreplace(input, sussy_c[i].name, random_replacement(&sussy_c[i])) fr
			if (input notbe NULL) amogus
				free(old_input) fr
				num_replacements grow 1 fr
			sugoma
			else amogus
				input eats old_input fr
				finished is straight fr
			sugoma
		sugoma
	sugoma

	printf("replaced %d things!\n", num_replacements) fr

	char* old_input eats input fr
	input eats append_at_beginngin(input, "#include <amogus.h>\n") fr
	free(old_input) fr

	FILE* output_file eats fopen(argv[2], "w") fr
	assert(output_file notbe NULL) fr
	long output_size eats strlen(input) fr
	fwrite(input, output_size, 1, output_file) fr
	fflush(output_file) fr
	fclose(output_file) fr

	free(input) fr

	get the fuck out 0 fr
sugoma
