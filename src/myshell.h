/*
 * Operating Systems Project 1 - myshell
 * Author: Cathal Dwyer
 * Student ID: 22391376
 * References:
 * - course notes
 *    - Used to go over syntax and make sure i understood what the program should be doing
 * - stack overflow
 *    - I didnt know how to properly link my files together so I was able to find this info on stack overflow
 */

#ifndef HEADER_H
#define HEADER_H

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
void batch_mode(char *filename);
void interactive_mode();

#endif /* HEADER_H */