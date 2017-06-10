/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 20:54:46 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/10 14:38:19 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static char	*utf8_to_byte(int c)
{
	char *out;

	out = ft_strnew(4);
	out[0] = (c >> 24) & 0xFF;
	out[1] = (c >> 16) & 0xFF;
	out[2] = (c >> 8) & 0xFF;
	out[3] = c & 0xFF;
	return (out);
}

static int	c_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*o;

	t = (wpl[0][0] >= 0) ? wpl[0][0] : 0;
	if (t > 0)
		t--;
	o = ft_strnew(1);
	o = (f[0][1] == 1) ? ft_strfill(o, "0", t, 0) : ft_strfill(o, " ", t, 0);
	if (f[0][1] != 2)
		ft_putstr(o);
	if (CHR(c) && *wpl[2] != (int)L)
		ft_putchar(va_arg(*args, int));
	else if (c == '%')
		write(1, "%", 1);
	else
		write(1, utf8_to_byte(va_arg(*args, wchar_t)), 4);
	if (f[0][1] == 2)
		ft_putstr(o);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	ft_strdel(&o);
	return (t + 1);
}

static int	ft_putwstr(wchar_t *str, int precision)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	if (precision != 0 && precision < len)
	{
		write(1, str, precision * sizeof(wchar_t));
		return (precision);
	}
	write(1, str, len * sizeof(wchar_t));
	return (len);
}

static int	str_handler(char c, va_list *args, int **f, int **wpl)
{
	int		t;
	char	*o;

	t = (wpl[0][0] >= 0) ? wpl[0][0] : 0;
	if (STR(c) && wpl[0][2] != (int)L)
		o = ft_strdup(va_arg(*args, char *));
	else
		o = ft_strnew(1);
	o = (wpl[0][1] != -1) ? ft_strsub(o, 0, wpl[0][1]) : o;
	o = (f[0][1] == 0) ? ft_strfill(o, " ", t, 0) : o;
	o = (f[0][1] == 1) ? ft_strfill(o, "0", t, 0) : o;
	o = (f[0][1] == 2) ? ft_strfill(o, " ", t, 1) : o;
	t = (STR(c) && wpl[0][2] != (int)L) ? ft_strlen(o) : t;
	if (f[0][1] != 2)
		ft_putstr(o);
	if (W_STR(c) || wpl[0][2] == (int)L)
		t += ft_putwstr(va_arg(*args, wchar_t *), wpl[0][1]);
	if (f[0][1] == 2)
		ft_putstr(o);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	ft_strdel(&o);
	return (t);
}

int			chr_handler(char c, va_list *args, int **flags, int **wpl)
{
	if (CHR(c) || W_CHR(c) || c == '%')
		return (c_handler(c, args, flags, wpl));
	if (STR(c) || W_STR(c))
		return (str_handler(c, args, flags, wpl));
	return (0);
}
