/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 22:15:33 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:39:26 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lit_len;
	int		i;
	char	*b;

	lit_len = ft_strlen(little);
	ft_strlen(big);
	i = 0;
	b = (char *)big;
	if (lit_len == 0)
		return (b);
	while (i <= (int)(len - lit_len) && big[i] != '\0')
	{
		if (ft_strnequ(&big[i], little, lit_len))
			return (&b[i]);
		i++;
	}
	return (NULL);
}
