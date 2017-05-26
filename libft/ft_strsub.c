/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 09:54:03 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:45:52 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t n)
{
	char			*out;
	unsigned int	end;
	int				i;

	if (s == NULL)
		return (NULL);
	out = ft_strnew(n);
	if (out == NULL)
		return (NULL);
	end = start + n;
	i = 0;
	while (start < end)
	{
		out[i] = s[start];
		start++;
		i++;
	}
	return (out);
}
