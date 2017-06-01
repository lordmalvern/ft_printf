/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:14:55 by bpuschel          #+#    #+#             */
/*   Updated: 2017/05/31 21:23:27 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *ft_strfill(char *src, const char *fill, size_t len, int dir)
{
	char *out;

	if (ft_strlen(src) >= len)
		return (src);
	while (ft_strlen(out) < len)
	{
		if (dir == 0)
			out = ft_strjoin(fill, out);
		else
			out = ft_strjoin(out, fill);
	}
	return (out);
}
