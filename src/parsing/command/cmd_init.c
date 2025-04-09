/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yishan <yishan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:26:14 by yishan            #+#    #+#             */
/*   Updated: 2025/04/09 13:45:09 by yishan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

t_cmd	*cmd_create(int infile, int outfile, char **argv)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		return (NULL);
	if (!cmd_init(new_cmd, infile, outfile, argv))
	{
		cmd_clear (&new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

t_bool	cmd_init(t_cmd *cmd, int infile, int outfile, char **argv)
{
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->skip_cmd = FALSE;
	cmd->infile = infile;
	cmd->outfile = outfile;
	cmd->argv = argv;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (TRUE);
}
