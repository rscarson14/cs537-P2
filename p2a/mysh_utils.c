
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mysh_utils.h"

int parse_input(char *line_buffer, char* tokens[]){
	char *next_token;
	char *delims = " ";
	int index = 0;
	int token_length = 0;
	
	printf("In parse_input: line_buffer = %s\n", line_buffer);
	next_token = strtok(line_buffer, delims);
	if(next_token != NULL){
		printf("token = %s\n", next_token);
		token_length = strlen(next_token);
		tokens[index] = (char *) malloc(token_length);
		strcpy(tokens[index], next_token);
		index++;
	}
	else{
		return 0;
	}

	while((next_token = strtok(NULL, delims)) != NULL){
		printf("token = %s\n", next_token);
		token_length = strlen(next_token);
		tokens[index] = (char *) malloc(token_length);
		strcpy(tokens[index], next_token);
		index++;
	}

	return index;
}

int execute_command(char* tokens[]){
	char* command = tokens[0];

	if(!strcmp(command, "exit")){
		exit(0);
	}
	
	
	return 0;
}
