/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:46:48 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/24 14:09:40 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		len;
	char		*result;

	end = ft_strlen(s1);
	start = 0;
	while (is_in_set(set, s1[start]) == 1)
		start ++;
	if (start >= end)
		return (ft_strdup(""));
	while (is_in_set(set, s1[end -1]) == 1)
		end --;
	len = end - start;
	result = ft_substr(s1, start, len);
	return (result);
}
