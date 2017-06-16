/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 10:30:20 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/15 18:41:04 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		base_length(uintmax_t value, unsigned int base)
{
	int len;

	len = 0;
	if (value == 0)
		return (len);
	while (value >= base)
	{
		value /= base;
		len++;
	}
	return (len);
}

static char		*to_str(uintmax_t val, int len, int i, unsigned int base)
{
	static char	*digits = "0123456789ABCDEF";
	char		*out;
	int			act_len;

	act_len = base_length(val, base);
	out = ft_strnew(len + 1);
	if (len > act_len)
	{
		while (--len > act_len)
			out[i++] = '0';
	}
	while (len >= 0 && val != 0)
		out[i++] = digits[(val / ft_pow(base, len--)) % base];
	out[i] = (val == 0) ? '0' : out[i];
	return (out);
}

char			*ft_utoa_base(uintmax_t value, int base, int precision)
{
	int	len;
	int	i;

	if (base < 2 || base > 16)
		return ("Invalid base");
	if (precision == 0 && value == 0)
		return (ft_strnew(1));
	len = base_length(value, base);
	if (len < precision)
		len = precision;
	i = 0;
	return (to_str(value, len, i, base));
}
