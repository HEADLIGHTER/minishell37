/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:10:44 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:10:44 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	l;
	size_t	l1;
	size_t	l2;

	i = 0;
	l1 = 0;
	l2 = 0;
	while (dst[l1] && l1 <= n)
		l1++;
	l = l1;
	while (src[l2])
		l2++;
	if (l1 > n || n == 0)
		return (l2 + n);
	while (l < n - 1 && src[i])
	{
		dst[l] = src[i];
		l++;
		i++;
	}
	dst[l] = '\0';
	return (l1 + l2);
}
