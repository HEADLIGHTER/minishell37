/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:15:55 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 21:18:08 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_no_quotes(char *s1, char *s2)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	j = 0;
	flag = -1;
	while (s1[++i])
	{
		if (flag == -1 && ft_isinset(s1[i], "\"\'"))
			flag = i;
		else if (flag != -1 && s1[flag] == s1[i])
			flag = -1;
		else
		{
			if (flag >= 0 && s1[flag] == '"' && s1[i + 1]
				&& ft_isinset(s1[i + 1], "$\"\\"))
				++i;
			s2[j++] = s1[i];
			s1[i] = '\0';
		}
	}
	s2[j] = '\0';
}

void	rm_quote(t_cmd *cmd)
{
	t_list	*tkn;
	char	*str;

	while (cmd)
	{
		tkn = cmd->token;
		while (tkn)
		{
			str = malloc(ft_strlen(tkn->content) + 1);
			if (tkn->content && str)
			{
				cpy_no_quotes(tkn->content, str);
				free(tkn->content);
				tkn->content = str;
			}
			tkn = tkn->next;
		}
		cmd = cmd->next;
	}
}

void	rm_redirect_pipe(t_cmd *cmd)
{
	t_list	*curr;
	t_list	*prev;

	while (cmd)
	{
		curr = cmd->token;
		prev = cmd->token;
		while (curr)
		{
			if (!curr->content || !((char *)curr->content)[0])
			{
				ft_lstrm(&cmd->token, prev, curr);
				curr = cmd->token;
			}
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}
		cmd = cmd->next;
	}
}
