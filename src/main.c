/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:27:40 by yisho             #+#    #+#             */
/*   Updated: 2025/05/06 15:34:06 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_data.h"
#include "../inc/linked_list.h"
#include "../libft/inc/libft.h"

int	count_var(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i ++;
	return (i);
}

void	divide_var(t_env *current, char *env, int exported)
{
	if (!ft_isalnum(env[0]))
		exported = -1;
	current->name = ft_substr(env, 0, strchri(env, '='));
	current->value = ft_substr(env, strchri(env, '=') + 1, ft_strlen(env));
	current->exported = exported;
}

t_env	*init_env(char **envp, int nvar)
{
	int		i;
	t_env	*export;
	t_env	*current;

	export = (t_env *)malloc(sizeof(t_env));
	if (export == NULL)
		return (NULL);
	export->var = envp[0];
	divide_var(export, envp[0], 1);
	export->next = NULL;
	i = 1;
	current = export;
	while (i < nvar)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_env *)malloc(sizeof(t_env));
		if (current->next == NULL)
			return (NULL);
		current->next->var = envp[i];
		divide_var(current->next, envp[i], 1);
		current->next->next = NULL;
		i ++;
	}
	return (export);
}

void	init_data(t_data *data)
{
	data->exit_code = 0;
	data->paths = NULL;
	data->token = NULL;
	data->env = NULL;
	data->export = NULL;
	data->cmd = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->last_pid = -1;
	data->child_pids = NULL;
	data->child_count = 0;
}

int main(int argc, char **argv, char **envp) 
{
    t_data  	data;
	int			nvar;
	//static int	i = 0; 				// doesn't work with a static. I need to know if this current process is a child

	(void)argv;
    if (argc == 3)
		return (1);
	init_data(&data);
	if (!envp) // backup in case of (env -i) no environment received, in this case you could generate manually your env data if some is critical to the program, or set all to NULL
	{
		ft_putstr_fd("Error: no environment received\n", 2);
		exit(1);
	}
	nvar = count_var(envp);
	data.env = init_env(envp, nvar);
	//if (getpid() > getppid()) 			// doesn't work.
	//	update_env(data.env, "SHLVL", "+1");
	/*if (i > 0) 						// if is a child:
		update_env(data.env, "SHLVL", "1");
	i ++;*/
	minishell_interactive(&data);
	return (0);
}