/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 02:10:19 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/27 03:30:44 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	char	*s1;
	int		i;
	int		sign;
	int		res;

	s1 = (char *)str;
	i = 0;
	res = 0;
	sign = 1;
	while ((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32)
		i++;
	if (s1[i] == '-' || s1[i] == '+')
	{
		if (s1[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (s1[i] >= '0' && s1[i] <= '9')
	{
		res = res * 10 + s1[i] - '0';
		i++;
	}
	res = res * sign;
	return (res);
}
