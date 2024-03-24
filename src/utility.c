/*
 * Operating Systems Project 1 - myshell
 * Author: Cathal Dwyer
 * Student ID: 22391376
 * In submitting this project, I declare that the project material, which I now
 * submit, is my own work. Any assistance received by way of borrowing from
 * the work of others has been cited and acknowledged within the work.
 */

#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

void execute_command(char *args[], int background) {
    // Fork a new process
    pid_t pid = fork();
    if (pid < 0) {
        // Check if fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        if (background) {
            // If background process, redirect stdin to /dev/null
            int dev_null = open("/dev/null", O_RDONLY);
            if (dev_null == -1) {
                fprintf(stderr, "Error opening /dev/null\n");
                exit(1);
            }
            dup2(dev_null, STDIN_FILENO);
            close(dev_null);
        }

        // Check for input redirection
        int i = 0;
        while (args[i] != NULL) {
            if (strcmp(args[i], "<") == 0) {
                // Check if the next argument exists
                if (args[i + 1] == NULL) {
                    fprintf(stderr, "Input file not specified\n");
                    exit(1);
                }
                // Open input file for reading
                int input_file = open(args[i + 1], O_RDONLY);
                if (input_file == -1) {
                    fprintf(stderr, "Error opening input file\n");
                    exit(1);
                }
                // Redirect stdin to the input file
                dup2(input_file, STDIN_FILENO);
                close(input_file);
                // Remove redirection symbols and input file from args array
                args[i] = NULL;
                args[i + 1] = NULL;
                break;
            }
            i++;
        }

        // Check for output redirection (truncate)
        i = 0;
        while (args[i] != NULL) {
            if (strcmp(args[i], ">") == 0) {
                // Check if the next argument exists
                if (args[i + 1] == NULL) {
                    fprintf(stderr, "Output file not specified\n");
                    exit(1);
                }
                // Open output file for writing (truncate)
                int output_file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output_file == -1) {
                    fprintf(stderr, "Error opening output file\n");
                    exit(1);
                }
                // Redirect stdout to the output file
                dup2(output_file, STDOUT_FILENO);
                close(output_file);
                // Remove redirection symbols and output file from args array
                args[i] = NULL;
                args[i + 1] = NULL;
                break;
            }
            i++;
        }

        // Check for output redirection (append)
        i = 0;
        while (args[i] != NULL) {
            if (strcmp(args[i], ">>") == 0) {
                // Check if the next argument exists
                if (args[i + 1] == NULL) {
                    fprintf(stderr, "Output file not specified\n");
                    exit(1);
                }
                // Open output file for writing (append)
                int output_file = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (output_file == -1) {
                    fprintf(stderr, "Error opening output file\n");
                    exit(1);
                }
                // Redirect stdout to the output file
                dup2(output_file, STDOUT_FILENO);
                close(output_file);
                // Remove redirection symbols and output file from args array
                args[i] = NULL;
                args[i + 1] = NULL;
                break;
            }
            i++;
        }

        // Set parent environment variable if not a background process
        if (!background) {
            setenv("parent", SHELL_PATH, 1);
        }

        // Execute the command
        execvp(args[0], args);
        // If execvp fails, print error message
        fprintf(stderr, "Error executing command\n");
        exit(1);
    } else {
        // Parent process
        if (!background) {
            // If not a background process, wait for child process to finish
            int status;
            waitpid(pid, &status, 0);
        } else {
            // If background process, print the PID
            printf("Background process started with PID: %d\n", pid);
        }
    }
}

/*batch_mode: Executes the shell in batch mode, reading and processing commands from a batch file.*/
void batch_mode(char *filename) {
    char *args[MAX_ARGS];   // Array to store command arguments
    char command[MAX_LINE]; // Array to store command line input
    int background = 0;     // Flag to indicate background execution

    FILE *batch_file = fopen(filename, "r"); // Open batch file for reading
    if (!batch_file) {                         // Check if file opening failed
        fprintf(stderr, "Error opening file %s\n", filename); // Print error message to stderr
        exit(EXIT_FAILURE);                                   // Exit with failure status
    }

    while (fgets(command, sizeof(command), batch_file) != NULL) { // Read commands from file
        // Remove newline character from the command
        command[strcspn(command, "\n")] = '\0';

        char *token = strtok(command, " "); // Tokenize command line
        int i = 0;
        while (token != NULL) {                              // Iterate over tokens
            args[i++] = token;                               // Store token in arguments array
            token = strtok(NULL, " "); // Get next token
        }
        args[i] = NULL; // Null-terminate arguments array

        // Check if background execution requested
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            background = 1;     // Set background flag
            args[i - 1] = NULL; // Remove "&" from arguments
        } else {
            background = 0; // Reset background flag
        }

        // Execute command
        execute_command(args, background);
    }

    fclose(batch_file); // Close batch file
    exit(EXIT_SUCCESS); // Exit with success status
}

