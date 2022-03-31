/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envworks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:28:22 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/30 23:28:22 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_value(t_env *env, char *new_value)
{
	size_t	i;

	i = find_char(new_value, '=');
	free(env->value);
	if (new_value[i] == '=')
		env->value = ft_substr(new_value, i + 1, ft_strlen(new_value + i + 1));
	else
		env->value = ft_strdup(new_value);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		++i;
		env = env->next;
	}
	return (i);
}

int	statcheck2(char *path)
{
	struct stat	buf;

	if (!stat(path, &buf) && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

int	statcheck(char *name)
{
	struct stat	buf;

	if (stat(name, &buf) == 0 && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

char	*get_bin(t_env *env, char *name)
{
	int			i;
	char		**split;
	char		*path;
	char		*s;

	if (statcheck(name))
		return (ft_strdup(name));
	env = get_env(env, "PATH");
	if (!env)
		return (NULL);
	i = -1;
	path = NULL;
	split = ft_split(env->value, ':');
	while (split && split[++i])
	{
		s = ft_strjoin(split[i], "/");
		path = ft_strjoin(s, name);
		free(s);
		if (statcheck2(path))
			break ;
		free(path);
		path = NULL;
	}
	free_split(split);
	return (path);
}
