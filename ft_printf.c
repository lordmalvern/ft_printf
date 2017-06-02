/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:57:26 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/01 16:49:13 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		*flag_handler(char *fmt, int *i)
{
	int *flags;

	flags = (int *)malloc(3 * sizeof(int));
	while (IS_FLAG(fmt[*i]))
	{
		if (fmt[*i] == '#')
			flags[0] = 1;
		if (fmt[*i] == '0' && flags[1] != 2)
			flags[1] = 1;
		if (fmt[*i] == '-')
			flags[1] = 2;
		if (fmt[*i] == ' ' && flags[2] != 2)
			flags[2] = 1;
		if (fmt[*i] == '+')
			flags[2] = 2;
		(*i)++;
	}
	return (flags);
}

static int		width_prec_handler(char *fmt, int *i)
{
	int j;

	j = *i;
	(*i)++;
	while (ft_isdigit(fmt[*i]))
		(*i)++;
	return (ft_atoi(ft_strsub(fmt, j, *i - j)));
}

static t_lmod	lmod_handler(char *fmt, int *i)
{
	if (fmt[*i] == 'h')
	{
		(*i)++;
		return ((fmt[*i] == 'h') ? HH : H);
	}
	else if (fmt[*i] == 'l')
	{
		(*i)++;
		return ((fmt[*i] == 'l') ? LL : L);
	}
	else if (fmt[*i] == 'j')
	{
		(*i)++;
		return (J);
	}
	else if (fmt[*i] == 'z')
	{
		(*i)++;
		return (Z);
	}
	else
		return (N);
}

/*
** static int print_handler(char *fmt, va_list *args, int i)
**
** Handles the flags and conversions given in the formatted string fmt.
** Internal variables set the flag conditions, field width, precision, and
** length modifier.
** flags[0] is set to 0 by default, 1 if there is a # flag.
** flags[1] is set to 0 for no padding, 1 for padding with zeroes, 2 for padding
** with spaces.
** flags[2] is set to 0 for default signs, 1 for blanks, 2 for both + and -
** width is set to 0 by default and is set to the field width if it exists.
** prec is set to 0 by default and is set to the precision if it exists.
** lmod is set to N by default and is set to the length modifier if it exists.
** j stores the index of the end of a number for atoi conversions.
** Returns number of characters written to stdout.
*/

static int		print_handler(char *fmt, va_list *args, int *i)
{
	int		*flags;
	int		*width_prec_lmod;
	t_lmod	lmod;

	flags = flag_handler(fmt, i);
	width_prec_lmod = (int *)malloc(3 * sizeof(int));
	width_prec_lmod[0] = (ft_isdigit(fmt[*i])) ? width_prec_handler(fmt, i) : 0;
	width_prec_lmod[1] = (fmt[*i] == '.') ? width_prec_handler(fmt, i) : 0;
	if (width_prec_lmod[1] != 0 && flags[1] == 1)
		flags[1] = 0;
	lmod = (IS_LMOD(fmt[*i])) ? lmod_handler(fmt, i) : N;
	width_prec_lmod[2] = (int)lmod;
	if (IS_NUM(fmt[*i]) || IS_LON(fmt[*i]))
		return (num_handler(fmt[*i], args, &flags, &width_prec_lmod));
	if (IS_CHR(fmt[*i]))
		return (chr_handler(fmt[*i], args, &flags, &width_prec_lmod));
	if (fmt[(*i)] == '%')
		return ((int)write(1, "%", 1));
	return (0);
}

int				ft_printf(char *fmt, ...)
{
	va_list	args;
	int		i;
	int		tot;

	i = -1;
	tot = 0;
	va_start(args, fmt);
	while (fmt[++i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			tot += print_handler(fmt, &args, &i);
		}
		else
			tot += (int)write(1, &fmt[i], 1);
	}
	va_end(args);
	return (tot);
}
