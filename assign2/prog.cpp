/**
 * Assignment 2: Simple UNIX Shell
 * @file prog.cpp
 * @author Julian Rangel & Nick Andrew
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <algorithm>

using namespace std;

#define MAX_LINE 80

vector<string> history;

//This is what splits the commands into seprerate lines
//for the history to keep track of

vector<string> split_command(const string& command) {
    vector<string> commands;
    string temp_command = command;
    size_t pos = 0;

    //While there is a command to split, it will continue
    while ((pos = temp_command.find("|")) != string::npos) {
        commands.push_back(temp_command.substr(0, pos));
        temp_command.erase(0, pos + 1);
    }

    //Add the split command to th commands list
    commands.push_back(temp_command);
    return commands;
}

//Parses the commands based on a space or a new line charcter

int parse_command(char command[], char* args[]) {
    int args_count = 0;
    char* token = strtok(command, " \n");

    //While there are still tokens to sort, we continue to add
    //them to the list
    while (token != NULL) {
        if (token[strlen(token) - 1] == '&' && strlen(token) > 1) {
            args[args_count++] = strtok(token, "&");
            args[args_count++] = const_cast<char*>("&");
        } else {
            args[args_count++] = token;
        }

        //if the command is not the !! command, we will add it to the
        //history
        if (strcmp(token, "!!") != 0) {
            history.push_back(token);
            cout << "This is what was jsut added to History: " << token << endl;
        }

        token = strtok(NULL, " \n");
    }

    args[args_count] = NULL;

    //if we are completing a command with an & at the end, we will manually remove the item from the list and reduece the count
    if (args_count > 0 && strcmp(args[args_count - 1], "&") == 0) {
        args[args_count - 1] = NULL;
        args_count--;
    }

    return args_count;
}

void last_command() {
    //This is used to recall the history of commands that have been entered
    if (!history.empty()) {
        string last_command = history.back();
        cout << "Previous command: " << last_command << endl;
        char last_command_cstr[MAX_LINE];
        strcpy(last_command_cstr, last_command.c_str());
        
        char* args[MAX_LINE / 2 + 1];
        //Proceeds to respond based on the state of the command and if it should be running in the background or not
        int args_count = parse_command(last_command_cstr, args);

        if (args_count > 0) {
            if (strcmp(args[0], "exit") == 0) {
                exit(0);
            }

            int run_in_background = 0;

            if (args_count > 0 && strcmp(args[args_count - 1], "&") == 0) {
                run_in_background = 1;
                args[args_count - 1] = NULL;
            }

            //creates a fork for the command to be executed on
            pid_t pid = fork();

            if (pid == 0) {
                //cases for if it should be a background program
                if (run_in_background) {
                    fclose(stdin);
                    fclose(stdout);
                    fclose(stderr);
                }
                //catch statements for if basic command inputs are not valid
                if (execvp(args[0], args) == -1) {
                    perror("Execvp failed");
                    printf("Command not found\n");
                    exit(1);
                }
            //Checks for if a fork creation failed
            } else if (pid < 0) {
                perror("Fork failed");
            } else {
                //runs in the can that the program is not set to run in the background
                if (!run_in_background) {
                    int status;
                    if (waitpid(pid, &status, 0) == -1) {
                        perror("Waitpid failed");
                    }
                }
            }
        }
    } else {
	//outputs if there is no argument in the command history
        cout << "No command history found." << endl;
    }
}

int main(int argc, char* argv[]) {
    //var for the incoming command
    char command[MAX_LINE];
    //var for the maximum number of arguments
    char* args[MAX_LINE / 2 + 1];
    //sets the state of the program
    int state = 1;

    if (getenv("PATH") == NULL) {
        //sets a default file path
        setenv("PATH", "/usr/bin:/bin", 1);
    }

    //while loop that handles the incoming commands
    while (state) {
        printf("osh>");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin);

        //closes the program in the command is 'exit'
        if (strcmp(command, "exit\n") == 0) {
            state = 0;
            continue;
        }

        //reads and runs the last command is the input is '!!'
        if (strcmp(command, "!!\n") == 0){
            last_command();
            continue;
        }

        if (string(command).find("|") != string::npos) {
            //Vector for the piped_commands if more than one are in queue
            vector<string> piped_commands = split_command(command);
            int num_pipes = piped_commands.size() - 1;
            int pipefds[2 * num_pipes];

            for (int i = 0; i < num_pipes; i++) {
                //Checks and catches any failures to create pipes
                if (pipe(pipefds + i * 2) == -1) {
                    perror("Pipe creation failed");
                    exit(1);
                }
            }

            int cmd_index = 0;

            //For each of the created pipes, checks the stage in the queued list of commands and executes them in order
            for (const string& cmd : piped_commands) {
                char cmd_cstr[MAX_LINE];
                strcpy(cmd_cstr, cmd.c_str());
                int args_count = parse_command(cmd_cstr, args);

                pid_t pid = fork();
                if (pid == 0) {
                    if (cmd_index > 0) {
                        if (dup2(pipefds[(cmd_index - 1) * 2], STDIN_FILENO) == -1) {
                            perror("Dup2 failed");
                            exit(1);
                        }
                    }
                    if (cmd_index < num_pipes) {
                        if (dup2(pipefds[cmd_index * 2 + 1], STDOUT_FILENO) == -1) {
                            perror("Dup2 failed");
                            exit(1);
                        }
                    }
                    //Closes any superfluous pipes
                    for (int i = 0; i < 2 * num_pipes; i++) {
                        close(pipefds[i]);
                    }

                    //catches any non-eleigible commands
                    if (execvp(args[0], args) == -1) {
                        perror("Execvp failed");
                        printf("Command not found\n");
                        exit(1);
                    }
                //Catches failed fork creation
                } else if (pid < 0) {
                    perror("Fork failed");
                    exit(1);
                }
                //Increments command index
                cmd_index++;
            }

            //closes all pipes when finished
            for (int i = 0; i < 2 * num_pipes; i++) {
                close(pipefds[i]);
            }

            for (int i = 0; i < num_pipes + 1; i++) {
                int status;
                if (wait(&status) == -1) {
                    perror("Wait failed");
                }
            }
        //Same as previous reading command of '!!'
        } else if (strcmp(command, "!!\n") == 0) {
            last_command();
        } else {
            int args_count = parse_command(command, args);

            int run_in_background = 0;
            //else case that deals with deafult commands without the need to create new threads or pipes
            if (args_count > 0 && strcmp(args[args_count - 1], "&") == 0) {
                run_in_background = 1;
                args[args_count - 1] = NULL;
            }

            //reads command of '<', '>' or '>>' and responds appropriately
            char* input_file = NULL;
            char* output_file = NULL;
            for (int i = 0; i < args_count; i++) {
                if (strcmp(args[i], "<") == 0) {
                    if (i + 1 < args_count) {
                        input_file = args[i + 1];
                        args[i] = NULL;
                        args[i + 1] = NULL;
                        break;
                    }
                } else if (strcmp(args[i], ">") == 0) {
                    if (i + 1 < args_count) {
                        output_file = args[i + 1];
                        args[i] = NULL;
                        args[i + 1] = NULL;
                        break;
                    }
                } else if (strcmp(args[i], ">>") == 0) {
                    if (i + 1 < args_count) {
                        output_file = args[i + 1];
                        args[i] = NULL;
                        args[i + 1] = NULL;
                        break;
                    }
                }
            }

            //Creates a new fork
            pid_t pid = fork();

            if (pid == 0) {
                if (run_in_background) {
                    fclose(stdin);
                    fclose(stdout);
                    fclose(stderr);
                }

                if (input_file != NULL) {
                    //Attempts to open a file for the user to record in
                    int input_fd = open(input_file, O_RDONLY);
                    if (input_fd < 0) {
                        //catches failed inout redirection
                        perror("Input redirection failed");
                        exit(1);
                    }
                    if (dup2(input_fd, STDIN_FILENO) == -1) {
                        //catches failed directory duplication
                        perror("Dup2 failed");
                        exit(1);
                    }
                    //closes input file directory
                    close(input_fd);
                }

                //As long as there is an output file, this code will continue to read the command inputs that would pertain to the output file
                if (output_file != NULL) {
                    int output_fd;
                    if (strcmp(args[0], ">>") == 0) {
                        output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
                    } else {
                        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    }
                    //catches failure of output redirection
                    if (output_fd < 0) {
                        perror("Output redirection failed");
                        exit(1);
                    }
                    //catches failure of output duplication
                    if (dup2(output_fd, STDOUT_FILENO) == -1) {
                        perror("Dup2 failed");
                        exit(1);
                    }
                    //closes output file directory
                    close(output_fd);
                }
                //catches non-eligible commands
                if (execvp(args[0], args) == -1) {
                    perror("Execvp failed");
                    printf("Command not found\n");
                    exit(1);
                }
            } else if (pid < 0) {
                //catches failure of fork creation
                perror("Fork failed");
                exit(1);
            } else {
                if (!run_in_background) {
                    int status;
                    //catches waitpid failure for non-background commands
                    if (waitpid(pid, &status, 0) == -1) {
                        perror("Waitpid failed");
                    }
                }
            }
        }
    }

    return 0;
}
