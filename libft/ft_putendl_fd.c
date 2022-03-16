#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	write(fd, s, i);
	write(fd, "\n", 1);
}
