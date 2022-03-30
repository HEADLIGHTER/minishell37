/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:42:22 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/31 00:42:22 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replacce(char **s, int i, char *l_e)
{
	size_t	j;
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = ft_substr(*s, 0, i);
	if (!l_e)
		s2 = "";
	else
		s2 = l_e;
	j = 0;
	if (ft_isdigit((*s + i + 1)[j]))
		j++;
	else
		while (ft_isalnum((*s + i + 1)[j]) || *(*s + i + 1 + j) == '_')
			j++;
	s3 = ft_substr(*s + i + 1, j, ft_strlen(*s + i + 1 + j));
	free(*s);
	*s = ft_strjoin(s1, s2);
	s2 = *s;
	*s = ft_strjoin(*s, s3);
	free(s1);
	free(s2);
	free(s3);
}

static void	env_search(char **s, int i, t_env *env)
{
	int		j;
	char	*tmp;
	t_env	*tmp2;

	if (ft_isdigit(*(*s + i + 1)))
		j = 2;
	else
	{
		j = 1;
		while (ft_isalnum(*(*s + i + j)) || *(*s + i + j) == '_')
			j++;
	}
	tmp = ft_substr(*s, i + 1, --j);
	tmp2 = get_env(env, tmp);
	if (!tmp2)
		replacce(s, i, NULL);
	else
		replacce(s, i, tmp2->value);
	free(tmp);
}

void	env_logic(t_list *tkn, t_env *env, int i, int last_exit)
{
	char	*str;
	char	*tmp;

	str = tkn->content;
	if (str[i + 1] == '?')
	{
		str = (char *)tkn->content;
		tmp = ft_itoa(last_exit);
		tkn->content = ft_strjoin(tmp, str + 2);
		free(tmp);
		free(str);
	}
	else
		env_search((char **)&tkn->content, i, env);
}

void	parser_dollar(t_cmd *cmd, t_env *env, int last_exit)
{
	int		i;
	char	*str;
	t_list	*tkn;

	while (cmd)
	{
		tkn = cmd->token;
		i = 0;
		while (tkn)
		{
			str = (char *)tkn->content;
			i = escaped(tkn->content, i, "$");
			if (str[i])
			{
				if (!str[i + 1] || str[i + 1] == '$')
					i++;
				else if (str[i + 1] == '"')
				{
					ft_memmove(str + i, str + 1 + i,
						ft_strlen(str) - i - 1);
					str[ft_strlen(str) - 1] = '\0';
				}
				else
					env_logic(tkn, env, i, last_exit);
				continue ;
			}
			i = 0;
			tkn = tkn->next;
		}
		cmd = cmd->next;
	}
}
