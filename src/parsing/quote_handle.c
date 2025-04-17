/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:39:04 by yishan            #+#    #+#             */
/*   Updated: 2025/04/14 14:47:01 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_data.h"
#include "../../libft/inc/libft.h"
/*checks if the current character is a quote (' or ")
If it’s a quote and not already inside a quote, it starts a new quote(' or ")
If it’s a quote and inside a matching quote, find ends of current quote.
If an index pointer is provided, it increments the index.*/
void	handle_quotes(char c, t_quote *quote)
{
	if (!quote->double_quote && !quote->single_quote)
	{
		if (c == '\'')
			quote->single_quote = TRUE;
		else if (c == '\"')
			quote->double_quote = TRUE;
		return ;
	}
	else if (quote->double_quote && c == '"')
	{
		quote->double_quote = FALSE;
		return ;
	}
	else if (quote->single_quote && c == '\'')
	{
		quote->single_quote = FALSE;
		return ;
	}
}

/*if the character is not a quote, increments the index.
After processing the entire string, it checks if any quote is still open.
If an open quote is found, it prints an error, sets the exit code, and returns 1.
If no open quotes are found, it returns 0.*/
int	check_open_quotes(t_data *data, char *input)
{
	int		i;

	data->quote.double_quote = FALSE;
	data->quote.single_quote = FALSE;
	i = 0;
	while (input && input[i])
	{
		handle_quotes(input[i], &data->quote);
		i++;
	}
	if (data->quote.double_quote || data->quote.single_quote)
	{
		print_error("open quote found\n");
		//add something that allows user to type in an input and ends only once they typed in the closing quote, then gives the correct error message: "minishell: $'%s\n%s': command not found" if no command properly given, or appropriate message if arg doesn't work with the command. Everytime user enters enter without closing the quote, adds a new \n on the %s. 
		data->exit_code = 1;
		return (0);
	}
	return (1);
}