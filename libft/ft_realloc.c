#include "libft.h"

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	void	*newptr;

	if (!ptr)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memset(newptr, '.', newsize);
	ft_memcpy(newptr, ptr, cursize);
	if (cursize != 0)
		free(ptr);
	return (newptr);
}
