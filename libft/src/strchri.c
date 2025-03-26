/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchri.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/03/26 09:25:31 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	strchri(const char *s, int c)
{
	int	i;

	c = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i ++;
	}
	return (-1);
}
