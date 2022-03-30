/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:48:45 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 00:48:45 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(t_env *env, char *key)
{
	size_t	i;

	if (!env || !key)
		return (NULL);
	i = find_char(key, '=');
	while (env)
	{
		if (ft_strlen(env->key) == i && !ft_strncmp(env->key, key, i))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*env_new(char *key, char *vaulue, int set)
{
	t_env	*new;

	new = malloc(sizeof (*new));
	if (!new)
	{
		write(2, "mini$hell37: malloc: ", 21);
		write(2, strerror(ENOMEM), ft_strlen(strerror(ENOMEM)));
		write(2, "\n", 1);
		return (NULL);
	}
	new->key = key;
	new->value = vaulue;
	new->set = set;
	new->next = NULL;
	return (new);
}

void	envp_back(t_env **old, t_env *new)
{
	t_env	*tmp;

	if (!old || !new)
		return ;
	if (!*old)
	{
		*old = new;
		new->next = NULL;
		return ;
	}
	tmp = *old;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

t_env	*parser_env(char **envp)
{
	size_t	i;
	size_t	ret;
	t_env	*env;
	t_env	*new;
	char	*tmp;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		ret = find_char(envp[i], '=');
		new = env_new(ft_substr(envp[i], 0, ret),
				ft_substr(envp[i], ret + 1, ft_strlen(envp[i] + ret + 1)), 1);
		envp_back(&env, new);
		++i;
	}
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
	return (env);
}

void	env_value(t_env *env, char *new_value)
{
	size_t	i;

	i = find_char(new_value, '=');
	free(env->value);
	if (new_value[i] == '=')
		env->value = ft_substr(new_value, i + 1, ft_strlen(new_value + i + 1));
	else
		env->value = ft_strdup(new_value);
}
