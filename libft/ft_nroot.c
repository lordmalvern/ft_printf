/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nroot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:32:39 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 13:44:38 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_nroot.c: get the nth root of a number "base"
**
**	Utilizes iteration to approximate the nth root of a positive number.
**	Returns an integer.
*/

int	ft_nroot(int base, int n)
{
	int x;

	x = 1;
	if (n == 1 || base == 1)
		return (base);
	if (n == 0 || base == 0)
		return (0);
	while (ft_pow(x, n) < base)
		x++;
	if (ft_pow(x, n) > base)
		return (x - 1);
	return (x);
}
