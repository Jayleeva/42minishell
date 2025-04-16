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

	data->exit_code = 0;
    s = "";
    temp = NULL;
    cur_str = str;
    while (cur_str && cur_str->type == ARG)
    {
        if (cur_str->str[0] == '$' && cur_str->str[1] != '?') //ATTENTION  peut aussi être après l'espace!! à adapter
        {
            temp = get_env_value(data->env, ft_substr(cur_str->str, 1, strchri(cur_str->str, ' ') -1)); //si le token est une string composée de plusieurs mots et que l'un d'entre eux est une variable d'environnement, il faut les traiter séparément! sinon ne trouve pas et donc imprime vide.
            if (!temp)
                temp = ft_strdup("");
        }
        else
            temp = ft_strdup(cur_str->str);
        s = ft_strjoin(s, temp);
        if (cur_str->next && cur_str->next->type == ARG)
            s = ft_strjoin(s, " ");
        free(temp);
        cur_str = cur_str->next;
    }
    ft_printf("%s\n", s);
    free(s);
}
