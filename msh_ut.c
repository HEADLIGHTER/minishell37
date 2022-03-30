#include "minishell.h"

int	is_builtin(char *token)
{
	if (token == NULL)
		return (0);
	if (!ft_strncmp("exit", token, 5))
		return (1);
	if (!ft_strncmp("cd", token, 3))
		return (1);
	else if (!ft_strncmp("echo", token, 5))
		return (1);
	else if (!ft_strncmp("env", token, 4))
		return (1);
	else if (!ft_strncmp("pwd", token, 4))
		return (1);
	else if (!ft_strncmp("export", token, 7))
		return (1);
	else if (!ft_strncmp("unset", token, 6))
		return (1);
	return (0);
}

int	check_input(char *input)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '|')
			dif = 1;
		if (input[i] == '|')
		{
			if (dif == 0)
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}
