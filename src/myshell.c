/*
 * Operating Systems Project 1 - myshell
 * Author: Cathal Dwyer
 * Student ID: 22391376
 * In submitting this project, I declare that the project material, which I now
 * submit, is my own work. Any assistance received by way of borrowing from
 * the work of others has been cited and acknowledged within the work.
 */

#include "myshell.h"

char SHELL_PATH[MAX_LINE]; // Define the SHELL_PATH variable globally

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