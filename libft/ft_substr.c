/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krnearin <krnearin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:10:16 by krnearin          #+#    #+#             */
/*   Updated: 2022/03/31 16:12:07 by krnearin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_coppy(char const *s, unsigned int start, size_t l)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(char) * l + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < l)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start || len <= 0)
		return (ft_strdup(""));
	l = len;
	if ((ft_strlen(s) - start) < len)
		l = ft_strlen(s) - start;
	return (ft_coppy(s, start, l));
}
