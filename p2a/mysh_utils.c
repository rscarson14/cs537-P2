
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh_utils.h"

#define PWD_BUF_SIZE 1024

int find_pipe(char* tokens[], int num_tokens);

int parse_input(char *line_buffer, char* tokens[]){
	char *next_token;
	char *delims = " ";
	int index = 0;
	int token_length = 0;
	
	//printf("In parse_input: line_buffer = %s\n", line_buffer);
	next_token = strtok(line_buffer, delims);
	if(next_token != NULL){
		//printf("token = %s\n", next_token);
		token_length = strlen(next_token);
		tokens[index] = (char *) malloc(token_length);
		strcpy(tokens[index], next_token);
		index++;
	}
	else{
		return 0;
	}

	while((next_token = strtok(NULL, delims)) != NULL){
		//printf("token = %s\n", next_token);
		token_length = strlen(next_token);
		tokens[index] = (char *) malloc(token_length);
		strcpy(tokens[index], next_token);
		index++;
	}

	return index;
}

int execute_command(char* tokens[], int num_tokens){
	char* command = tokens[0];
	char* pwd_buf; // Allocated if a pwd command is executed
	
	FILE* redir;
	
	pid_t child;

	int redir_overwrite = 0;
	int redir_append = 0;
	int pipe_index = -1; // index of character in tokens, -1 denotes no pipe
	int i = 0;
	int retval = 0;
	int status; // Used for wait()/waitpid() calls

	// Check the simplest command that requires no redirection/piping/etc
	if(!strcmp(command, "exit")){		
		return 1;
	}
	// Check the next simplest command that requires no redirection/piping/etc
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
		redir = fopen(tokens[num_tokens - 1], "w"); 
		if(redir == NULL){
			retval = -1; // error
			return -1;
		}
		child = fork();
		if(child != 0){
			waitpid(child, &status, 0);
		}
		else{
			dup2(fileno(stdout), fileno(redir));
		}
	}
	else if(!strcmp(tokens[num_tokens -2], ">>")){
		printf("Output redirection >>\n");
		redir_append = 1;
		redir = fopen(tokens[num_tokens - 1], "wa");
		if(redir == NULL){
			retval = -1; // error
			return -1;
		}
	}
	else if((pipe_index = find_pipe(tokens, num_tokens)) > -1){ // Search for pipe '|'
		
	}
	else{
		child = fork();
		if(child != 0){
			waitpid(child, &status, 0);
		}
		else{
			tokens[num_tokens] = NULL;
			execvp(command, tokens);
			exit(-1);
		}
	}
	
	return status;
}

int find_pipe(char* tokens[], int num_tokens){
	int pipe_index = -1;
	int i = 0;

	for(i = 0; i < num_tokens; i++){
		if(!strcmp(tokens[i], "|")){
			pipe_index = i;
			printf("Pipe at %d\n", pipe_index);
			i = num_tokens;
		}
	}
	return pipe_index;
}
