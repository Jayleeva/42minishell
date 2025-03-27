/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:29 by yisho             #+#    #+#             */
/*   Updated: 2025/03/27 11:54:43 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

# include "../libft/inc/libft.h"

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