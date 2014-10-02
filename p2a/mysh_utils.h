/** Declarations for helper functions used by mysh
 * Author - R. Scott Carson
 * */

#ifndef _MYSH_UTILS_H
#define _MYSH_UTILS_H

#define RET_ERROR (-1)
#define RET_OK (0)
#define RET_EXIT (1)

int parse_input(char *line_buffer, char* tokens[]);
int execute_command(char* tokens[], int num_tokens);

#endif
