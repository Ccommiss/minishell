#include "libft.h"

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void *newptr;

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
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}
