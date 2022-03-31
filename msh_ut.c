/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 02:48:52 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 02:48:52 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	sh_ut(t_env *env, t_env *new, size_t i, char *tmp)
{
	if (!get_env(env, "SHLVL"))
	{
		new = env_new("SHLVL", "1", 1);
		envp_back(&env, new);
	}
	else
	{
		new = get_env(env, "SHLVL");
		i = ft_atoi(new->value) + 1;
		if (i > 1000)
		{
			ft_putstr_fd("bash: warning: shell level (", 2);
			ft_putstr_fd(new->value, 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			i = 1;
		}
		tmp = new->value;
		new->value = ft_itoa(i);
		free(tmp);
	}
}
