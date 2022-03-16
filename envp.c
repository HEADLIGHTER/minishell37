#include "minishell.h"

t_env *get_env(t_env *env, char *key)
{
	size_t i;

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

t_env *env_new(char *key, char *vaulue, int set)
{
	t_env *new;

	if (!(new = malloc(sizeof (*new))))
	{
		printf("minishell: malloc: %s\n", strerror(ENOMEM));
		return (NULL);
	}
	new->key = key;
	new->value = vaulue;
	new->set = set;
	new->next = NULL;
	return (new);
}

void envp_back(t_env **old, t_env *new)
{
	t_env *tmp;

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

t_env 	*parser_env(char **envp)
{
	size_t i;
	size_t ret;
	t_env *env;
	t_env *new;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		ret = find_char(envp[i], '=');
		new = env_new(ft_substr(envp[i] , '=', ret),
					  ft_substr(envp[i], ret + 1, ft_strlen(envp[i] + ret + 1)), 1);
		envp_back(&env, new);
		++i;
	}
	return (env);
}
