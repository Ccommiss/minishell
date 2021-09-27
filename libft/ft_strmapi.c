/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:29:43 by mpochard          #+#    #+#             */
/*   Updated: 2020/11/24 02:30:29 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				count;
	char			*fi;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	count = ft_strlen((char *)s);
	fi = malloc(sizeof(char) * (count + 1));
	if (!(fi))
		return (NULL);
	while (s[i])
	{
		fi[i] = f(i, s[i]);
		i++;
	}
	fi[i] = '\0';
	return (fi);
}
