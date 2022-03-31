/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 07:45:23 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/30 07:45:23 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append(t_list *token, int ret)
{
	if (((char *)token->content)[ret] == '>'
		&& ((char *)token->content)[ret + 1] == '>')
		return (1);
	else
		return (0);
}

void	redir(t_list *token, int ret, t_cmd *cmd)
{
	if (((char *)token->content)[ret] == '>')
		cmd->std_out = REDIRECT;
	else
		cmd->std_in = REDIRECT;
}
