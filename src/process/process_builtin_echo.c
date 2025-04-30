/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/29 17:07:47 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    process_echo(t_data *data, char **argv) //ATTENTION segfault par moment / fait segfault exit si echo plusieurs string (avec espaces) avant, chercher pourquoi
{
    char    *s;
    char    *temp;
    int     i;
    int     n_flag;

    n_flag = 0;
    s = "";
    temp = NULL;
    data->exit_code = 0;
    if (!argv[1]) //si pas d'arguments donné, imprime juste un retour à la ligne.
    {
        ft_printf("\n");
        return ;
    }
    else if (argv[1] && !ft_strncmp(argv[1], "-n", 2) && !argv[2]) //si flag -n mais pas d'argument après, imprime vide (sans retour à la ligne).
    {
        ft_printf("");
        return ;
    }
    i = 1;
    if (!ft_strncmp(argv[1], "-n", 2))
    {
        i = 2;
        n_flag = 1;
    }
    while (argv[i])
    {
        if (argv[i][0] == '$' && argv[i][1] && argv[i][1] != '?') // if echo '$HOME' for example, prints NULL instead (the quotes seem to stop it from finding the variable)
        {
            temp = get_env_value(data->env, ft_substr(argv[i], 1, ft_strlen(argv[i]))); 
            if (!temp)
                temp = ft_strdup("");
        }
        else
            temp = ft_strdup(argv[i]);
        s = ft_strjoin(s, temp);
        if (argv[i + 1])
            s = ft_strjoin(s, " ");
        free(temp);
        i ++;
    }
    if (n_flag)
        ft_printf("%s", s);
    else
        ft_printf("%s\n", s);
    free(s);
}
