/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 09:23:19 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:46:21 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digits(long n, long *place, int *sign, int *i)
{
	int size;

	*i = 0;
	*sign = (n < 0) ? 1 : 0;
	size = 1;
	*place = 1;
	while (n % (*place * 10) != n)
	{
		*place *= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*out;
	long	place;
	int		sign;
	int		i;
	long	num;

	num = n;
	out = ft_strnew(num_digits(num, &place, &sign, &i) + sign);
	if (out == NULL)
		return (NULL);
	if (sign)
	{
		num *= -1;
		out[i++] = '-';
	}
	while (place != 0)
	{
		out[i++] = (num / place) + 48;
		num -= (num / place) * place;
		place /= 10;
	}
	return (out);
}
