#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define BUFFER_SIZE 64


#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define NC      "\033[0m" // No Color

typedef struct s_builtin {
    const char *name;
    int (*func)(char **args);
} t_builtin;

/* shell.c */
void    shell_loop(void);
char    *read_line(void);
char    **split_line(char *line);
int     execute(char **args);

/* builtins.c */
int     builtin_echo(char **args);
int     builtin_cd(char **args);
int     builtin_exit(char **args);

/* utils.c */
int     launch_process(char **args);
void printBanner(void);

#endif
