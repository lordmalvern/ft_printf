/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:02:01 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:43:39 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*out;
	int		i;
	int		j;
	int		k;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	out = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (s1[j] != '\0')
		out[i++] = s1[j++];
	while (s2[k] != '\0')
		out[i++] = s2[k++];
	return (out);
}
