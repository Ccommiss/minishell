/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 02:30:55 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/03 14:03:07 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <errno.h>
char	*ft_strdup(const char *s)
{
	int		i;
	unsigned char	*s1;
	unsigned char	*fi;

	if (!s)
		return (NULL);
	printf ("YO en haut \n");
	s1 = (unsigned char *)s;
	fi = NULL;
	printf ("YO presaue en haut \n");

	i = 0;
	fi = (unsigned char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + 1));
	if (errno == ENOMEM)
		printf ("YAYAYA\n");
	printf ("YO ici apres le malloc \n");
	//printf ("fi %zu\n", malloc_usable_size(fi));
	printf ("strlen line = %zu \n", ft_strlen((char *)s1));
	if (!(fi))
	{
		printf ("la\n");
		exit (0);
		return (NULL);
	}
	while (s1[i])
	{
		//if (fi[i])
			fi[i] = s1[i];
		//else
		// {
		//if (i >= 4096)
		//printf ("ici %d\n", i);
		// 	exit (0);
		// }
		i++;
	}
	fi[i] = '\0';
	printf ("YO FIN\n");
	return ((char *)fi);
}
