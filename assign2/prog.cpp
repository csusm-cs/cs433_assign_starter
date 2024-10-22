
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Zach Miller
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */


int parse_command(char command[], char *args[])
{
    char *token = strtok(command, " \n");   // Handle both spaces and newlines
    int argcount = 0;   // int to keep track of arguments
    while (token != nullptr) {      // loops through whole command until end
        //printf("token: %s\n", token);
        args[argcount] = token;
        //printf("parsed argument[%d]: |%s|\n", argcount, args[argcount]);
        argcount++;
        token = strtok(nullptr, " \n");
    }
    args[argcount] = nullptr;  // End the argument list
    return argcount;
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char command_history[MAX_LINE];       // the command that was entered
    command_history[0] = '\0';
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */  

    unsigned int loop = 0;  // int to keep track of command count
    while (should_run)
    {
        int background = 0;     // to keep track of background process

        printf("osh[%u]>", loop++);
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);

        if (strcmp(command, "!!\n")) {
            strcpy(command_history, command);
        }

// Parse the input command
        int num_args = parse_command(command, args);


        if (!num_args)
            continue;

        // check for history command
        if (strcmp(args[0], "!!") == 0) {
            if (!strlen(command_history)) {       // if history is empty, then print no commands
                printf("No command history found.\n");
                continue;
            } else {
            // copy command in history to args
            cout << "previous command: " << command_history << "\n";
            num_args = parse_command(command_history, args);
            }
            
        }

        if (num_args) {
            char *cmd = args[0];

            if (!strcmp(cmd, "exit")) {
                should_run = 0;     // exit while loop and terminate shell
            } else {                // call fork determine child or parent if child

                for (int i = 0; i < num_args; i++)  // iterates through num_args 
                {
                    int length = strlen(args[i]);
                    if ('&' == args[i][length - 1])     // if there is an &, remove it from command and then continue executing as normal
                    {
                        //printf("running in background: %s\n", args[0]);
                        args[i][length - 1] = '\0';
                        background = 1;
                    }
                }

                pid_t pid = fork();     // fork process
                if (pid == 0) {
                    execvp(args[0], args);  // execute args[0]
                    command_history[0] = '\0';  
                    perror("execvp");    // if execvp fails, print error message
                    exit(0);
                } else if (pid < 0) {
                    perror("Fork Failed.");     // if fork fails print error message, then exit
                    exit(EXIT_FAILURE);
                } else {
                    if (!background) {
                    wait(NULL);     // parent process waits for the child to exit
                    }
                }
            }
        }

    }
    return 0;
}