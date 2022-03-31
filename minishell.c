/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:39:08 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 19:17:28 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_free(t_shell *sh)
{
	write(1, "exit\n", 5);
	free_env(sh->env);
	return (1);
}

void	start_exec(t_shell *sh, char *input)
{
	sh->cmd = NULL;
	sh->line = input;
	sh->cmd = parsing(sh->line, sh->env, &sh->last_exit);
	free(sh->line);
	if (input != NULL && sh->cmd)
		executor(sh->cmd, sh);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*sh;

	sh = get_shell(INIT);
	sh->env = parser_env(envp);
	if (!ac && !av)
		return (0);
	while (1)
	{
		signal(SIGINT, sig_cmd);
		signal(SIGQUIT, SIG_IGN);
		input = readline("mini$hell37> ");
		add_history(input);
		if (input == NULL)
			return (print_free(sh));
		if (check_input(input) != 0)
			error_input();
		else
			start_exec(sh, input);
	}
}
