#include "libft.h"
#include <stdio.h>

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void *newptr;

	newptr = malloc(newsize);
	newptr = ft_bzero(newptr, newsize);
	newptr = ft_memcpy(newptr, ptr, cursize);
	printf("ici %s \n", (char *)newptr);
	free(ptr);
	return (newptr);
}


void	**ft_realloc_double_pointer(void **ptr, size_t cursize, size_t newsize)
{
	void	**newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}
