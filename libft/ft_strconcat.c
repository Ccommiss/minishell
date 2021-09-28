
#include "libft.h"

char	*ft_strconcat(char *s1, char *s2, int size)
{
	char		*concat;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!ft_malloc_char_pointer(size + 1, &concat))
		return (NULL);
	if (s1)
		while (s1[i])
			*concat++ = s1[i++];
	if (s2)
		while (s2[j])
			*concat++ = s2[j++];
	*(concat) = '\0';
	return (concat - ft_strlen(s1) - ft_strlen(s2));
}
