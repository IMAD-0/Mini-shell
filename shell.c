#include "shell.h"

t_builtin g_builtins[] = {
    {"echo", builtin_echo},
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {NULL, NULL}
};

int execute(char **args) {
    if (!args[0]) return 1;
    
    for (int i = 0; g_builtins[i].name; i++) {
        if (strcmp(args[0], g_builtins[i].name) == 0) {
            return g_builtins[i].func(args);
        }
    }
    return launch_process(args);
}

void shell_loop(void) {
    char *line;
    char **args;

    while (1) {  // Boucle infinie contr�l�e en interne
        // Affiche le prompt seulement en mode interactif
        if (isatty(STDIN_FILENO))
            printf(GREEN ">$ " NC);
        fflush(stdout);  // Force l'affichage imm�diat

        line = read_line();
        if (!line)  // Gestion de Ctrl+D/EOF
            break;

        args = split_line(line);
        if (!args[0]) {  // Ligne vide
            free(line);
            free(args);
            continue;
        }

        execute(args);
        free(line);
        free(args);
    }
}

int main(void) {
	printBanner();
    shell_loop();
    return 0;
}
