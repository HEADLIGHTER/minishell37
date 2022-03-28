#include "minishell.h"

int built_in_env(t_env *env)
{
	while (env)
	{
		if (env->set)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}