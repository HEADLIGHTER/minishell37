/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:57:34 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/27 23:37:30 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	escaped(char *str, size_t i, char *sep)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '"' && dq == 0 && sq == 0)
			++dq;
		else if (str[i] == '"' && dq == 1)
			--dq;
		if (str[i] == '\'' && sq == 0 && dq == 0)
			++sq;
		else if (str[i] == '\'' && sq == 1)
			--sq;
		if (ft_isinset(str[i], sep) && sq == 0
			&& (dq == 0 || ft_isinset('$', sep)))
			return (i);
		++i;
	}
	return (i);
}


void	set_builtin_pipe(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
	{
		dup2(cmd->p_in[0], STDIN_FILENO);
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
	if (cmd->std_out == PIPE)
	{
		dup2(cmd->p_out[1], STDOUT_FILENO);
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
	}
}

void	handel_built_in(t_shell *sh, t_cmd *cmd, t_list *tkn)
{
	set_builtin_pipe(cmd);
	if (!ft_strncmp(tkn->content, "echo", 5))
		sh->last_exit = built_in_echo(tkn->next);
	else if (!ft_strncmp
			(tkn->content, "cd", 3))
		sh->last_exit = built_in_cd(sh->env, tkn->next);
	else if (!ft_strncmp(tkn->content, "pwd", 4))
		sh->last_exit = built_in_pwd();
	else if (!ft_strncmp(tkn->content, "export", 7))
		sh->last_exit = built_in_export(sh->env, tkn->next);
//	else if (!ft_strncmp(tkn->content, "unset", 6))
//		sh->last_exit = builtin_unset(&sh->env, tkn->next);
	else if (!ft_strncmp(tkn->content, "env", 4))
		sh->last_exit = built_in_env(sh->env);
//	else if (!ft_strncmp(tkn->content, "exit", 5))
//		builtin_exit(sh, tkn->next);
}
