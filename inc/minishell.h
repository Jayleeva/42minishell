#ifndef MINISHELL_H
# define MINISHELL_H
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

/*
* <
* <<
* >
* >>
* |
* command
* argument
*/
typedef enum e_token_type
{
	INPUT = 1,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE,
	CMD,
	ARG,
}	t_token_type;

typedef unsigned char	t_bool;
# define TRUE 1
# define FALSE 0
#endif