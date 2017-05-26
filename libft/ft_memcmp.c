/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:01:26 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:03:48 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*left;
	unsigned char	*right;

	i = 0;
	left = (unsigned char *)s1;
	right = (unsigned char *)s2;
	while (i < n)
	{
		if (left[i] != right[i])
			return (left[i] - right[i]);
		i++;
	}
	return (0);
}
