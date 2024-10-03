
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
    char *token = strtok(command, "\n");    // token delimeter is 
    int argcount = 0;
    while (nullptr != token) {
        args[argcount] = token;

        printf("parsed argument[%d]: |%s|\n", argcount, args[argcount]);
        argcount++;

        token = strtok(nullptr, "\n");
    }
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

    // TODO: Add additional variables for the implementation.

    unsigned int loop = 0;
    while (should_run)
    {
        printf("osh[%u]>", loop++);
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        // Parse the input command
        int num_args = parse_command(command, args);

        if (num_args) {
            char *cmd = args[0];

            if (!strcmp(cmd, "quit")) {
                should_run = 0;     // exit while loop and terminate shell
            } else {
                // call fork determine child or parent if child
                // then do an if-else-statement for each commmand.
                // use that command and arguments to call execvp().

                // I would recommend you create a function:
                // void child(int numargs, char *args[]); and call
                // this function when you determine you are the child.

                pid_t pid = fork();
                if (0 == pid) {
                    printf("[child]\n");

                    exit(0);
                } else {
                    printf ("[parent]\n");
                    printf("child pid: %d\n", pid);
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
    return 0;
}
