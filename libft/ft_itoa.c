/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:18:51 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/28 17:56:34 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_division(unsigned int n)
{
	int i;

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

static int		ft_modulo(unsigned int n, int i)
{
	char *base;

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

char			*ft_itoa(int n)
{
	char			*fi;
	int				i;
	unsigned int	nb;
	int				count;

	i = 0;
	if (n < 0)
	{
		n = -n;
		count = (ft_division(n));
		if (!(fi = malloc(sizeof(char) * count + 2)))
			return (NULL);
		fi[i++] = '-';
	}
	else
	{
		count = (ft_division(n));
		if (!(fi = malloc(sizeof(char) * count + 1)))
			return (0);
	}
	nb = n;
	while ((count))
		fi[i++] = ft_modulo(nb, count--);
	fi[i] = '\0';
	return (fi);
}
