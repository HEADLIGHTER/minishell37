#include "minishell.h"

static char *replace(t_env *env, char *path, int flag)
{
	char    *new;
	t_env   *tmp;

	if (!(tmp = get_env(env, "HOME")))
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		if (flag)
			free(path);
		return (NULL);
	}
	new = ft_strjoin(tmp->value, path + 1);
	if (flag)
		free(path);
	return (new);
}

static int cd_path(t_env *env, char *path, int flag)
{
	char *pwd;
	t_env *tmp;
	t_env *tmp_old;

	if (path && path[0] == '~' && !(path = replace(env, path, flag)))
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (1);
	}
	if ((tmp = get_env(env, "PWD")) &&
		(tmp_old = get_env(env, "OLDPWD")))
		env_value(tmp_old, tmp->value);
	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell: getcwd:", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	if (tmp)
		env_value(tmp, pwd);
	free(pwd);
	return (0);
}

int built_in_cd(t_env *env, t_list *tkn)
{
	if (!tkn)
		return (cd_path(env, ft_strdup("~"), 1));
	return (cd_path(env, tkn->content, 0));
}