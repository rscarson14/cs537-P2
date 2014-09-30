/**
 * MyShell - Simple Linux command-line interpreter
 * Author - R. Scott Carson
 *
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "mysh_utils.h"

#define BUFFER_SIZE 1024

int parse_input(char *line_buffer, char* tokens[]);
int execute_command(char* tokens[], int num_tokens);

volatile int finished;

int main(int argc, char* argv[]){
	
	int length;
	int num_tokens;
	char line_buffer[1024];
	char* tokens[1024];
	const char *prompt = "mysh> ";
	char* command;
	finished = 0;

	while(!finished){
		printf("%s", prompt);
		fgets(line_buffer, BUFFER_SIZE, stdin);

		// Remove the new line character
		length = strlen(line_buffer) - 1;
		if( line_buffer[length] == '\n' ){
			line_buffer[length] = '\0';
		}

		printf("Buffer = %s\n", line_buffer);
		num_tokens = parse_input(line_buffer, tokens);
		printf("Number of tokens = %d\n", num_tokens);
		if(num_tokens > 0){
			printf("Command: %s\n", tokens[0]);
			execute_command(tokens, num_tokens);
		}
	}
	
	return 0;
}

