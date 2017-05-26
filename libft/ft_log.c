/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:53:52 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:01:38 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_log: calculates natural logarithm of number num
**
**	Uses Taylor Series to find natural logarithm iteratively.
**	Taylor Series for ln(x):
**	The sum of (((-1)^(n + 1))/n) * x^n with n going from 1 to infinity.
**	Returns approximation of ln(x).
*/

static double	ft_dblpow(double x, int n)
{
	if (n == 0)
		return (1);
	return (x * ft_dblpow(x, n - 1));
}

static double	to_sn(double x, int *digits)
{
	while (x >= 1)
	{
		*digits += 1;
		x /= 10;
	}
	return (x);
}

double			ft_log(double x)
{
	double	log;
	double	log10;
	int		digits;
	double	base;
	int		n;

	if (x == 0)
		return (-1.0 / 0.0);
	if (x < 0)
		return (0.0 / 0.0);
	n = 1;
	log = 0;
	log10 = 2.3025851;
	digits = 0;
	base = to_sn(x, &digits);
	while (n <= 2000)
	{
		if (n % 2 == 0)
			log += (-1 * ft_dblpow(base - 1, n)) / n;
		else
			log += ft_dblpow(base - 1, n) / n;
		n++;
	}
	log += (digits * log10);
	return (log);
}
