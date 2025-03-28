/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 16:54:56 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

char	*first_word(char *s)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			res = cutstr(s, s[0], ' ');
			if (!res)
				return (NULL);
			return (res);
		}
		i ++;
	}
	return (s);
}

void    process_cd(char *cmd, t_data *data)
{
    char    *path;

	data->exit_code = 0;
    path = NULL;
    path = ft_substr(cmd, 3, ft_strlen(cmd));  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
	if (strchri(path, ' ') != -1 && path[strchri(path, ' ') + 1] > 32) 
	{
		ft_printf("cd: too many arguments\n");
		return ;
	}
	if (path[ft_strlen(path) -1] == ' ')  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
		path = cutstr(path, path[0], ' ');
	//gerer les quotes;
    if (chdir(path) == -1)
	{
		data->exit_code = 1;
        ft_printf("cd: %s: No such file or directory\n", first_word(path));
	}
    free(path);
}

void    process_pwd(t_data *data)
{
    char    *path;

	data->exit_code = 0;
    path = NULL;
    path = getcwd(path, 0);
    if (path == NULL)
	{
		data->exit_code = 1;
        return ;
	}
    ft_printf("%s\n", path);
    free(path);
}

void    process_env(t_data *data)
{
	t_env	*current;

	current = data->env;
	data->exit_code = 0;
	while (current->next != NULL)
	{
		ft_printf("%s\n", current->vartest);
		current = current->next;
	}
}

void	process_export(char *cmd, t_data *data) //ne marche pas tout de suite, doit faire 2 fois avant que env l'affiche 
{
	t_env	*current;

	cmd = ft_substr(cmd, 7, ft_strlen(cmd));  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
	if (cmd == NULL)
	{
		data->exit_code = 1;
		return ;
	}
	current = data->env;
	while (current->next != NULL)
		current = current->next;
	current->next = (t_env *)malloc(sizeof(t_env));
	if (current->next == NULL)
		return ;
	current->next->vartest = ft_strdup(cmd); // peut aussi juste assigner cmd mais du coup même pointeur que la liste donc peut pas être free séparément, à voir ce qui est le mieux; si utilise strdup, ajouter protection.
	current->next->next = NULL;
	free(cmd);
	//ft_printf("%s\n", current->next->vartest);
}

void	process_unset(char *cmd, t_data *data)
{
	t_env	*current;

	cmd = ft_substr(cmd, 6, ft_strlen(cmd));  //ADAPT ONCE TOKENS ARE WORKING AND INTEGRATED
	if (cmd == NULL)
	{
		data->exit_code = 1;
		return ;
	}
	current = data->env;
	while (current->next->next != NULL)
	{
		if (!ft_strncmp(current->next->vartest, cmd, strchri(current->next->vartest, '=')))
			break;
		current = current->next;
	}
	//ft_printf("to delete : %s\n", current->next->vartest);
	current->next = current->next->next;
	//free? what?
}