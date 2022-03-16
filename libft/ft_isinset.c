#include "libft.h"

int		ft_isinset(int c, char *set)
{
	size_t i;

	i = 0;
	if (!c)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}
