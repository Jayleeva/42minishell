/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 16:18:23 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

char	*first_word(const char *s)
{
	char	*res;

	res = cutstr(s, s[0], ' ');
	if (!res)
		return (NULL);
	return (res);
}

void    process_cd(char *cmd, t_data *data)
{
    char    *path;
	//char	*set;
	//int		i;

	data->exit_code = 0;
	/*set = ft_calloc(11, sizeof(char));
	if (set == NULL)
		return ;
	set = "\0\n\t ";*/
    path = NULL;
    path = ft_substr(cmd, 3, ft_strlen(cmd));
	if (strchri(path, ' ') != -1 && path[strchri(path, ' ') + 1] > 32) 
	{
		ft_printf("cd: too many arguments\n");
		return ;
	}
	/*i = 0;
	while (set[i])
    {
		write(1, &set[i], 1);
		path = cutstr(path, path[0], set[i]); //ATTENTION: si autre chose après le path, n'est pas pris en compte + pour l'instant ne gère pas les quotes
		i ++;
	}*/
	if (path[ft_strlen(path)] == ' ')
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

	cmd = ft_substr(cmd, 7, ft_strlen(cmd));
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
	current->next->vartest = cmd;
	current->next->next = NULL;
	//ft_printf("%s\n", current->next->vartest);
}

/*void	process_unset(char *cmd, t_sig *g_sig, t_data *data)
{
	
}*/