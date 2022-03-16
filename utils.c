#include "minishell.h"

size_t  escaped(char *str, size_t i, char *sep)
{
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '"' && dq == 0 && sq == 0)
			++dq;
		else if (str[i] == '"' && dq == 1)
			--dq;
		if (str[i] == '\'' && sq == 0 && dq == 0)
			++sq;
		else if (str[i] == '\'' && sq == 1)
			--sq;
		if (ft_isinset(str[i], sep) && sq == 0
				&& (dq == 0 || ft_isinset('$', sep)))
			return (i);
		++i;
	}
	return (i);
}
