#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_sig
{
    int exit_status;
}       t_sig;

void process_input(char *input);