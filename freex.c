/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:20:21 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/30 21:20:21 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (-1);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (1);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		ft_lstclear(&cmd->token, &free);
		ft_lstclear(&cmd->file_in, &free);
		ft_lstclear(&cmd->file_out, &free);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

int	free_all(t_shell *sh)
{
	free_cmd(sh->cmd);
	free_env(sh->env);
	return (1);
}
