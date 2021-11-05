#include "libft.h"

char	*ft_auto_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*s1;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		free((char *)s);
        return (NULL);
	}
	s1 = malloc(sizeof(char) * (len + 1));
	if (!(s1))
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && j < len)
		s1[j++] = s[i++];
	s1[j] = '\0';
    free((char *)s);
    s = NULL;
	return (s1);
}
