/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:06:17 by bpuschel          #+#    #+#             */
/*   Updated: 2017/03/10 19:15:14 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *out;

	out = (char *)malloc(((size + 1) * sizeof(char)));
	if (out == NULL)
		return (NULL);
	ft_bzero(out, (size + 1) * sizeof(char));
	ft_strclr(out);
	return (out);
}
