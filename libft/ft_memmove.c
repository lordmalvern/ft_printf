/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:17:04 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:04:10 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	int				j;
	unsigned char	*d;
	unsigned char	*s;

	i = -1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst > src)
	{
		j = len;
		while (--j >= 0)
			d[j] = s[j];
	}
	else
	{
		while (++i < len)
			d[i] = s[i];
	}
	dst = d;
	return (dst);
}
