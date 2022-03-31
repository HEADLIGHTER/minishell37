/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:07:49 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 18:40:02 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"minishell.h"

static int	is_valid_option(t_shell *sh, t_list *tkn)
{
	size_t	i;
	char	c;

	i = 0;
	while (((char *)tkn->content)[i])
	{
		c = ((char *)tkn->content)[i];
		if (!ft_isdigit(c) && !ft_isspace(c) && c != 43 && c != 45)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(tkn->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			sh->last_exit = 2;
			return (1);
		}
		++i;
	}
	if (tkn->next)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		sh->last_exit = 1;
		return (0);
	}
	sh->last_exit = (unsigned int)ft_atoi(tkn->content);
	return (1);
}

void	builtin_exit(t_shell *sh, t_list *tkn)
{
	int	exit_value;

	write(2, "exit\n", 5);
	if (tkn && !is_valid_option(sh, tkn))
		return ;
	exit_value = sh->last_exit;
	exit(exit_value);
}
