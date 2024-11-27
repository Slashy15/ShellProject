#include "shell.h"

#include <stdio.h>

#include "utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFFER_SIZE 128

void shell_loop() {
    char input[BUFFER_SIZE];

    while (1) {
        // Show the prompt
        write_message("enseash % ");

        // Read the input of the user
        ssize_t bytes_read = read(STDIN_FILENO, input, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            write_message("Error of reading.\n");
            continue;
        }

        input[bytes_read - 1] = '\0';

        if (strncmp(input, "exit", BUFFER_SIZE) == 0) {
            break;
        }

        if (bytes_read == 1) {
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            write_message("Error to create the processus.\n");
            continue;
        } else if (pid == 0) {
            char *args[] = {input, NULL};
            if (execvp(input, args) == -1) {
                write_message("Error: Command doesn't exist, please retry.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                write_message("Command done\n");
            } else {
                write_message("Command done but strangely\n");
            }
        }
    }
}

