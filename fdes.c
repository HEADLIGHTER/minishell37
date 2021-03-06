/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:02:11 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 18:17:32 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_cmd *cmd, t_list *file, int std_fd)
{
	int	fd;

	fd = -1;
	if (std_fd == STDOUT_FILENO)
	{
		if (cmd->append)
			fd = open(file->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (std_fd == STDIN_FILENO)
		fd = open(file->content, O_RDONLY);
	return (fd);
}

static int	heredoc(char *name, t_cmd *cmd)
{
	char	*str;

	dup2(cmd->std_in, 0);
	str = readline("> ");
	if (!str)
		return (0);
	while (ft_strncmp(str, name, ft_strlen(str) + 1))
	{
		free(str);
		str = readline("> ");
		if (!str)
			return (0);
	}
	free(str);
	signal(SIGINT, SIG_DFL);
	return (0);
}

void	set_redirect_fd(t_cmd *cmd, int std_fd)
{
	int		fd;
	t_list	*file;

	file = f_in_out(cmd, std_fd);
	f_copy_in_out(cmd, std_fd);
	while (file)
	{
		if (cmd->herd)
		{
			heredoc(file->content, cmd);
			return ;
		}
		fd = open_file(cmd, file, std_fd);
		if (fd == -1)
			return (mas(file, cmd));
		file = file->next;
		if (file)
			close(fd);
	}
	dup2(fd, std_fd);
	close(fd);
}

void	open_fd(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
		cmd->fd_copy_in = dup(STDIN_FILENO);
	if (cmd->std_out == PIPE)
	{
		pipe(cmd->p_out);
		cmd->fd_copy_out = dup(STDOUT_FILENO);
	}
	if (cmd->std_in == REDIRECT)
		set_redirect_fd(cmd, STDIN_FILENO);
	if (cmd->std_out == REDIRECT)
		set_redirect_fd(cmd, STDOUT_FILENO);
	if (cmd->next && cmd->std_out != PIPE && cmd->next->std_in == PIPE)
	{
		pipe(cmd->p_out);
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
		close(cmd->p_out[1]);
	}
}

void	reset_fd(t_cmd *cmd)
{
	if (cmd->std_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_copy_out, STDOUT_FILENO);
		close(cmd->fd_copy_out);
	}
	if (cmd->std_in != STDIN_FILENO)
	{
		dup2(cmd->fd_copy_in, STDIN_FILENO);
		close(cmd->fd_copy_in);
	}
}
