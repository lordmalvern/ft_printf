/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:14:55 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/08 19:05:31 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strfill(char *src, const char *fill, size_t len, int dir)
{
	char *out;
	char *temp;

	if (ft_strlen(src) >= len)
		return (src);
	out = ft_strdup(src);
	free(src);
	while (ft_strlen(out) < len)
	{
		if (dir == 0)
			temp = ft_strjoin(fill, out);
		else
			temp = ft_strjoin(out, fill);
		free(out);
		out = ft_strdup(temp);
		free(temp);
	}
	return (out);
}
