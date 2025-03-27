/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 15:46:43 by cyglardo         ###   ########.fr       */
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

	data->exit_code = 0;
	while (data->env->next != NULL)
	{
		ft_printf("%s\n", data->env->vartest);
		//ft_printf("%s=%s\n", data->env->var.name, data->env->var.value);
		data->env = data->env->next;
	}
}

/*void	process_export(char *cmd, t_data *data, char **envp)
{
	char	*var;
	//int		i;
	int		len;

	(void)envp;
	cmd = ft_substr(cmd, 7, ft_strlen(cmd));
	if (cmd == NULL)
	{
		data->exit_code = 1;
		return ;
	}
	len = strchri(cmd, '=');
	if (len == -1)
	{
		data->exit_code = 1;
		return ;
	}
	var = ft_calloc(len, sizeof(char));
	if (var == NULL)
		return ;
	var = ft_memcpy(var, cmd, len);
	var[len] = '\0';
	if (getenv(var))
	{
		ft_printf("%s exists already\n", var);
	}
	else
	{
		//ajouter var en dernière ligne à envp
		while (envp->next != NULL)
			envp = envp->next;
		envp->next = NULL;
		envp->var->name = var;
		envp->var->value = value;
		ft_printf("%s was created\n", var);
	}
	free(var);
}*/

/*void	process_unset(char *cmd, t_sig *g_sig, t_data *data)
{
	
}*/