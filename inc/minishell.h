/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 10:56:08 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>

/*typedef struct s_sig
{
	int exit_status;
}       t_sig;*/

typedef struct s_var
{
	char	*name;
	char	*value;
}			t_var;

typedef struct	s_env
{
	t_var			*var;
	struct s_env	*next;
}					t_env;


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