/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:48:24 by yishan            #+#    #+#             */
/*   Updated: 2025/05/01 15:43:48 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linked_list.h"

void	array_clear(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	arr = NULL;
}

static void	free_all_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;

	if (cmd->infile != 0) //CYCY mod.: was >=3 before;
		close(cmd->infile);
	cmd->infile = 0; //CYCY mod.: was = -2 before;

	if (cmd->outfile != 1) //CYCY mod.: was >= 3 before;
		close(cmd->outfile);
	cmd->outfile = 1; //CYCY mod.: was = -2 before;

	if (cmd->argv)
	{
		array_clear(cmd->argv);
		cmd->argv = NULL;
	}
}

void	cmd_clear(t_cmd **cmd)
{
	t_cmd	*current;

	if (!cmd || !(*cmd))
		return ;
	while (*cmd)
	{
		current = *cmd;
		*cmd = (*cmd)->next;
		free_all_cmd(current);
		free(current);
	}
	*cmd = NULL;
}
