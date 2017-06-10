/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:53:19 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/10 14:44:02 by bpuschel         ###   ########.fr       */
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

static char		*int_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*o;
	char	*temp;
	int		lmod;

	wpl[0][1] = (wpl[0][1] == -1 && f[0][1] == 1) ? wpl[0][0] : wpl[0][1];
	lmod = wpl[0][2];
	o = ft_itoa_base(s_con(c, args, (t_lmod)lmod), 10, wpl[0][1]);
	t = (wpl[0][0] >= 0) ? wpl[0][0] : 0;
	o = (ft_strlen(o) < t && f[0][1] == 0) ? ft_strfill(o, " ", t, 0) : o;
	if (ft_strlen(o) < t && f[0][1] == 2)
		o = ft_strfill(o, " ", t, 1);
	if ((f[0][2] == 1 || f[0][2] == 2) && ft_strchr(o, '-') == NULL)
	{
		temp = (f[0][2] == 1) ? ft_strjoin(" ", o) : ft_strjoin("+", o);
		free(o);
		o = ft_strdup(temp);
		free(temp);
	}
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (o);
}

static char		*oct_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*o;
	char	*temp;
	int		lmod;

	wpl[0][1] = (wpl[0][1] == -1 && f[0][1] == 1) ? wpl[0][0] : wpl[0][1];
	lmod = wpl[0][2];
	o = ft_utoa_base(u_con(c, args, (t_lmod)lmod), 8, wpl[0][1]);
	t = (wpl[0][0] >= 0) ? wpl[0][0] : 0;
	o = (ft_strlen(o) < t && f[0][1] == 0) ? ft_strfill(o, " ", t, 0) : o;
	if (ft_strlen(o) < t && f[0][1] == 2)
		o = ft_strfill(o, " ", t, 1);
	temp = (f[0][0] == 1) ? ft_strjoin("0", o) : o;
	free(o);
	o = ft_strdup(temp);
	free(temp);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (o);
}

static char		*uint_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*o;
	int		lmod;

	wpl[0][1] = (wpl[0][1] == -1 && f[0][1] == 1) ? wpl[0][0] : wpl[0][1];
	lmod = wpl[0][2];
	o = ft_utoa_base(u_con(c, args, (t_lmod)lmod), 10, wpl[0][1]);
	t = (wpl[0][0] >= 0) ? wpl[0][0] : 0;
	o = (ft_strlen(o) < t && f[0][1] == 0) ? ft_strfill(o, " ", t, 0) : o;
	if (ft_strlen(o) < t && f[0][1] == 2)
		o = ft_strfill(o, " ", t, 1);
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (o);
}

static char		*hex_handler(char c, va_list *args, int **f, int **wpl)
{
	size_t	t;
	char	*o;
	char	*temp;
	int		lmod;

	wpl[0][1] = (wpl[0][1] == -1 && f[0][1] == 1) ? wpl[0][0] : wpl[0][1];
	lmod = wpl[0][2];
	o = ft_utoa_base(u_con(c, args, (t_lmod)lmod), 16, wpl[0][1]);
	t = (wpl[0][0] >= 0) ? wpl[0][0] : 0;
	o = (ft_strlen(o) < t && f[0][1] == 0) ? ft_strfill(o, " ", t, 0) : o;
	o = (ft_strlen(o) < t && f[0][1] == 2) ? ft_strfill(o, " ", t, 1) : o;
	temp = (f[0][0] == 1 || PTR(c)) ? ft_strjoin("0X", o) : o;
	free(o);
	o = ft_strdup(temp);
	free(temp);
	if (HEX(c) || PTR(c))
	{
		temp = ft_strmap(o, (char (*)(char))ft_tolower);
		free(o);
		o = ft_strdup(temp);
		free(temp);
	}
	ft_memdel((void **)f);
	ft_memdel((void **)wpl);
	return (o);
}

int				num_handler(char c, va_list *args, int **flags, int **wpl)
{
	char	*o;
	int		len;

	if (INT(c) || LON(c))
		o = int_handler(c, args, flags, wpl);
	else if (OCT(c) || L_OCT(c))
		o = oct_handler(c, args, flags, wpl);
	else if (U_INT(c) || U_LON(c))
		o = uint_handler(c, args, flags, wpl);
	else if (HEX(c) || C_HEX(c) || PTR(c))
		o = hex_handler(c, args, flags, wpl);
	else
		return (0);
	len = ft_strlen(o);
	ft_putstr(o);
	free(o);
	return (len);
}
