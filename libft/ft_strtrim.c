/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:22:19 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:45:36 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iswhtspc(char c)
{
	return ((c == ' ') || (c == '\n') || (c == '\t'));
}

char		*ft_strtrim(const char *s)
{
	char	*out;
	int		beg;
	int		end;
	int		i;

	if (s == NULL)
		return (NULL);
	end = ft_strlen(s) - 1;
	beg = 0;
	while (iswhtspc(s[beg]) && beg <= end / 2)
		beg++;
	while (iswhtspc(s[end]) && end >= beg)
		end--;
	i = 0;
	out = ft_strnew(end - beg + 1);
	if (out == NULL)
		return (NULL);
	if (beg == end)
		return (out);
	while (beg <= end)
		out[i++] = s[beg++];
	return (out);
}
