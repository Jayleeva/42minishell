/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/04/14 11:30:03 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

void    process_echo(t_token *str, t_data *data)
{
    char    *s;
    char    *temp;
    t_token *cur_str;
    char    **tab;
    int     i;
    int     n_flag;

	data->exit_code = 0;
    n_flag = 0;
    s = "";
    temp = NULL;
    cur_str = str;
    while (cur_str && cur_str->type == ARG)
    {
        if (!ft_strncmp(cur_str->str, "-n", 2))
        {
            cur_str = cur_str->next;
            n_flag = 1;
        }
        tab = ft_split(cur_str->str, ' '); //au cas où le token contient plusieurs args entre les mêmes guillemets
        if (!tab)
            return ;
        i = 0;
        while (tab[i])
        {
            if (tab[i][0] == '$' && tab[i][1] && tab[i][1] != '?')
            {
                temp = get_env_value(data->env, ft_substr(tab[i], 1, ft_strlen(tab[i]))); 
                if (!temp)
                    temp = ft_strdup("");
            }
            else
                temp = ft_strdup(tab[i]);
            s = ft_strjoin(s, temp);
            if (tab[i + 1] || (cur_str->next && cur_str->next->type == ARG))
                s = ft_strjoin(s, " ");
            free(temp);
            i ++;
        }
        free_tab(tab);
        cur_str = cur_str->next;
    }
    if (n_flag)
        ft_printf("%s", s);
    else
        ft_printf("%s\n", s);
    free(s);
}
