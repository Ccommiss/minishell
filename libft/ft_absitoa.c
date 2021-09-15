/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absitoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:18:51 by mpochard          #+#    #+#             */
/*   Updated: 2021/01/15 17:09:17 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static long int		ft_abs(long int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static int			ft_eldivision(long int n)
{
	int				i;
	long long int	nb;

	i = 0;
	nb = ft_abs(n);
	if (n == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static int			ft_elmodulo(long int n, int i)
{
	char			*base;
	long long int	nb;

	base = "0123456789";
	if (n == 0)
		return (base[0 % 10]);
	nb = ft_abs(n);
	while (i > 1)
	{
		nb /= 10;
		i--;
	}
	return (base[nb % 10]);
}

char				*ft_absitoa(long int n)
{
	char			*fi;
	int				i;
	int				count;

	i = 0;
	count = (ft_eldivision(n));
	if (!(fi = malloc(sizeof(char) * count + 1)))
		return (0);
	while ((count))
		fi[i++] = ft_elmodulo(n, count--);
	fi[i] = '\0';
	return (fi);
}
