/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:10:28 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:10:28 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	f;

	j = 0;
	i = 0;
	f = 0;
	if (ft_strlen(s1) < ft_strlen(s2))
		return (0);
	if (ft_strlen(s2) == 0)
		return ((char *)s1 + i);
	while (s1[i] && i + ft_strlen(s2) <= n)
	{
		while (s1[i] == s2[j])
		{
			i++;
			j++;
			if (s2[j] == '\0')
				return ((char *)s1 + i - j);
		}
		j = 0;
		f++;
		i = f;
	}
	return (NULL);
}
