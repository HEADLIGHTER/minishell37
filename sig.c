/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:10:51 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/30 23:10:51 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_cmd(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_main(int sig)
{
	t_shell	*sh;

	(void)sig;
	sh = get_shell(PULL);
	ft_putstr_fd("", 0);
	free(sh->line);
	sh->line = NULL;
}

void	sig_child(int sig)
{
	static int	pid;

	if (pid)
	{
		kill(pid, sig);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		else if (sig == SIGINT || sig == SIGQUIT)
			ft_putstr_fd("\n", 1);
		pid = 0;
	}
	else
		pid = sig;
}
