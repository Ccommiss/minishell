/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:18:51 by mpochard          #+#    #+#             */
/*   Updated: 2021/06/09 14:32:38 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_division(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_modulo(unsigned int n, int i)
{
	char	*base;

	base = "0123456789";
	if (n == 0)
		return (base[0 % 10]);
	while (i > 1)
	{
		n /= 10;
		i--;
	}
	return (base[n % 10]);
}

static int	n_inf(int *n, char **fi, int *count, int *i)
{
	*count = (ft_division(*n));
	*fi = malloc(sizeof(char) *(*count) + 2);
	if (!(fi))
		return (-1);
	*fi[*i++] = '-';
	return (0);
}

char	*ft_itoa(int n)
{
	char			*fi;
	int				i;
	unsigned int	nb;
	int				count;

	i = 0;
	if (n < 0)
	{
		n = -n;
		if ((n_inf(&n, &fi, &count, &i)) == -1)
			return (0);
	}
	else
	{
		count = (ft_division(n));
		fi = malloc(sizeof(char) * (count + 1));
		if (!(fi))
			return (0);
	}
	nb = n;
	while ((count))
		fi[i++] = ft_modulo(nb, count--);
	fi[i] = '\0';
	return (fi);
}
