/*
 * Operating Systems Project 1 - myshell
 * Author: Cathal Dwyer
 * Student ID: 22391376
 * References:
 * - The C Programming Language, 2nd Edition by Brian W. Kernighan and Dennis M. Ritchie
 *    - Used for understanding C programming concepts and syntax.
 * - https://medium.com/@winfrednginakilonzo/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd
 *    - Helped me understand what I needed to do in order to create a shell
 * - https://www.studocu.com/row/document/yildirim-beyazit-universitesi/computer-programming-i/22-interactive-and-batch-modes-file-operations/13343967
 *    - I didnt know how to separate and use interactive mode and batch mode
 * - Linux manual pages (man pages)
 *    - Referenced for understanding system calls and library functions.
 * - course notes
 *    - Used to go over syntax and make sure i understood what the program should be doing
 * - youtube channel Jess_inspired 
 *    - Helped me get started and understand what to do as I was overwhelmed at the begining
 */


#include "myshell.h"
char SHELL_PATH[MAX_LINE]; // Define the SHELL_PATH variable

int main(int argc, char *argv[]) {
    // Get the path of the shell executable
    if (realpath(argv[0], SHELL_PATH) == NULL) { // Get the full path of the shell executable
        fprintf(stderr, "Error getting shell path\n"); // Print error message if path retrieval fails
        exit(1); // Exit with failure status
    }

    if (argc > 1) {
        batch_mode(argv[1]);
    } else {
        interactive_mode();
    }

    return 0;
}
