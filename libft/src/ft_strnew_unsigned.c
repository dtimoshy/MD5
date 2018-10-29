/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:19:55 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:19:56 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*ft_strnew_unsigned(size_t len)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *)malloc(len + 1);
	i = 0;
	while (i <= len)
	{
		res[i] = '\0';
		i++;
	}
	return (res);
}
