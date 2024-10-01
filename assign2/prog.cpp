

/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Rayn Bannon, and Nathan Nguyen (TODO: your name)
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

/*
//Problom that could not be fix by me(nathan) yet
// test history and pipe
//test history give error 
Test Failed: When user type !!, the shell should print out the previous command and execute it again. If no previous command, print No command history found.

In grade scope
Correct output
osh> No commands history 
osh> 
Error, Not found in output: No command history
just lost what to do on this

//pipe did not attempt to do it yet
*/
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

#define MAX_LINE 80 // The maximum length command


char *history[100]; // Array to store command history
int history_count = 0; // Counter for history commands

/**
 * @brief Trims the newline character at the end of the command string
 *
 * @param command
 */
void trim_newline(char *command) {
    int len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
        command[len - 1] = '\0';  // Remove newline
    }
}

/**
 * @brief Parse the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int Number of arguments
 */
int parse_command(char command[], char *args[]) {
    int i = 0;
    char *current = command;
    char *start = NULL;

    while (*current) {
        if (*current == ' ' || *current == '\t' || *current == '\n' || *current == '&') {
            if (start) {
                *current = '\0'; // Null-terminate the string
                args[i++] = start; // Add the argument
                start = NULL; // Reset start
            }
        } else {
            if (!start) {
                start = current; // Mark the start of a new argument
            }
        }
        current++;
    }

    if (start) { // Handle the last argument if there is one
        args[i++] = start;
    }
    args[i] = NULL; // Null-terminate args array
    return i; // Return number of arguments
}

/**
 * @brief Add a command to history
 * 
 * @param command The command to add
 */
void add_to_history(char command[]) {
    if (history_count < 100) {
        history[history_count] = strdup(command); // Duplicate command string
        history_count++;
    } else {
        // Shift the history to make space for new entries (optional for handling overflow)
        free(history[0]); // Free the oldest command
        for (int i = 1; i < 100; i++) {
            history[i - 1] = history[i];
        }
        history[99] = strdup(command); // Add new command at the end
    }
}

/**
 * @brief Execute the command
 * 
 * @param args Command arguments
 * @param num_args Number of arguments
 * @return int Return status of the executed command
 */
int execute_command(char *args[], int num_args) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return -1;
    } else if (pid == 0) { // Child process
        // Check for input/output redirection
        for (int i = 0; i < num_args; i++) {
            if (strcmp(args[i], ">") == 0) {
                args[i] = NULL; // Terminate arguments before redirection
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("Could not open file for writing");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                break; // Exit loop after redirection
            } else if (strcmp(args[i], "<") == 0) {
                args[i] = NULL; // Terminate arguments before redirection
                int fd = open(args[i + 1], O_RDONLY);
                if (fd < 0) {
                    perror("Could not open file for reading");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                break; // Exit loop after redirection
            }
        }

        execvp(args[0], args);
        perror("Command not found");
        exit(1);
    }

    // Parent process
    return pid;
}

/**
 * @brief The main function of a simple UNIX Shell.
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    while (should_run) {
        printf("osh> ");           // Print the shell prompt
        fflush(stdout);

        // Read the input command
        if (fgets(command, MAX_LINE, stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        trim_newline(command); // Trim newline from input command

        // Add command to history before parsing or modifying it
        if (strlen(command) > 0 && strcmp(command, "!!") != 0) {
            add_to_history(command); // Save the command as it was entered
        }

        // Handle command history (when !! is used)
        if (strcmp(command, "!!") == 0) {
            if (history_count == 0) {
                printf("No commands in history.\n");
                continue;
            }
            // Retrieve last command from history
            strcpy(command, history[history_count - 1]); // Use last command
            printf("Last command: %s\n", command); // Print last command
        }

        // Parse the input command
        int num_args = parse_command(command, args);
        if (num_args == 0) {
            continue; // If no command was entered, skip to next iteration
        }

        // Handle exit command
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Check for background execution (&)
        bool background = false;
        if (num_args > 0 && strcmp(args[num_args - 1], "&") == 0) {
            background = true;
            args[num_args - 1] = NULL; // Remove '&' from arguments
            num_args--; // Adjust argument count
        }

        // Execute command
        int pid = execute_command(args, num_args);

        // If not running in the background, wait for child process
        if (!background) {
            waitpid(pid, NULL, 0); // Wait for the child process to finish
        }
    }

    // Free allocated memory for history
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }

    return 0;
}
