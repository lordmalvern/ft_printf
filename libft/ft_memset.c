/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:09:03 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:04:19 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	fill;
	unsigned char	*temp;
	size_t			i;

	i = 0;
	fill = c;
	temp = (unsigned char *)b;
	while (i < len)
	{
		temp[i] = fill;
		i++;
	}
	b = temp;
	return (b);
}
