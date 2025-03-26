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

char    *first_word(const char *s);
void	process_cmd(char *input, t_sig *g_sig);
void	process_cd(char *cmd, t_sig *g_sig);
void    process_pwd(t_sig *g_sig);
void    process_env(char *cmd, t_sig *g_sig);
//void	process_export(char *cmd, t_sig *g_sig);
//void	process_unset(char *cmd, t_sig *g_sig);
void    process_echo(char *cmd, t_sig *g_sig);
void    process_exit(void);
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