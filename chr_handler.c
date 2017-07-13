/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 20:54:46 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/13 09:40:14 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** static char *utf8_to_char(int c)
**
** Converts a UTF-8 character into a format that is readable by the write system
** call.
** Conversion takes place using bit manipulation to strip the given integer into
** bytes based on the chart given in https://en.wikipedia.org/wiki/UTF-8
** If the given character is outside the valid Unicode range, then the character
** is replaced with U+FFFD aka the replacement character.
*/

static char	*utf8_to_char(int c)
{
	char *o;

	o = ft_strnew(4);
	o[0] = (c <= 0xFF) ? c & 0xFF : o[0];
	if (c <= 0x7FF && c > 0xFF)
	{
		o[0] = (0xC0 | O(c, 1));
		o[1] = (0x80 | (O(c, 0) & 0x3F));
	}
	else if (c <= 0xFFFF && c > 0xFF && (c < 0xD800 || c > 0xDFFF))
	{
		o[0] = (0xE0 | O(c, 2));
		o[1] = (0x80 | (O(c, 1) & 0x3F));
		o[2] = (0x80 | (O(c, 0) & 0x3F));
	}
	else if (c <= 0x10FFFF && c > 0xFF && (c < 0xD800 || c > 0xDFFF))
	{
		o[0] = (0xF0 | O(c, 3));
		o[1] = (0x80 | (O(c, 2) & 0x3F));
		o[2] = (0x80 | (O(c, 1) & 0x3F));
		o[3] = (0x80 | (O(c, 0) & 0x3F));
	}
	else if ((c > 0xD800 && c < 0xDFFF) || c > 0x10FFFF)
		o = ft_strdup("\xEF\xBF\xBD");
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

	t = (wpl[0] > 0) ? wpl[0] - 1 : 0;
	o = ft_strnew(1);
	o = (f[1] == 1) ? ft_strfill(&o, "0", t, 0) : ft_strfill(&o, " ", t, 0);
	if (f[1] != 2)
		ft_putstr(o);
	if (CHR(c) && wpl[2] != L)
		ft_putchar(va_arg(*args, int));
	else if (!CHR(c) && !W_CHR(c))
		write(1, &c, 1);
	else
	{
		w = utf8_to_char(va_arg(*args, wchar_t));
		t += (w[0] == '\0') ? write(1, "\0", 1) : ft_strlen(w);
		ft_putstr(w);
		ft_strdel(&w);
	}
	if (f[1] == 2)
		ft_putstr(o);
	ft_strdel(&o);
	return ((W_CHR(c) || (CHR(c) && wpl[2] == L)) ? t : ++t);
}

static char	*ft_wcstombs(wchar_t *str)
{
	int		i;
	char	*o;
	char	*temp;
	char	*w;

	i = 0;
	if (str == NULL)
		return (NULL);
	o = ft_strnew(1);
	while (str[i] != L'\0')
	{
		w = utf8_to_char(str[i++]);
		temp = ft_strjoin(o, w);
		ft_strdel(&w);
		ft_strdel(&o);
		o = ft_strdup(temp);
		ft_strdel(&temp);
	}
	return (o);
}

static int	str_handler(char c, va_list *args, int *f, int *wpl)
{
	int		t;
	char	*o;

	t = (wpl[0] > 0) ? wpl[0] : 0;
	if (STR(c) && wpl[2] != L)
		o = ft_strdup(va_arg(*args, char *));
	else
		o = ft_wcstombs(va_arg(*args, wchar_t *));
	if (o == NULL && f[1] == 0)
	{
		ft_putstr("(null)");
		return (ft_strlen("(null)"));
	}
	else if (o == NULL)
		o = ft_strnew(1);
	if (wpl[1] > 0 && (W_STR(c) || wpl[2] == L) && wpl[1] % 4 == 0)
		wpl[1]--;
	o = (wpl[1] != -1) ? ft_strsub(o, 0, wpl[1]) : o;
	o = (f[1] == 1) ? ft_strfill(&o, "0", t, 0) : o;
	o = (f[1] == 2) ? ft_strfill(&o, " ", t, 1) : ft_strfill(&o, " ", t, 0);
	t = ft_strlen(o);
	ft_putstr(o);
	ft_strdel(&o);
	return (t);
}

int			chr_handler(char c, va_list *args, int *flags, int *wpl)
{
	if (!STR(c) && !W_STR(c))
		return (c_handler(c, args, flags, wpl));
	if (STR(c) || W_STR(c))
		return (str_handler(c, args, flags, wpl));
	return (0);
}
