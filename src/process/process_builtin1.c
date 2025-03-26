/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/26 13:08:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../inc/token.h"
#include "../../libft/inc/libft.h"

void    process_cd(char *cmd, t_data *data)
{
    char    *path;

	data->exit_code = 0;
    path = NULL;
    path = ft_substr(cmd, 3, ft_strlen(cmd));
    path = cutstr(path, path[0], " \n\t\r\b\0");  //ATTENTION: si autre chose après le path, n'est pas pris en compte + pour l'instant ne gère pas les quotes OBLIGE DE METTRE UN ESPACE APRES LE PATH POUR QUE CA MARCHE, A CORRIGER
	ft_printf("%s\n", path);
    if (chdir(path) == -1)
	{
		data->exit_code = 1;
        ft_printf("cd: %s: No such file or directory\n", path);
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

void    process_env(t_data *data, char ***envp)
{
	int		i;

	data->exit_code = 0;
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i ++;
	}
}

/*void	process_export(char *cmd, t_data *data, char ***envp)
{
	char	*var;
	//int		i;
	int		len;

	(void)data;
	cmd = ft_substr(cmd, 7, ft_strlen(cmd));
	if (cmd == NULL)
		return ;
	len = strchri(cmd, '=');
	if (len == -1)
		return ;
	var = (char *)malloc((len + 1) * sizeof(char));
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
		ft_printf("%s was created\n", var);
	}
	free(var);
}*/

/*void	process_unset(char *cmd, t_sig *g_sig, t_data *data)
{
	
}*/