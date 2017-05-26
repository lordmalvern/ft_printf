/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:51:59 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:05:09 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	key;
	int		i;
	int		len;
	char	*src;

	key = c;
	i = 0;
	src = (char *)s;
	len = ft_strlen(src);
	while (i <= len)
	{
		if (src[i] == key)
			return (&src[i]);
		i++;
	}
	return (NULL);
}
