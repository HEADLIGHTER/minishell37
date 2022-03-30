/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils37.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 03:55:47 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/30 03:55:47 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getenv_check(t_env *env, t_list *tkn)
{
	t_env	*tmp;

	tmp = get_env(env, tkn->content);
	if (tmp)
		return (1);
	return (0);
}

void	no_path(t_cmd *cmd, t_shell *sh)
{
	struct stat	buf;

	if (stat(cmd->token->content, &buf) == 0 && S_ISDIR(buf.st_mode))
		built_in_cd(sh->env, cmd->token);
	else
	{
		write(2, "mini$hell37: ", 13);
		write(2, cmd->token->content, ft_strlen(cmd->token->content));
		write(2, ": command not found\n", 20);
		sh->last_exit = 127;
	}
}

t_list	*f_in_out(t_cmd *cmd, int std_fd)
{
	if (std_fd == STDIN_FILENO)
		return (cmd->file_in);
	else
		return (cmd->file_out);
}

void	f_copy_in_out(t_cmd *cmd, int std_fd)
{
	if (std_fd == STDIN_FILENO)
		cmd->fd_copy_in = dup(std_fd);
	else
		cmd->fd_copy_out = dup(std_fd);
}