
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
        args[argcount] = token;
        printf("parsed argument[%d]: |%s|\n", argcount, args[argcount]);
        argcount++;
        token = strtok(nullptr, " \n");
    }
    args[argcount] = nullptr;  // End the argument list
    return argcount;
}


// TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */
    char *history = nullptr;

    // TODO: Add additional variables for the implementation.

    unsigned int loop = 0;  // int to keep track of command count
    while (should_run)
    {
        printf("osh[%u]>", loop++);
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        
         //cout << "This is history right after it is typed: " << history;
        // Parse the input command
        int num_args = parse_command(command, args);

        // check for history command
        if (strncmp(args[0], "!!", 2) == 0) {
            if (history == nullptr) {       // if history is empty, then print no commands
                printf("No commands in history.\n");
                break;
            } else {
            // copy command in history to args
            strcpy(command, history);
            cout << "history: " << history;
            num_args = parse_command(command, args);     // parse the history command again
            printf("Executing previous command: %s\n", command);
            }

        } else {
            // Save command into history
            free(history);
            history = strdup(command);
        }

        


        if (num_args) {
            char *cmd = args[0];

            if (!strcmp(cmd, "exit")) {
                should_run = 0;     // exit while loop and terminate shell
            } else {
                // call fork determine child or parent if child
                // then do an if-else-statement for each commmand.
                // use that command and arguments to call execvp().

                // I would recommend you create a function:
                // void child(int numargs, char *args[]); and call
                // this function when you determine you are the child.

                pid_t pid = fork();
                if (pid == 0) {
                    printf("[child]\n");
                    execvp(args[0], args);
                    perror("execvp");    // if execvp fails, print error message
                    exit(0);
                } else if (pid < 0) {
                    perror("Fork Failed.");     // if fork fails print error message, then exit
                    exit(EXIT_FAILURE);
                } else {
                    printf ("[parent]\n");
                    printf("-----------\n");
                    //printf("child pid: %d\n", pid);
                    wait(NULL);     // parent process waits for the child to exit
                }
            }
        }
        

        // TODO: Add your code for the implementation
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */
        //cout << parse_command(command, args);

    }
    free(history);
    return 0;
}
