This project is a simple command line shell designed for Linux, providing basic functionalities including command execution, I/O redirection, and batch processing. The shell supports internal commands such as cd, clr, dir, environ, echo, help, pause, and quit, as well as execution of external programs with support for background processing.

Features
Internal Commands:

cd [directory]: Change or report the current directory and update the PWD environment variable.
clr: Clear the screen.
dir [directory]: List the contents of a directory.
environ: List all environment variables.
echo [string]: Display a string on the screen.
help: Display the user manual using more.
pause: Pause shell operations until 'Enter' is pressed.
quit: Exit the shell.
Shell Environment:

The environment includes shell=/myshell with the full path to the shell executable.
Invoked programs include parent=/myshell in their environment.
Program Execution:

Fork and execute external programs as child processes.
Support background execution using &.
Batch Mode:

Execute commands from a specified file.
I/O Redirection:

Support input (<) and output (> and >>) redirection for both internal and external commands.
Miscellaneous:

The command prompt displays the current directory path.
Handles errors appropriately (e.g., file operations).
Development and Usage
System Compatibility:

Designed to compile and run on Linux systems.
Ensure compatibility by testing on Linux lab computers.
Code Quality:

Extensively commented and properly structured code.
Organized into multiple files for better maintainability.
Building the Shell
To build the shell, simply run:

go
Copy code
make
User Manual
The user manual (readme.md) provides detailed descriptions of shell usage, including:

Explanation of I/O redirection, environment variables, and background execution.
References to at least four peer-reviewed sources using Harvard or IEEE citation style.
Getting Started
Clone the repository and build the shell to get started:

bash
Copy code
git clone https://github.com/yourusername/simple-shell.git
cd simple-shell
make
Contributing
Contributions are welcome! Please fork the repository and submit pull requests.
