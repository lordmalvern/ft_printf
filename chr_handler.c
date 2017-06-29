/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 20:54:46 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/29 14:17:37 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** static int utf8_to_char(int c)
**
** Converts a UTF-8 character into a format that is readable by the write system
** call.
** Conversion takes place using bit manipulation to strip the bytes to their
** significant bits based on the chart given in
** https://en.wikipedia.org/wiki/UTF-8
** Returns the integer representing the significant bits of the UTF-8 character
*/

static int	utf8_to_char(int c)
{
	unsigned char o[4];

	o[0] = c & 0xFF;
	o[1] = ((c >> 8) & 0xFF) & 0x3F;
	o[2] = ((c >> 16) & 0xFF) & 0x3F;
	o[3] = ((c >> 24) & 0xFF) & 0x3F;
	if ((o[0] & 0x80) == 0)
		return (o[0]);
	if ((o[0] & 0xE0) == 0xC0)
		return (((o[0] & 0x1F) << 6) | o[1]);
	else if ((o[0] & 0xF0) == 0xE0)
		return (((o[0] & 0x0F) << 12) | (o[1] << 6) | o[2]);
	else if ((o[0] & 0xF8) == 0xF0)
		return (((o[0] & 0x07) << 18) | (o[1] << 12) | (o[2] << 6) | o[3]);
	return (0);
}

/*
** Each of the following functions contains integer array wpl as an argument.
**
** wpl is short for width, precision, and length modifier. The array contains
** data for each of these parameters.
** wpl[0] is field width. It can be any int.
** wpl[1] is precision. It can be any int.
** wpl[2] is length modifier. This needs to be directly cast to the enum t_lmod
** for comparison purposes.
**
** The other integer array flags (or f) is also important to understand.
** flags[0] is 1 if the # flag was present, 0 if not.
** flags[1] is 1 if the 0 flag was present, 2 if the - flag was, 0 if neither.
** flags[2] is 1 if the ' ' flag was present, 2 if the + flag was, 0 if neither.
** The flags in flags[2] can only be used on signed numbers (d or i)
*/

static int	c_handler(char c, va_list *args, int *f, int *wpl)
{
	size_t	t;
	char	*o;
	int		w;

	t = (wpl[0] >= 0) ? wpl[0] : 0;
	if (t > 0)
		t--;
	o = ft_strnew(1);
	o = (f[1] == 1) ? ft_strfill(o, "0", t, 0) : ft_strfill(o, " ", t, 0);
	if (f[1] != 2)
		ft_putstr(o);
	if (CHR(c) && wpl[2] != (int)L)
		ft_putchar(va_arg(*args, int));
	else if (c == '%')
		write(1, "%", 1);
	else
	{
		w = utf8_to_char(va_arg(*args, wchar_t));
		write(1, &w, sizeof(int));
	}
	if (f[1] == 2)
		ft_putstr(o);
	ft_strdel(&o);
	return (t + 1);
}

static int	ft_putwstr(wchar_t *str, int precision)
{
	int len;
	int i;
	int w;

	len = 0;
	i = 0;
	while (str[len] != 0)
		len++;
	if (precision != 0 && precision < len)
	{
		while (i < precision)
		{
			w = utf8_to_char(str[i++]);
			write(1, &w, sizeof(int));
		}
		return (precision);
	}
	while (i < len)
	{
		w = utf8_to_char(str[i++]);
		write(1, &w, sizeof(int));
	}
	return (len);
}

static int	str_handler(char c, va_list *args, int *f, int *wpl)
{
	int		t;
	char	*o;

	t = (wpl[0] >= 0) ? wpl[0] : 0;
	if (STR(c) && wpl[2] != (int)L)
		o = ft_strdup(va_arg(*args, char *));
	else
		o = ft_strnew(1);
	if (o == NULL && wpl[2] != (int)L && !W_STR(c))
	{
		ft_putstr("(null)");
		return (ft_strlen("(null)"));
	}
	o = (wpl[1] != -1) ? ft_strsub(o, 0, wpl[1]) : o;
	o = (f[1] == 1) ? ft_strfill(o, "0", t, 0) : o;
	o = (f[1] == 2) ? ft_strfill(o, " ", t, 1) : ft_strfill(o, " ", t, 0);
	t = (STR(c) && wpl[2] != (int)L) ? ft_strlen(o) : t;
	if (f[1] != 2)
		ft_putstr(o);
	if (W_STR(c) || wpl[2] == (int)L)
		t += ft_putwstr(va_arg(*args, wchar_t *), wpl[1]);
	if (f[1] == 2)
		ft_putstr(o);
	ft_strdel(&o);
	return (t);
}

int			chr_handler(char c, va_list *args, int *flags, int *wpl)
{
	if (CHR(c) || W_CHR(c) || c == '%')
		return (c_handler(c, args, flags, wpl));
	if (STR(c) || W_STR(c))
		return (str_handler(c, args, flags, wpl));
	return (0);
}
