/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:40 by yishan            #+#    #+#             */
/*   Updated: 2025/05/01 15:36:14 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

char    *extract_var_name(char *input, int length)
{
    char    *name;
    int     i;

    name = malloc(sizeof(char) * (length + 1));
    if (!name)
        return (NULL);
    i = 0;
    while (input[i] && i < length)
    {
        name[i] = input[i];
        i++;
    }
    name[i] = '\0';
    return (name);
}

char    *get_env_value(t_env *env, char *name)
{
    t_env   *var;

    var = find_var(env, name);
    if (!var)
        return (NULL);
    else
        return (var->value);
}

int get_var_name_length(char *input)
{
    int i;

    i = 0;
    while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
        i++;
    return (i);
}

int check_env_variable(char *input, int *i, t_data *data)
{
    int     l;
    char    *name;
    t_env   *var;
    
    if (input[*i + 1] == '?' || input[*i + 1] == '$')
        return (2);
    l = get_var_name_length(&input[*i + 1]);
    if (l == 0)
        return (0);
    name = ft_substr(input, *i + 1, l);
    var = find_var(data->env, name);
    if (var)
    {
        *i += l + 1;
        printf("EXISTS\n");
        return (1);
    }
    printf("DOESNT EXIST\n");
    return (0);
}
