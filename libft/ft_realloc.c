#include "libft.h"
#include <stdio.h>
#include <malloc/malloc.h>


void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	int i;
	void *newptr;

	i = 0;
	newptr = malloc(newsize);
	newptr = ft_bzero(newptr, newsize);
	newptr = memcpy(newptr, ptr, cursize);
	free(ptr);
	return (newptr);
}


void	**ft_realloc_double_pointer(void **ptr, size_t cursize, size_t newsize)
{
	void	**newptr;
	unsigned long int		i;

	i = 0;
	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	while (i < (cursize/sizeof(void *)))
	{
		if (ptr[i])
			newptr[i] = ft_strdup(ptr[i]); //faudrait le malloc de strlen
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (newptr);
}
