/*
 * Operating Systems Project 1 - myshell
 * Author: Cathal Dwyer
 * Student ID: 22391376
 */

#ifndef MYSHELL_H
#define MYSHELL_H

// Include necessary standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Declare the global variable environ which contains the environment variables
extern char **environ;

// Define maximum line length and maximum number of arguments
#define MAX_LINE 80
#define MAX_ARGS 20

// Declare the global variable SHELL_PATH to store the path of the shell executable
extern char SHELL_PATH[MAX_LINE];

// Declare function prototypes for the shell functionalities
void execute_command(char *args[], int background);
void interactive_mode();
void batch_mode(char *filename);
void dir_command(char *directory);

#endif /* MYSHELL_H */