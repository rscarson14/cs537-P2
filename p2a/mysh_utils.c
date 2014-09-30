
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mysh_utils.h"

#define PWD_BUF_SIZE 1024

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

int execute_command(char* tokens[], int num_tokens){
	char* command = tokens[0];
	char* pwd_buf;
	int redir_overwrite = 0;
	int redir_append = 0;
	int pipe = 0;

	if(!strcmp(command, "exit")){
		exit(0);
	}
	else if(!strcmp(command, "cd")){
		chdir(tokens[1]);
		pwd_buf = malloc(PWD_BUF_SIZE);
		getcwd(pwd_buf, PWD_BUF_SIZE);
		printf("Working directory currently: %s\n", pwd_buf);
		free(pwd_buf);
	}
	
	// Check for overwrite redirection '>' or '>>'
	if(!strcmp(tokens[num_tokens - 2], ">")){
		printf("Output redirection >\n");
		redir_overwrite = 1;
	}
	else if(!strcmp(tokens[num_tokens -2], ">>")){
		printf("Output redirection >>\n");
		redir_append = 1;
	}



	return 0;
}
