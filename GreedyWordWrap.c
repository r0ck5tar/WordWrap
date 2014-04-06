#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	FILE *txt_orig;
	FILE *txt_wrapped;

	if (argc != 2) {
		printf("Error: insufficient arguments.\nUsage: WordWrap [path_to_text_file]");
		exit(-1);
	}

	char * file_name = malloc(strlen("wrapped_") + strlen(argv[1]));
	strcpy(file_name, "wrapped_");

	printf("Opening text file %s\n", argv[1]);

	txt_orig = fopen(argv[1], "r");
	txt_wrapped = fopen(strcat(file_name, argv[1]), "w");

	char* word = malloc(20);
	char* line = malloc(77); //each line has 76 characters max (plus the string terminator, \O)
	//strcpy(line, "");

	while (fscanf(txt_orig, "%s", word) != EOF) {
		if (strlen(line) + strlen(word) <= 76) {
			strcat(line, word);
			strcat(line, " ");
		}
		else{
			fprintf(txt_wrapped, "%s\n", line);
			strcpy(line, "");
			strcpy(line, word);
		}
	}

	fprintf(txt_wrapped, "%s", line); //append the last line
}