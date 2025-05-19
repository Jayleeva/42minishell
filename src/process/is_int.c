/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:12 by cyglardo          #+#    #+#             */
/*   Updated: 2025/05/19 13:34:39 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_bigger_than_int(int k, int j, char *s, char *num)
{
	j = k;
	while (s[j] == num[j - k] && num[j - k])
		j ++;
	if ((k == 0 && j == 9) || (k == 1 && j == 10))
	{
		if ((k == 0 && s[j] > '7') || (k == 1 && s[j] > '8'))
			return (1);
	}
	else
	{
		while (num[j - k])
		{
			if (s[j] > num[j - k])
				return (1);
			else if (s[j] < num[j - k])
				break ;
			else if (s[j] == num[j - k])
				j ++;
		}
	}
	return (0);
}
static int  count_nelem(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i ++;
    return (i);
}

static int	isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i ++;
	}
	return (1);
}

int	is_int(char *s)
{
	int		k;
	char	*num;
    int     nelem;
    int     i;

    if (!isnum(s))
    {
        return (0);
    }
	num = "214748364";
    i = 0;
    nelem = count_nelem(s);
	while (i < nelem)
	{
		k = 0;
		if (s[0] == '-')
			k = 1;
		if ((k == 0 && nelem > 10) || (k == 1 && nelem > 11))
			return (0);
		else if ((k == 0 && nelem == 10) || (k == 1 && nelem == 11))
			if (is_bigger_than_int(k, nelem, s, num))
				return (0);
		i ++;
	}
	return (1);
}