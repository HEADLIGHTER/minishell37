/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:30:05 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 20:51:08 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_var_declarat(char *str)
{
	size_t	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	if (str[i] != '\0')
	{
		if (str[i] != '=' && str[i + 1] != '\0')
			return (0);
		i++;
		while (ft_isalnum(str[i]) || ft_isinset(str[i], "_-:./;"))
			++i;
		if (str[i])
			return (0);
	}
	return (1);
}

void	mas3(t_list *tkn)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(tkn->content, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
}
