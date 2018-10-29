/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:10:24 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/10/29 16:10:38 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_unsigned(unsigned char **s1, unsigned char *s2,
		size_t l1, size_t l2)
{
	unsigned char	*temp;
	size_t			i;

	temp = ft_strnew_unsigned(l1);
	i = 0;
	while (i < l1)
	{
		temp[i] = s1[0][i];
		i++;
	}
	*s1 ? ft_strdel_unsigned(s1) : 0;
	*s1 = ft_strnew_unsigned(l1 + l2);
	i = 0;
	while (i < l1)
	{
		s1[0][i] = temp[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		s1[0][l1 + i] = s2[i];
		i++;
	}
	ft_strdel_unsigned(&temp);
}
