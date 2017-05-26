/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:15:46 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/10 20:31:40 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	long	place;

	place = 1;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n == 2147483647)
		ft_putstr_fd("2147483647", fd);
	else if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
		while (n % (place * 10) != n)
			place *= 10;
		while (place != 0)
		{
			ft_putchar_fd((n / place) + 48, fd);
			n -= (n / place) * place;
			place /= 10;
		}
	}
}
