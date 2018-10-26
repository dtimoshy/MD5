/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:43:42 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/01/04 15:31:26 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	size_t	i;
	char	*buff;

	length = 0;
	if (!s)
		return (NULL);
	while (s[length])
		length++;
	buff = (char *)malloc(sizeof(char*) * (length + 1));
	if (buff)
	{
		i = 0;
		while (i < length)
		{
			buff[i] = s[i];
			i++;
		}
		buff[i] = '\0';
	}
	return (buff);
}
