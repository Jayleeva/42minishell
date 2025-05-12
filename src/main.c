/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:27:40 by yisho             #+#    #+#             */
/*   Updated: 2025/05/12 12:31:50 by cyglardo         ###   ########.fr       */
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

int	divide_var(t_env *current, char *var, int exported)
{
	if (!ft_isalnum(var[0]))
		exported = -1;
	current->name = ft_substr(var, 0, strchri(var, '='));
	if (!current->name)
		return (0);
	current->value = ft_substr(var, strchri(var, '=') + 1, ft_strlen(var));
	if (!current->value)
		return (0);
	current->exported = exported;
	return (1);
}

t_env	*init_env(char **envp, int nvar, int i)
{
	t_env	*export;
	t_env	*current;

	export = (t_env *)malloc(sizeof(t_env));
	if (export == NULL)
		return (NULL);
	export->var = envp[0];
	if (!divide_var(export, envp[0], 1))
		return (NULL);
	export->next = NULL;
	current = export;
	while (i < nvar)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_env *)malloc(sizeof(t_env));
		if (current->next == NULL)
			return (NULL);
		current->next->var = envp[i];
		if (!divide_var(current->next, envp[i], 1))
			return (NULL);
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
	data->cmd = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->last_pid = -1;
	data->child_pids = NULL;
	data->child_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		nvar;

	(void)argv;
	if (argc == 3)
		return (1);
	init_data(&data);
	if (!envp)
	{
		ft_putstr_fd("Error: no environment received\n", 2);
		free_all(&data, 1);
	}
	nvar = count_var(envp);
	data.env = init_env(envp, nvar, 1);
	minishell_interactive(&data);
	return (0);
}
