/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpochard <mpochard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:00:08 by mpochard          #+#    #+#             */
/*   Updated: 2021/12/07 14:03:06 by mpochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_realloc_tab(void **tab, int currsize, int newsize)
{
	int		i;
	void	**new_tab;

	i = 0;
	new_tab = malloc(newsize);
	while (i < currsize)
	{
		new_tab[i] = ft_strdup(tab[i], data->map_w, sizeof(char) * (x + 1));
		i++;
	}
	return (new_tab);
}
