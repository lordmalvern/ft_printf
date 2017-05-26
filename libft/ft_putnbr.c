/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:58:04 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/10 19:16:51 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	long	place;

	place = 1;
	if (n == 0)
		ft_putchar('0');
	else if (n == 2147483647)
		ft_putstr("2147483647");
	else if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n *= -1;
		}
		while (n % (place * 10) != n)
			place *= 10;
		while (place != 0)
		{
			ft_putchar((n / place) + 48);
			n -= (n / place) * place;
			place /= 10;
		}
	}
}
