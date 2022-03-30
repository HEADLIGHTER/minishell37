/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:33:30 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 00:33:30 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	retapp(t_cmd *cmd)
{
	if (cmd->append == 1)
		return (2);
	else
		return (1);
}

t_list	**r_in_out(t_cmd *cmd, t_list *token, int ret)
{
	if (((char *)token->content)[ret] == '>')
		return (&cmd->file_out);
	else
		return (&cmd->file_in);
}

void	parser_redirect(t_cmd *cmd, t_list *token, int ret)
{
	t_list	**file;

	cmd->append = append(token, ret);
	redir(token, ret, cmd);
	file = r_in_out(cmd, token, ret);
	if (!((char *)token->content)[ret + 1] ||
		(((char *)token->content)[ret + 1] == '>' &&
		!((char *)token->content)[ret + 2]))
	{
		ft_lstadd_back(file, ft_lstnew(ft_strdup(token->next->content)));
		ft_bzero(token->next->content + ret,
			ft_strlen(token->next->content + ret));
	}
	else
	{
		ret += retapp(cmd);
		if (((char *)token->content)[ret] == '>')
			++ret;
		ft_lstadd_back(file, ft_lstnew(ft_substr(token->content, ret,
					ft_strlen(token->content + ret))));
			ret -= retapp(cmd);
	}
	ft_bzero(token->content + ret, ft_strlen(token->content + ret));
}

void	parse_pipe(t_cmd *cmd, t_list *tkn, int i)
{
	t_cmd	*new;

	new = cmd_new();
	if (!((char *)tkn->content)[i + 1])
	{
		tkn_back(&new, ft_strdup(tkn->next->content));
		((char *)tkn->content)[i] = '\0';
		new->token->next = tkn->next->next;
		free(tkn->next->content);
		free(tkn->next);
	}
	else
	{
		tkn_back(&new, ft_substr(tkn->content, i + 1,
				ft_strlen(tkn->content + i + 1)));
		ft_bzero(tkn->content + i, ft_strlen(tkn->content + i));
		new->token->next = tkn->next;
	}
	tkn->next = NULL;
	new->next = cmd->next;
	cmd->next = new;
	new->std_in = PIPE;
	cmd->std_out = PIPE;
}

void	parser_special_char(t_cmd *cmd, char *s_char,
							void (*found)(t_cmd *, t_list *, int))
{
	int		i;
	t_list	*tkn;

	while (cmd)
	{
		i = 0;
		tkn = cmd->token;
		while (tkn && (i == 0 || ((char *)tkn->content)[i]))
		{
			i = escaped(tkn->content, i, s_char);
			if (!((char *)tkn->content)[i])
			{
				i = 0;
				tkn = tkn->next;
			}
			else if (ft_isinset(((char *)tkn->content)[i], s_char))
				(*found)(cmd, tkn, i);
		}
		cmd = cmd->next;
	}
}
