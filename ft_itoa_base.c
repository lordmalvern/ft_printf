/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:05:14 by bpuschel          #+#    #+#             */
/*   Updated: 2017/05/31 21:12:08 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static int		base_length(intmax_t value, int base)
{
	int len;

	len = 0;
	if (value == 0)
		return (len);
	if (value < 0)
		value *= -1;
	while (value >= base)
	{
		value /= base;
		len++;
	}
	return (len);
}

static intmax_t	ft_lpow(intmax_t base, int pow)
{
	if (pow == 0)
		return (1);
	return (base * ft_lpow(base, pow - 1));
}

static char		*to_str(intmax_t val, int len, int i, int base)
{
	char *digits;
	char *out;

	digits = "0123456789ABCDEF";
	if (val < 0)
	{
		val *= -1;
		if (base == 10)
		{
			out = (char *)malloc((len + 3) * sizeof(char));
			out[i++] = '-';
		}
		else
			out = (char *)malloc((len + 2) * sizeof(char));
	}
	else
		out = (char *)malloc((len + 2) * sizeof(char));
	while (len > base_length(val, base))
		out[i++] = '0';
	while (len >= 0)
		out[i++] = digits[(val / ft_lpow(base, len--)) % base];
	out[i] = '\0';
	return (out);
}

char			*ft_itoa_base(intmax_t value, int base, int precision)
{
	int	len;
	int	i;

	if (value == 0)
		return ("0");
	len = base_length(value, base);
	if (len < precision)
		len += precision;
	i = 0;
	return (to_str(value, len, i, base));
}
