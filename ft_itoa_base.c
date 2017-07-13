/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:05:14 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/13 09:47:26 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static char		*to_str(intmax_t val, int len, int i, int base)
{
	static char	*digits = "0123456789ABCDEF";
	char		*out;
	int			act_len;

	act_len = base_length(val, base);
	if (val < 0)
	{
		val *= -1;
		if (base == 10)
		{
			out = ft_strnew(len + 2);
			out[i++] = '-';
		}
		else
			out = ft_strnew(len + 1);
	}
	else
		out = ft_strnew(len + 1);
	if (len > act_len)
		while (--len > act_len)
			out[i++] = '0';
	while (len >= 0 && val != 0)
		out[i++] = digits[(val / (intmax_t)ft_pow(base, len--)) % base];
	out[i] = (val == 0) ? '0' : out[i];
	return (out);
}

char			*ft_itoa_base(intmax_t value, int base, int precision)
{
	int	len;
	int	i;

	if (base < 2 || base > 16)
		return (ft_strdup("Invalid base"));
	if (value < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (precision == 0 && value == 0)
		return (ft_strnew(1));
	len = base_length(value, base);
	if (len < precision)
		len = precision;
	i = 0;
	return (to_str(value, len, i, base));
}
