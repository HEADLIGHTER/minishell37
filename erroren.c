/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroren.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:01:12 by bbellatr          #+#    #+#             */
/*   Updated: 2022/03/29 13:01:12 by bbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_input(void)
{
	write(2, "mini$hell37: syntax error near unexpected token '|'\n", 52);
}

void	sig_quit(int sig)
{
	sig = 0;
}
