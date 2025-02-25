/**
 * Simple UNIX Shell Implementation
 * Following original parameter structure
 */
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>
using namespace std;

#define MAX_LINE 80 // The maximum length command

// Global variables for history feature
char last_command[MAX_LINE] = {0};
bool has_history = false;

/**
 * Parse command into tokens
 * @param command Input command string
 * @param args Array to store command arguments
 * @return Number of arguments
 */
int parse_command(char command[], char *args[]) {
    int i = 0;
    char *token;
    
    // Remove newline if present
    size_t len = strlen(command);
    if (len > 0 && command[len-1] == '\n') {
        command[len-1] = '\0';
    }
    
    // Parse the command using strtok
    token = strtok(command, " ");
    while (token != NULL && i < MAX_LINE/2) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    
    args[i] = NULL;  // Null terminate the argument list
    return i;
}

/**
 * Main function implementing the shell
 */
int main(void) {
    char command[MAX_LINE];       // Command entered
    char *args[MAX_LINE/2 + 1];   // Command line arguments
    int should_run = 1;           // Flag to determine when to exit program
    
    while (should_run) {
        printf("osh>");
        fflush(stdout);
        
        // Read the command
        if (!fgets(command, MAX_LINE, stdin)) {
            break;
        }
        
        // Handle history (!!) command
        if (strcmp(command, "!!\n") == 0) {
            if (!has_history) {
                printf("No commands in history.\n");
                continue;
            }
            printf("%s", last_command);
            strcpy(command, last_command);
        } else {
            strcpy(last_command, command);
            has_history = true;
        }
        
        // Parse the command
        int num_args = parse_command(command, args);
        if (num_args == 0) continue;
        
        // Check for exit command
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }
        
        // Check for background operation
        bool background = false;
        if (strcmp(args[num_args-1], "&") == 0) {
            background = true;
            args[num_args-1] = NULL;
            num_args--;
        }
        
        // Check for I/O redirection
        char *input_file = NULL;
        char *output_file = NULL;
        for (int i = 0; i < num_args; i++) {
            if (strcmp(args[i], "<") == 0) {
                input_file = args[i + 1];
                args[i] = NULL;
                i++;
            } else if (strcmp(args[i], ">") == 0) {
                output_file = args[i + 1];
                args[i] = NULL;
                i++;
            }
        }
        
        // Fork and execute command
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed");
            continue;
        }
        
        if (pid == 0) { // Child process
            // Handle input redirection
            if (input_file != NULL) {
                int fd = open(input_file, O_RDONLY);
                if (fd == -1) {
                    perror("Error opening input file");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            
            // Handle output redirection
            if (output_file != NULL) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("Error opening output file");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            
            // Execute the command
            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
                exit(1);
            }
        } else { // Parent process
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }
    }
    
    return 0;
}