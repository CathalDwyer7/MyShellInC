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
 *    - Had a basic tutorial on shell in c helped me get started as I was overwhelmed at the begining
 */
#include "myshell.h"

void execute_command(char *args[], int background) {
    pid_t pid = fork(); // Fork a new process
    if (pid < 0) { // Check if fork failed
        fprintf(stderr, "Fork failed\n"); // Print error message to stderr
        exit(1); // Exit with failure status
    } else if (pid == 0) { // Child process
        if (!background) { // If not background process
            setenv("parent", SHELL_PATH, 1); // Set parent environment variable
        }
        execvp(args[0], args); // Execute the command
        fprintf(stderr, "Error executing command\n"); // Print error message if execvp fails
        exit(1); // Exit with failure status
    } else { // Parent process
        if (!background) { // If not background process
            int status;
            waitpid(pid, &status, 0); // Wait for child process to finish
        } else { // If background process
            printf("Background process started with PID: %d\n", pid); // Print background process PID
        }
    }
}

void batch_mode(char *filename) {
    char *args[MAX_ARGS]; // Array to store command arguments
    char command[MAX_LINE]; // Array to store command line input
    int background = 0; // Flag to indicate background execution

    FILE *batch_file = fopen(filename, "r"); // Open batch file for reading
    if (!batch_file) { // Check if file opening failed
        fprintf(stderr, "Error opening file\n"); // Print error message to stderr
        exit(1); // Exit with failure status
    }

    while (fgets(command, sizeof(command), batch_file) != NULL) { // Read commands from file
        command[strcspn(command, "\n")] = 0; // Remove newline character
        char *token = strtok(command, " "); // Tokenize command line
        int i = 0;
        while (token != NULL) { // Iterate over tokens
            args[i++] = token; // Store token in arguments array
            token = strtok(NULL, " "); // Get next token
        }
        args[i] = NULL; // Null-terminate arguments array
        if (strcmp(args[i - 1], "&") == 0) { // Check if background execution requested
            background = 1; // Set background flag
            args[i - 1] = NULL; // Remove "&" from arguments
        }
        execute_command(args, background); // Execute command
        background = 0; // Reset background flag
    }
    fclose(batch_file); // Close batch file
    exit(0); // Exit with success status
}

void interactive_mode() {
    char *args[MAX_ARGS]; // Array to store command arguments
    char command[MAX_LINE]; // Array to store command line input
    int background = 0; // Flag to indicate background execution

    while (1) { // Interactive mode: accept user input
        char cwd[MAX_LINE];
        getcwd(cwd, sizeof(cwd)); // Get current working directory
        printf("%s> ", cwd); // Print prompt with current directory
        fflush(stdout); // Flush output buffer
        fgets(command, sizeof(command), stdin); // Read command line input
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "exit") == 0) { // Check if "exit" command entered
            break; // Exit shell loop
        }

        char *token = strtok(command, " "); // Tokenize command line
        int i = 0;
        while (token != NULL) { // Iterate over tokens
            args[i++] = token; // Store token in arguments array
            token = strtok(NULL, " "); // Get next token
        }
        args[i] = NULL; // Null-terminate arguments array

        if (strcmp(args[0], "cd") == 0) { // Check if "cd" command entered
            if (chdir(args[1]) != 0) { // Change directory
                fprintf(stderr, "Error changing directory\n"); // Print error message if directory change fails
            }
        } else if (strcmp(args[0], "clr") == 0) { // Check if "clr" command entered
            system("clear"); // Clear screen
        } else if (strcmp(args[0], "dir") == 0) { // Check if "dir" command entered
            system("ls"); // List directory contents
        } else if (strcmp(args[0], "environ") == 0) { // Check if "environ" command entered
            char **env = environ; // Pointer to environment variables
            while (*env) { // Iterate over environment variables
                printf("%s\n", *env); // Print each environment variable
                env++; // Move to next environment variable
            }
        } else if (strcmp(args[0], "echo") == 0) { // Check if "echo" command entered
            for (int j = 1; args[j] != NULL; j++) { // Iterate over echo arguments
                printf("%s ", args[j]); // Print each argument
            }
            printf("\n"); // Print newline
        } else if (strcmp(args[0], "help") == 0) { // Check if "help" command entered
            FILE *fp = popen("more readme", "r"); // Open user manual file for reading
            if (fp == NULL) { // Check if file opening failed
                fprintf(stderr, "Error opening user manual\n"); // Print error message to stderr
            } else {
                char c;
                while ((c = fgetc(fp)) != EOF) { // Read and print
                    putchar(c);
                }
                pclose(fp);
            }
        } else { // External command
            if (strcmp(args[i - 1], "&") == 0) { // Check if background execution requested
                background = 1; // Set background flag
                args[i - 1] = NULL; // Remove "&" from arguments
            }
            execute_command(args, background); // Execute command
            background = 0; // Reset background flag
        }
    }
}