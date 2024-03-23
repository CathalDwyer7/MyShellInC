//Introduction
Welcome to MyShell, a simple command-line shell program designed to help you interact with your computer more effectively. MyShell provides a user-friendly interface for executing commands, managing files, and controlling processes on your system. Whether you're a beginner to UNIX-like systems or an experienced user, MyShell offers an intuitive and efficient way to work with your computer.

//Getting Started
To use MyShell, simply open your terminal or command prompt and navigate to the directory where the MyShell executable is located. You can then start MyShell by typing ./bin/myshell and pressing Enter.

Basic Commands
MyShell supports a variety of basic commands that you can use to perform common tasks. Here are some of the most commonly used commands:

- cd [directory]: Change directory. Use cd <directory> to navigate to a specific directory.
EXAMPLE: "$ cd src"

- clr: Clear the screen. Simply type clr and press Enter to clear the terminal screen.
EXAMPLE: "$ clr"

- cd: Writes the full pathname of the current working directory to the standard output.
Example: "$ cd"

- dir : List directory contents. Typing dir will display the files and folders in the current directory.
EXAMPLE: "$ dir"

- dir [directory]: List directory contents of the selected [directory] in the command line. It will display the files and folders in the current directory.
EXAMPLE: "$ dir src"

- environ: List environment variables. Use environ to view a list of environment variables set in your shell.
EXAMPLE: "$ environ"

- echo: Print text. Type echo <text> to display the specified text on the screen.
EXAMPLE: "$ echo Hello, World!"

- help: Display user manual. Simply type help to view the user manual within MyShell.
EXAMPLE: "$ help"

- pause: Pause operation. Use pause to temporarily halt the shell until you press Enter.
EXAMPLE: "$ pause"

// Advanced Features

MyShell also has advanced features to enhance your user experience:

- Batch Mode: You can provide MyShell with a batch file containing a series of commands to execute. Use ./myshell batchfile to run commands from a file.
EXAMPLE: Suppose you have a batch file named commands.txt containing the following commands:

"commands.txt"
dir src

You can run these commands in MyShell using batch mode:
"$ ./bin/myshell commands.txt"

- Input/Output Redirection: MyShell supports redirection of standard input and output using batch mode. You can use < to redirect input from a file and > or >> to redirect output to a file.
EXAMPLE: Suppose you have a file named input.txt containing some text. You can redirect this file as input to a command:

"Orediretion.txt"
echo "Hello, world!" > output.txt

./bin/myshell Orediretion.txt

This command will create a new file named output.txt containing the text "Hello, world!".

- Background Execution: MyShell allows you to run commands in the background by appending & to the end of the command. This allows you to continue using the shell while the command runs in the background.
MyShell will execute the command in the background, allowing you to continue using the shell while the command runs.


//Conclusion

I hope this user manual helps you get started with MyShell. If you have any questions or encounter any issues, feel free to consult the user manual or reach out for assistance. Happy shell scripting!

Cathal Dwyer

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
 * - Love, R. (2010). Linux system programming: Talking directly to the kernel and C library. O'Reilly Media.
 *    - helped me on Linux system programming, including file I/O operations, system calls, and kernel interfaces.
 * - Stack overflow
 *    - Stack overflow helped me out when i was coding i/o redirection