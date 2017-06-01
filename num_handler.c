/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:53:19 by bpuschel          #+#    #+#             */
/*   Updated: 2017/05/31 21:22:54 by bpuschel         ###   ########.fr       */
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
** The 0 flag can only be used if wpl[1] == 0
** flags[2] is 1 if the ' ' flag was present, 2 if the + flag was, 0 if neither.
** The flags in flags[2] can only be used on signed numbers (d or i)
*/

static int int_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*out;

	*wpl[1] = (*wpl[1] == 0 && *f[1] == 1) ? *wpl[0] : *wpl[1];
	if ((t_lmod)*wpl[2] == L || LON(c))
		out = ft_itoa_base(va_arg(*args, long), 10, *wpl[1]);
	else if ((t_lmod)*wpl[2] == LL)
		out = ft_itoa_base(va_arg(*args, long long), 10, *wpl[1]);
	else if ((t_lmod)*wpl[2] == J)
		out = ft_itoa_base(va_arg(*args, intmax_t), 10, *wpl[1]);
	else if ((t_lmod)*wpl[2] == Z)
		out = ft_itoa_base(va_arg(*args, ssize_t), 10, *wpl[1]);
	else
		out = ft_itoa_base(va_arg(*args, int), 10, *wpl[1]);
	t = *wpl[0];
	out = (ft_strlen(out) < t && *f[1] == 0) ? ft_strfill(out, " ", t, 0) : out;
	if (ft_strlen(out) < t &&  *f[1] == 2)
		out = ft_strfill(out, " ", t, 1);
	if ((*f[2] == 1 || *f[2] == 2) && ft_strchr(out, '-') == NULL)
		out = (*f[2] == 1) ? ft_strjoin(" ", out) : ft_strjoin("+", out);
	ft_putstr(out);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (ft_strlen(out));
}

static int oct_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*out;

	*wpl[1] = (*wpl[1] == 0 && *f[1] == 1) ? *wpl[0] : *wpl[1];
	if ((t_lmod)*wpl[2] == L ||L_OCT(c))
		out = ft_itoa_base(va_arg(*args, unsigned long), 8, *wpl[1]);
	else if ((t_lmod)*wpl[2] == LL)
		out = ft_itoa_base(va_arg(*args, unsigned long long), 8, *wpl[1]);
	else if ((t_lmod)*wpl[2] == J)
		out = ft_itoa_base(va_arg(*args, uintmax_t), 8, *wpl[1]);
	else if ((t_lmod)*wpl[2] == Z)
		out = ft_itoa_base(va_arg(*args, size_t), 8, *wpl[1]);
	else
		out = ft_itoa_base(va_arg(*args, unsigned int), 8, *wpl[1]);
	t = *wpl[0];
	out = (ft_strlen(out) < t && *f[1] == 0) ? ft_strfill(out, " ", t, 0) : out;
	if (ft_strlen(out) < t &&  *f[1] == 2)
		out = ft_strfill(out, " ", t, 1);
	out = (*f[0] == 1) ? ft_strjoin("0", out) : out;
	ft_putstr(out);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (ft_strlen(out));
}

static int uint_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*out;

	*wpl[1] = (*wpl[1] == 0 && *f[1] == 1) ? *wpl[0] : *wpl[1];
	if ((t_lmod)*wpl[2] == L || U_LON(c))
		out = ft_itoa_base(va_arg(*args, unsigned long), 10, *wpl[1]);
	else if ((t_lmod)*wpl[2] == LL)
		out = ft_itoa_base(va_arg(*args, unsigned long long), 10, *wpl[1]);
	else if ((t_lmod)*wpl[2] == J)
		out = ft_itoa_base(va_arg(*args, uintmax_t), 10, *wpl[1]);
	else if ((t_lmod)*wpl[2] == Z)
		out = ft_itoa_base(va_arg(*args, size_t), 10, *wpl[1]);
	else
		out = ft_itoa_base(va_arg(*args, unsigned int), 10, *wpl[1]);
	t = *wpl[0];
	out = (ft_strlen(out) < t && *f[1] == 0) ? ft_strfill(out, " ", t, 0) : out;
	if (ft_strlen(out) < t &&  *f[1] == 2)
		out = ft_strfill(out, " ", t, 1);
	ft_putstr(out);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (ft_strlen(out));
}

static int hex_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*out;

	*wpl[1] = (*wpl[1] == 0 && *f[1] == 1) ? *wpl[0] : *wpl[1];
	if ((t_lmod)*wpl[2] == L)
		out = ft_itoa_base(va_arg(*args, unsigned long), 16, *wpl[1]);
	else if ((t_lmod)*wpl[2] == LL)
		out = ft_itoa_base(va_arg(*args, unsigned long long), 16, *wpl[1]);
	else if ((t_lmod)*wpl[2] == J)
		out = ft_itoa_base(va_arg(*args, uintmax_t), 16, *wpl[1]);
	else if ((t_lmod)*wpl[2] == Z)
		out = ft_itoa_base(va_arg(*args, size_t), 16, *wpl[1]);
	else if (PTR(c))
		out = ft_itoa_base((unsigned int)va_arg(*args, void *), 16, *wpl[1]);
	else
		out = ft_itoa_base(va_arg(*args, unsigned int), 16, *wpl[1]);
	t = *wpl[0];
	out = (ft_strlen(out) < t && *f[1] == 0) ? ft_strfill(out, " ", t, 0) : out;
	out = (ft_strlen(out) < t && *f[1] == 2) ? ft_strfill(out, " ", t, 1) : out;
	out = (*f[0] == 1 || PTR(c)) ? ft_strjoin("0X", out) : out;
	out = (HEX(c) || PTR(c)) ? ft_strmap(out, (char (*)(char))ft_tolower) : out;
	ft_putstr(out);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (ft_strlen(out));
}

int num_handler(char c, va_list *args, int **flags, int **wpl)
{
	if (INT(c) || LON(c))
		return (int_handler(c, args, flags, wpl));
	if (OCT(c) || L_OCT(c))
		return (oct_handler(c, args, flags, wpl));
	if (U_INT(c) || U_LON(c))
		return (uint_handler(c, args, flags, wpl));
	if (HEX(c) || C_HEX(c) || PTR(c))
		return (hex_handler(c, args, flags, wpl));
	return (0);
}
