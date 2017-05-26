/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:43:39 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:06:34 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	key;
	int		i;
	int		last;
	int		len;
	char	*src;

	key = c;
	i = 0;
	last = -1;
	src = (char *)s;
	len = ft_strlen(src);
	while (i <= len)
	{
		if (src[i] == key)
			last = i;
		i++;
	}
	return ((last == -1) ? NULL : &src[last]);
}
