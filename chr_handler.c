/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 20:54:46 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/02 19:16:31 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** static char *utf8_to_char(int c)
**
** Converts a UTF-8 character into a format that is readable by the write system
** call.
** Conversion takes place using bit manipulation to strip the bytes to their
** significant bits based on the chart given in
** https://en.wikipedia.org/wiki/UTF-8
** The resulting integer is then split into bytes. Each byte is converted to a
** hexadecimal string which is then joined together with a hexadecimal escape
** sequence, creating a string of hexadecimal bytes which the function returns.
** This string is interpreted by write as the Unicode character.
*/

static char	*utf8_to_char(int c)
{
	char *o;

	o = ft_strnew(4);
	if (c <= 0x7F)
		o[0] = c & 0x7F;
	else if (c <= 0x7FF)
	{
		o[0] = (0xC0 | O(c, 1));
		o[1] = (0x80 | (O(c, 0) & 0x3F));
	}
	else if (c <= 0xFFFF)
	{
		o[0] = (0xE0 | O(c, 2));
		o[1] = (0x80 | (O(c, 1) & 0x3F));
		o[2] = (0x80 | (O(c, 0) & 0x3F));
	}
	else if (c <= 0x1FFFFF)
	{
		o[0] = (0xF0 | O(c, 3));
		o[1] = (0x80 | (O(c, 2) & 0x3F));
		o[2] = (0x80 | (O(c, 1) & 0x3F));
		o[3] = (0x80 | (O(c, 0) & 0x3F));
	}
	return (o);
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
	char	*w;

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
		w = utf8_to_char(va_arg(*args, int));
		ft_putstr(w);
	}
	if (f[1] == 2)
		ft_putstr(o);
	ft_strdel(&o);
	return (t + 1);
}

static int	ft_putwstr(wchar_t *str, int precision)
{
	int		len;
	int		i;
	char	*w;

	len = 0;
	i = 0;
	while (str[len] != L'\0')
		len++;
	if (precision > 0 && precision < len)
	{
		while (i < precision)
		{
			w = utf8_to_char((int)str[i++]);
			ft_putstr(w);
		}
		return (precision);
	}
	while (i < len)
	{
		w = utf8_to_char((int)str[i++]);
		ft_putstr(w);
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
