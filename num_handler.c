/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:53:19 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/09 13:43:57 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Each of the following functions contains integer array w as an argument.
**
** w is short for width, precision, and length modifier. The array contains
** data for each of these parameters.
** w[0] is field width. It can be any int.
** w[1] is precision. It can be any int.
** w[2] is length modifier. This needs to be directly cast to the enum t_lmod
** for comparison purposes.
**
** The other integer array flags (or f) is also important to understand.
** flags[0] is 1 if the # flag was present, 0 if not.
** flags[1] is 1 if the 0 flag was present, 2 if the - flag was, 0 if neither.
** The 0 flag can only be used if w[1] == 0
** flags[2] is 1 if the ' ' flag was present, 2 if the + flag was, 0 if neither.
** The flags in flags[2] can only be used on signed numbers (d or i)
*/

static char		*int_handler(char c, va_list *args, int *f, int *w)
{
	size_t		t;
	char		*o;
	char		*temp;
	intmax_t	n;

	n = s_con(c, args, w[2]);
	w[0] = ((n < 0 || f[2] > 0) && f[1] == 1 && w[1] == -1) ? w[0] - 1 : w[0];
	w[1] = (f[1] == 1 && w[1] == -1) ? w[0] : w[1];
	o = ft_itoa_base(n, 10, w[1]);
	if ((f[2] == 1 || f[2] == 2) && ft_strchr(o, '-') == NULL)
	{
		temp = (f[2] == 1) ? ft_strjoin(" ", o) : ft_strjoin("+", o);
		free(o);
		o = ft_strdup(temp);
		free(temp);
	}
	t = (w[0] >= 0) ? w[0] : 0;
	if (f[1] == 0 || (f[1] == 1 && w[1] != w[0]))
		o = ft_strfill(&o, " ", t, 0);
	o = (f[1] == 2) ? ft_strfill(&o, " ", t, 1) : o;
	return (o);
}

static char		*oct_handler(char c, va_list *args, int *f, int *w)
{
	size_t		t;
	char		*o;
	char		*p;
	uintmax_t	n;

	w[1] = (f[1] == 1 && w[1] == -1) ? w[0] : w[1];
	if (f[0] == 1 && w[1] - 1 > 0)
		w[1]--;
	n = u_con(c, args, w[2]);
	o = ft_utoa_base(n, 8, w[1]);
	t = (w[0] >= 0) ? w[0] : 0;
	p = (f[0] == 1 && (n > 0 || w[1] == 0)) ? ft_strjoin("0", o) : ft_strdup(o);
	free(o);
	o = ft_strdup(p);
	free(p);
	if (f[1] == 0 || (f[1] == 1 && w[1] != w[0]))
		o = ft_strfill(&o, " ", t, 0);
	o = (f[1] == 2) ? ft_strfill(&o, " ", t, 1) : o;
	return (o);
}

static char		*uint_handler(char c, va_list *args, int *f, int *w)
{
	size_t		t;
	char		*o;
	uintmax_t	n;

	w[1] = (f[1] == 1 && w[1] == -1) ? w[0] : w[1];
	n = u_con(c, args, w[2]);
	o = ft_utoa_base(n, 10, w[1]);
	t = (w[0] >= 0) ? w[0] : 0;
	if (f[1] == 0 || (f[1] == 1 && w[1] != w[0]))
		o = ft_strfill(&o, " ", t, 0);
	o = (f[1] == 2) ? ft_strfill(&o, " ", t, 1) : o;
	return (o);
}

static char		*hex_handler(char c, va_list *args, int *f, int *w)
{
	size_t		t;
	char		*o;
	char		*p;
	uintmax_t	n;

	w[1] = (f[1] == 1 && w[1] == -1) ? w[0] : w[1];
	w[1] -= ((f[0] == 1 || PTR(c)) && w[1] - 2 > 0 && w[1] == w[0]) ? 2 : 0;
	n = u_con(c, args, w[2]);
	o = ft_utoa_base(n, 16, w[1]);
	t = (w[0] >= 0) ? w[0] : 0;
	p = ((f[0] == 1 && n != 0) || PTR(c)) ? ft_strjoin("0X", o) : ft_strdup(o);
	free(o);
	o = ft_strdup(p);
	free(p);
	if (f[1] == 0 || (f[1] == 1 && w[1] != w[0]))
		o = ft_strfill(&o, " ", t, 0);
	o = (f[1] == 2) ? ft_strfill(&o, " ", t, 1) : o;
	if (HEX(c) || PTR(c))
	{
		p = ft_strmap(o, (char (*)(char))ft_tolower);
		free(o);
		o = ft_strdup(p);
		free(p);
	}
	return (o);
}

int				num_handler(char c, va_list *args, int *flags, int *w)
{
	char	*o;
	int		len;

	if (INT(c) || LON(c))
		o = int_handler(c, args, flags, w);
	else if (OCT(c) || L_OCT(c))
		o = oct_handler(c, args, flags, w);
	else if (U_INT(c) || U_LON(c))
		o = uint_handler(c, args, flags, w);
	else if (HEX(c) || C_HEX(c) || PTR(c))
		o = hex_handler(c, args, flags, w);
	else
		return (0);
	len = ft_strlen(o);
	ft_putstr(o);
	free(o);
	return (len);
}
