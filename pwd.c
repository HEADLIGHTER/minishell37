#include "minishell.h"

int built_in_pwd(void)
{
	char *buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		ft_putstr_fd("minishell: pwd:", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}