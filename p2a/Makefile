
all: mysh.o mysh_utils.o
	gcc -o mysh mysh.o mysh_utils.o -Wall -O

mysh.o: mysh.c
	gcc -c mysh.c -Wall -O

mysh_utils.o: mysh_utils.c
	gcc -c mysh_utils.c -Wall -O
