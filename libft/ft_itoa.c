/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:11:38 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:11:38 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_sing(int n)
{
	size_t	nb;

	nb = n;
	if (n < 0)
		return (-nb);
	return (n);
}

size_t	ft_len(int n)
{
	size_t	l;
	size_t	nb;

	nb = ft_sing(n);
	l = 1;
	while (nb >= 10)
	{
		nb /= 10;
		l++;
	}
	return (l);
}

char	*ft_zero(int nb)
{
	char		*str;

	str = (char *)malloc(sizeof(char) * 1 + 1);
	if (!str)
		return (NULL);
	str[0] = nb + '0';
	str[1] = '\0';
	return (str);
}

char	*ft_finish(char *str, int n)
{
	if (n < 0)
		str[ft_len(n) + 1] = '\0';
	else
		str[ft_len(n)] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	number;

	number = ft_sing(n);
	if (number == 0)
		return (ft_zero(number));
	len = ft_len(n);
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	len--;
	if (n < 0)
		str[0] = '-';
	while (number > 0)
	{
		str[len--] = (number % 10) + '0';
		number = number / 10;
	}
	return (ft_finish(str, n));
}
