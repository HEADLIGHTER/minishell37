#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	j;

	str = (unsigned char *)s;
	j = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == j)
			return ((void *)s + i);
		i++;
	}
	if (i == n)
	{
		return (NULL);
	}
	return (0);
}
