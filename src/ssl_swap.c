/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimoshy <dtimoshy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:50:07 by dtimoshy          #+#    #+#             */
/*   Updated: 2018/11/04 18:50:08 by dtimoshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	sha512_swap(
		unsigned long *vars, unsigned long temp1, unsigned long temp2)
{
	vars[7] = vars[6];
	vars[6] = vars[5];
	vars[5] = vars[4];
	vars[4] = vars[3] + temp1;
	vars[3] = vars[2];
	vars[2] = vars[1];
	vars[1] = vars[0];
	vars[0] = temp1 + temp2;
}

void	sha256_swap(
		unsigned int *vars, unsigned int temp1, unsigned int temp2)
{
	vars[7] = vars[6];
	vars[6] = vars[5];
	vars[5] = vars[4];
	vars[4] = vars[3] + temp1;
	vars[3] = vars[2];
	vars[2] = vars[1];
	vars[1] = vars[0];
	vars[0] = temp1 + temp2;
}

void	md5_swap(unsigned int *vars, unsigned rotleft)
{
	unsigned int temp;

	temp = vars[3];
	vars[3] = vars[2];
	vars[2] = vars[1];
	vars[1] = vars[1] + rotleft;
	vars[0] = temp;
}
