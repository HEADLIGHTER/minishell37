#include "libft.h"

size_t  find_char(char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}
