/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:43:28 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:04:43 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		ft_putstr_fd("mini$hell37: pwd:", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
