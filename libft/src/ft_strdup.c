/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:00:43 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/27 12:29:21 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*copy;

	copy = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i ++;
	}
	copy[i] = '\0';
	return (copy);
}
