#include <string.h>

void	*ft_memset(void *srs, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	j;

	str = (unsigned char *)srs;
	j = (unsigned char)c;
	i = 0;
	while (n > i)
	{
		str[i] = j;
		i++;
	}
	return (str);
}
