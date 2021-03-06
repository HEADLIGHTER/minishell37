/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:45:05 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 20:25:33 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_argv(t_list *tkn)
{
	size_t	i;
	size_t	len;
	char	**argv;

	len = ft_lstsize(tkn);
	argv = malloc(sizeof(*argv) * (len + 1));
	if (!argv)
	{
		write(2, "mini$hell37: malloc: ", 21);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (NULL);
	}
	i = 0;
	while (i < len + 1 && tkn)
	{
		argv[i] = ft_strdup(tkn->content);
		if (!argv[i])
			break ;
		tkn = tkn->next;
		++i;
	}
	argv[i] = NULL;
	return (argv);
}

static char	**create_envp(t_env *env)
{
	int		i;
	size_t	len;
	char	**envp;

	envp = malloc(sizeof(*envp) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		envp[i] = malloc(len);
		if (!envp[i])
		{
			mall_err(strerror(errno));
			break ;
		}
		ft_bzero(envp[i], len);
		ft_strlcat(envp[i], env->key, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i++], env->value, len);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

static void	parent_code(t_shell *sh, t_cmd *cmd, pid_t pid)
{
	set_cmd_pipe(cmd);
	sig_child(pid);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(pid, &sh->last_exit, 0);
	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_quit);
	sh->last_exit = WEXITSTATUS(sh->last_exit);
}

static void	exec_cmd(t_shell *sh, char *path, char **av, char **ev)
{
	if (execve(path, av, ev) == -1)
	{
		write(2, "mini$hell37: execve: ", 21);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		free(path);
		free_split(av);
		free_split(ev);
		free_all(sh);
		exit(1);
	}
}

void	execve_fct(t_shell *sh, t_cmd *cmd, char *path)
{
	pid_t	pid;
	char	**ev;
	char	**av;

	pid = fork();
	if (pid == -1)
	{
		write(2, "mini$hell37: fork: ", 19);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else if (pid > 0)
		parent_code(sh, cmd, pid);
	else
	{
		set_read_write_pipe(cmd);
		av = create_argv(cmd->token);
		ev = create_envp(sh->env);
		signal(SIGINT, SIG_DFL);
		exec_cmd(sh, path, av, ev);
		exit(0);
	}
	free(path);
}
