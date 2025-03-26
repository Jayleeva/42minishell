/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/26 09:25:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cutstr(char const *s, char c1, char *set)
{
	char	*result;
	int	len;
	int	j;
	int	end;
	int	start;

	if (s == NULL)
		return (NULL);
	start = strchri(s, c1);
	j = 0;
	while (set[j])
	{
		end = strchri(s, set[j]) - 1;
		if (end < 0)
			j ++;
		else
			break;
	}
	if (start < 0 || end < 0)
		return (NULL);
	len = end - start + 1;
	result = (char *)malloc((len) * sizeof(char));
	if (result == NULL)
		return (NULL);
	j = 0;
	while (start < len)
	{
		result[j] = s[start];
		j ++;
		start ++;
	}
	result[j] = '\0';
	return (result);
}
