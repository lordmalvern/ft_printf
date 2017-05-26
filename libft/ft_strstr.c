/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 17:20:01 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 16:06:50 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	lit_len;
	int		i;
	char	*b;

	lit_len = ft_strlen(little);
	i = 0;
	b = (char *)big;
	if (lit_len == 0)
		return (b);
	while (big[i] != '\0')
	{
		if (ft_strnequ(&big[i], little, lit_len))
			return (&b[i]);
		i++;
	}
	return (NULL);
}
