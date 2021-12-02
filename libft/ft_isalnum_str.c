/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:36:38 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/01 18:36:53 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
