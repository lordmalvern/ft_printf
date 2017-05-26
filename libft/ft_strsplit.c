/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:28:49 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:44:58 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*get_word(const char *str, size_t beg, size_t end)
{
	char	*out;

	out = ft_strnew(end - beg);
	if (out == NULL)
		return (NULL);
	return (ft_strncpy(out, (str - end) + beg, end - beg));
}

static char		*ft_strtok(const char *str, const char d, size_t *i, size_t s)
{
	size_t	beg;
	size_t	end;

	if (*i >= s)
		return (NULL);
	if (ft_strchr(str, d) == NULL)
	{
		*i = s;
		return (ft_strdup(str));
	}
	while (*str == d && *str != '\0')
	{
		*i = *i + 1;
		str++;
	}
	beg = *i;
	while (*str != d && *str != '\0')
	{
		*i = *i + 1;
		str++;
	}
	end = *i;
	return (get_word(str, beg, end));
}

static size_t	num_strings(const char *s, char d, size_t size)
{
	size_t	i;
	size_t	total;
	char	*temp;

	total = 0;
	i = 0;
	if (ft_strchr(s, d) == NULL && !ft_strequ(s, ""))
		return (1);
	while (s[i] != '\0' && i < size)
	{
		temp = ft_strtok((s + i), d, &i, size);
		if (temp != NULL && temp[0] != '\0')
			total++;
		ft_strdel(&temp);
	}
	return (total);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**out;
	size_t	i;
	size_t	j;
	size_t	total;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	total = num_strings(s, c, size);
	i = 0;
	j = 0;
	out = (char **)ft_memalloc((total + 1) * sizeof(char *));
	if (out == NULL)
		return (NULL);
	while (i < total)
		out[i++] = ft_strtok((s + j), c, &j, size);
	out[i] = NULL;
	return (out);
}
