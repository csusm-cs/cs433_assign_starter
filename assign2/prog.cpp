/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Julian Rangel & Nick Andrew
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80

vector<string> history;


vector<string> split_command(const string& command) {
    vector<string> commands;
    string temp_command = command;
    size_t pos = 0;

    while ((pos = temp_command.find("|")) != string::npos) {
        commands.push_back(temp_command.substr(0, pos));
        temp_command.erase(0, pos + 1);
    }

    commands.push_back(temp_command);
    return commands;
}

int parse_command(char command[], char* args[]) {
    int args_count = 0;
    char* token = strtok(command, " \n");

    while (token != NULL) {
        if (token[strlen(token) - 1] == '&' && strlen(token) > 1) {
            args[args_count++] = strtok(token, "&");
            args[args_count++] = const_cast<char*>("&");
        } else {
            args[args_count++] = token;
        }

        if (strcmp(token, "!!") != 0) {
            history.push_back(token);
        }

        token = strtok(NULL, " \n");
    }

    args[args_count] = NULL;

    if (args_count > 0 && strcmp(args[args_count - 1], "&") == 0) {
        args[args_count - 1] = NULL;
        args_count--;
    }

    return args_count;
}

void last_command() {
    if (!history.empty()) {
        string last_command = history.back();
        cout << "Previous command: " << last_command << endl;
        char last_command_cstr[MAX_LINE];
        strcpy(last_command_cstr, last_command.c_str());
        char* args[MAX_LINE / 2 + 1];
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

            pid_t pid = fork();

            if (pid == 0) {
                if (run_in_background) {
                    fclose(stdin);
                    fclose(stdout);
                    fclose(stderr);
                }

                if (execvp(args[0], args) == -1) {
                    perror("Execvp failed");
                    printf("Command not found\n");
                    exit(1);
                }
            } else if (pid < 0) {
                perror("Fork failed");
            } else {
                if (!run_in_background) {
                    int status;
                    if (waitpid(pid, &status, 0) == -1) {
                        perror("Waitpid failed");
                    }
                }
            }
        }
    } else {
        cout << "No command history found." << endl;
    }
}

int main(int argc, char* argv[]) {
    char command[MAX_LINE];
    char* args[MAX_LINE / 2 + 1];
    int state = 1;

    if (getenv("PATH") == NULL) {
        setenv("PATH", "/usr/bin:/bin", 1);
    }

    while (state) {
        printf("osh>");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin);

        if (strcmp(command, "exit\n") == 0) {
            state = 0;
            continue;
        }

        if (strcmp(command, "!!\n") == 0){
            last_command();
            continue;
        }

        if (string(command).find("|") != string::npos) {
            vector<string> piped_commands = split_command(command);
            int num_pipes = piped_commands.size() - 1;
            int pipefds[2 * num_pipes];

            for (int i = 0; i < num_pipes; i++) {
                if (pipe(pipefds + i * 2) == -1) {
                    perror("Pipe creation failed");
                    exit(1);
                }
            }

            int cmd_index = 0;
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

                    for (int i = 0; i < 2 * num_pipes; i++) {
                        close(pipefds[i]);
                    }

                    if (execvp(args[0], args) == -1) {
                        perror("Execvp failed");
                        printf("Command not found\n");
                        exit(1);
                    }
                } else if (pid < 0) {
                    perror("Fork failed");
                    exit(1);
                }

                cmd_index++;
            }

            for (int i = 0; i < 2 * num_pipes; i++) {
                close(pipefds[i]);
            }

            for (int i = 0; i < num_pipes + 1; i++) {
                int status;
                if (wait(&status) == -1) {
                    perror("Wait failed");
                }
            }
        } else if (strcmp(command, "!!\n") == 0) {
            last_command();
        } else {
            int args_count = parse_command(command, args);

            int run_in_background = 0;
            if (args_count > 0 && strcmp(args[args_count - 1], "&") == 0) {
                run_in_background = 1;
                args[args_count - 1] = NULL;
            }

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

            pid_t pid = fork();

            if (pid == 0) {
                if (run_in_background) {
                    fclose(stdin);
                    fclose(stdout);
                    fclose(stderr);
                }

                if (input_file != NULL) {
                    int input_fd = open(input_file, O_RDONLY);
                    if (input_fd < 0) {
                        perror("Input redirection failed");
                        exit(1);
                    }
                    if (dup2(input_fd, STDIN_FILENO) == -1) {
                        perror("Dup2 failed");
                        exit(1);
                    }
                    close(input_fd);
                }

                if (output_file != NULL) {
                    int output_fd;
                    if (strcmp(args[0], ">>") == 0) {
                        output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
                    } else {
                        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    }
                    if (output_fd < 0) {
                        perror("Output redirection failed");
                        exit(1);
                    }
                    if (dup2(output_fd, STDOUT_FILENO) == -1) {
                        perror("Dup2 failed");
                        exit(1);
                    }
                    close(output_fd);
                }

                if (execvp(args[0], args) == -1) {
                    perror("Execvp failed");
                    printf("Command not found\n");
                    exit(1);
                }
            } else if (pid < 0) {
                perror("Fork failed");
                exit(1);
            } else {
                if (!run_in_background) {
                    int status;
                    if (waitpid(pid, &status, 0) == -1) {
                        perror("Waitpid failed");
                    }
                }
            }
        }
    }

    return 0;
}
