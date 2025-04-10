/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yisho <yisho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:15:43 by yishan            #+#    #+#             */
/*   Updated: 2025/04/10 15:06:04 by yisho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"

t_bool	print_error_token(t_token *token, t_data *data)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	if (!token->next || token->next == data->token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd("'\n", 2);
	return (FALSE);
}

//for debugging
void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != cmd)
	{
		printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ",
			tmp->skip_cmd, tmp->infile, tmp->outfile);
		print_tab(tmp->argv);
		printf("\n");
		tmp = tmp->next;
	}
	printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ", tmp->skip_cmd,
		tmp->infile, tmp->outfile);
	print_tab(tmp->argv);
	printf("\n");
}