/*interactive_mode: This function represents the interactive mode of your shell. It continuously prompts the user for input, reads the command,
       and tokenizes it into individual arguments. Then, based on the command entered, it performs specific actions such as changing directory (cd), clearing the screen (clr),
       listing directory contents (dir), displaying environment variables (environ), or echoing the input (echo).*/
void interactive_mode()
{
    char *args[MAX_ARGS];   // Array to store command arguments
    char command[MAX_LINE]; // Array to store command line input

    while (1)
    { // Interactive mode: accept user input
        char cwd[MAX_LINE];
        getcwd(cwd, sizeof(cwd));               // Get current working directory
        printf("%s> ", cwd);                    // Print prompt with current directory
        fflush(stdout);                         // Flush output buffer
        fgets(command, sizeof(command), stdin); // Read command line input
        command[strcspn(command, "\n")] = 0;    // Remove newline character

        // printf("Command entered: %s\n", command); // Debugging statement

        // Tokenize command line
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL)
        {                              // Iterate over tokens
            args[i++] = token;         // Store token in arguments array
            token = strtok(NULL, " "); // Get next token
        }
        args[i] = NULL; // Null-terminate arguments array
        if (strcmp(args[0], "") == 0)
        {
            continue;
        }

        else if (strcmp(args[0], "cd") == 0)
        { // Check if "cd" command entered
            if (args[1] == NULL || strcmp(args[1], "") == 0)
            { // If no directory argument provided
                char cwd[MAX_LINE];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                    printf("Current directory: %s\n", cwd); // Print current directory
                else
                    fprintf(stderr, "Error getting current directory\n"); // Print error if unable to get current directory
            }
            else
            { // Change directory
                if (chdir(args[1]) != 0)
                {                                                  // Change directory
                    fprintf(stderr, "Error changing directory\n"); // Print error message if directory change fails
                }
            }
        }
        else if (strcmp(args[0], "clr") == 0)
        {                    // Check if "clr" command entered
            system("clear"); // Clear screen
        }
        else if (strcmp(args[0], "help") == 0)
        { // Check if "help" command entered
            // Assuming the user manual file is located at "manual/readme.md"
            char *more_cmd[] = {"more", "manual/readme.md", NULL};
            execute_command(more_cmd, 0); // Execute the 'more' command with the manual file
        }
        else if (strcmp(args[0], "dir") == 0)
        {
            // Check if a directory argument is provided
            if (args[1] != NULL)
            {
                dir_command(args[1]);
            }
            else
            {
                // List contents of current directory
                dir_command(".");
            }
        }

        else if (strcmp(args[0], "environ") == 0)
        {                         // Check if "environ" command entered
            char **env = environ; // Pointer to environment variables
            while (*env)
            {                         // Iterate over environment variables
                printf("%s\n", *env); // Print each environment variable
                env++;                // Move to next environment variable
            }
        }
        else if (strcmp(args[0], "echo") == 0)
        { // Check if "echo" command entered
            for (int j = 1; args[j] != NULL; j++)
            {                           // Iterate over echo arguments
                printf("%s ", args[j]); // Print each argument
            }
            printf("\n"); // Print newline
        }
        else if (strcmp(args[0], "quit") == 0)
        { // Check if "quit" command entered
            printf("Exiting the shell.\n");
            exit(EXIT_SUCCESS); // Exit the shell with success status
        }
        else if (strcmp(args[0], "pause") == 0)
        { // Check if "pause" command entered
            printf("Shell paused. Press Enter to resume.\n");
            while (getchar() != '\n')
                ; // Wait for Enter key press
            printf("Resuming shell operation.\n");
        }
    }
}
void dir_command(char *directory) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(directory);
    if (dir == NULL) {
        fprintf(stderr, "Error opening directory\n");
        return;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);
}