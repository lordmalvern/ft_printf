/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:59:25 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:02:23 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprime(int num)
{
	int n;

	if (num == 0)
		return (0);
	if (num == 2 || num == 3 || num == 5)
		return (1);
	n = 2;
	while ((n * n <= num) && n <= 46340)
	{
		if (num % n == 0)
			return (0);
		n++;
	}
	return (1);
}
