/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:06:53 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 01:06:53 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_echo(t_list *tkn)
{
	int	flag;

	if (tkn && !ft_strncmp(tkn->content, "-n", 3))
	{
		flag = 1;
		tkn = tkn->next;
	}
	else
		flag = 0;
	while (tkn)
	{
		write(1, tkn->content, ft_strlen(tkn->content));
		tkn = tkn->next;
		if (tkn)
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
