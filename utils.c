#include "shell.h"

char *read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t n_read;

    n_read = getline(&line, &bufsize, stdin);
    if (n_read <= 0) {
        free(line);
        return NULL;
    }
    if (line[n_read - 1] == '\n')
        line[n_read - 1] = '\0';
    return line;
}

char **split_line(char *line) {
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    token = strtok(line, " \t\r\n");
    while (token) {
        tokens[position++] = token;
        if (position >= bufsize) {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
        }
        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return tokens;
}

int launch_process(char **args) {
    pid_t pid = fork();
    
    if (pid == 0) {
        execvp(args[0], args);
        perror("shell");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    } else {
        perror("fork");
        return 1;
    }
}


void printBanner(void) {
    printf(BLUE);
    printf("    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
    printf(" ██╗██╔════╝██║  ██║██╔════╝██║     ██║     \n");
    printf(" ╔═╝███████╗███████║█████╗  ██║     ██║     \n");
    printf(" ██╗╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
    printf(" ██║███████║██║  ██║███████╗███████╗███████╗\n");
    printf(" ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
    printf(NC);
    printf("%s          ===========================\n", GREEN);
    printf("%s             Par       : MRIMI Imad\n", GREEN);
    printf("             Version   : 0.1\n");
    printf("%s          ===========================%s\n", GREEN, NC);
}
