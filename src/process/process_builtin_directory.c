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
