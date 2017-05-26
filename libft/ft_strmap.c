/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:09:50 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/10 22:09:31 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	int		i;
	int		len;
	char	*out;
	char	*src;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	out = ft_strnew(len);
	if (out == NULL)
		return (NULL);
	src = (char *)s;
	i = 0;
	while (i < len)
	{
		out[i] = f(src[i]);
		i++;
	}
	return (out);
}
