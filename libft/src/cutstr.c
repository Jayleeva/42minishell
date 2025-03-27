/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 11:02:53 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cutstr(char const *s, char c1, char c2)
{
	char	*result;
	int		len;
	int		j;
	int		end;
	int		start;

	if (s == NULL)
		return (NULL);
	start = strchri(s, c1);
	end = strchri(s, c2) - 1;
	if (start < 0 || end < 0)
		return (NULL);
	len = end - start + 1;
	result = ft_calloc(len, sizeof(char));
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
