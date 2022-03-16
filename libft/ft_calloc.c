#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;
	size_t	count;

	count = nmemb * size;
	str = (void *) malloc(count);
	if (!str)
		return (NULL);
	ft_bzero(str, count);
	return (str);
}
