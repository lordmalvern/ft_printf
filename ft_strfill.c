/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:14:55 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/04 21:41:33 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strfill(char **src, const char *fill, size_t len, int dir)
{
	char	*out;
	char	*temp;
	size_t	l;

	l = ft_strlen(*src);
	if (l >= len || len <= 0)
		return (*src);
	out = ft_strdup(*src);
	ft_strdel(src);
	while (l < len)
	{
		if (dir == 0)
			temp = ft_strjoin(fill, out);
		else
			temp = ft_strjoin(out, fill);
		free(out);
		out = ft_strdup(temp);
		free(temp);
		l += ft_strlen(fill);
	}
	return (out);
}
