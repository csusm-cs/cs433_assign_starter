
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author ??? (TODO: your name)
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
    // TODO: implement this function
     int args_count = 0;
    char *token = strtok(command, " ");

    while(token != NULL && args_count < MAX_LINE){
        args[args_count++] = token;
        token = strtok(nullptr," ");
    }

    args[args_count] = nullptr;

    return args_count;
}

// TODO: Add additional functions if you need
void last_command(){

    if(!history.empty()){ // checks to see if hsitory is empty
        string prev_command = history.back(); // retrieves last command
        char prev_command_cstr[MAX_LINE];  //C string
        strcpy(prev_command_cstr, prev_command.c_str()); //gets copied to other string
        char *args[MAX_LINE/2+1]; 
        int args_count = parse_command(prev_command_cstr, args); //parse arguments and store them in args array

        if(args_count < 0){ //special command check see if num of arguments is negative
            if(strcmp(args[0], "exit")==0){
                exit(0);
            }
        }
        //handle background execution
        int background = 0;
        if(args_count > 0 && strcmp(args[args_count - 1], "&") == 0){ //checks if last argument is '&' then modifies background accordingly
            background = 1;
            args[args_count - 1] = nullptr;
        }

        pid_t pid = fork(); //forks the process

        if(pid == 0){

            if(background){ //close input, output, and error if in background
                fclose(stdin);
                fclose(stdout);
                fclose(stderr);
            }
            if(execvp(args[0], args) == -1){ //execute command
                perror("execvp failed.");
                printf("command not found\n");
                exit(1);
            }
        }else if(pid < 0){
            perror("fork faild.");
        }else{
            if(!background){ 
                int state; //if not in background wait for child to finish
                if(waitpid(pid, &state, 0) == -1){ 
                    perror("waitpid failed");
                }
            }
        }
    }
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
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    // TODO: Add additional variables for the implementation.
     pthread_t tid; //the thread identifier
    pthread_attr_t attr; //set attribute of the thread

    if(argc != 2){
        fprintf(stderr, "usage: %s <integer val> \n", argv[0]);

        return -1;
    }

    pthread_attr_init(&attr); //set default attributes

    pthread_create(&tid, &attr, runner, argv[1]); //create the thread

    pthread_join(tid, NULL); //wait for thread to exit

    printf("parent print sum = %d\n",sum);
    
    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        // Parse the input command
        int num_args = parse_command(command, args);

        // TODO: Add your code for the implementation
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) parent will invoke wait() unless command included &
         */
    }
    return 0;
}
//thread begins in control function
void *runner(void *param){
    int upper = atoi(param);
    sum = 0;
    cout << "Running the child thread" << endl;
    
    if(upper > 0){
        for(int i = 0; i <= upper; i++){
            sum++;
        }
    }

}
