#include "shell.h"

int builtin_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s", args[i]);
        if (args[i + 1]) printf(" ");
    }
    printf("\n");
    return 0;
}

int builtin_cd(char **args) {
    if (!args[1]) {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}

int builtin_exit(char **args) {
    (void)args;
    exit(EXIT_SUCCESS);
}