#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;
int exec_comm(char **argv);
char *get_comm(void);
int exit_comm(char *comm);
char *my_getline();

#endif
