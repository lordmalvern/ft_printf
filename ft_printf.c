/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:57:26 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/02 21:32:03 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flag_handler(int **flags, char *fmt, int *i)
{
	while (IS_FLAG(fmt[*i]))
	{
		if (fmt[*i] == '#')
			(*flags)[0] = 1;
		if (fmt[*i] == '0' && (*flags)[1] != 2)
			(*flags)[1] = 1;
		if (fmt[*i] == '-')
			(*flags)[1] = 2;
		if (fmt[*i] == ' ' && (*flags)[2] != 2)
			(*flags)[2] = 1;
		if (fmt[*i] == '+')
			(*flags)[2] = 2;
		(*i)++;
	}
}

static int		wp_handler(char *fmt, int *i)
{
	int		j;
	int		out;
	char	*to_i;

	if (fmt[*i] == '.')
		(*i)++;
	j = *i;
	while (ft_isdigit(fmt[*i]))
		(*i)++;
	to_i = ft_strsub(fmt, j, *i - j);
	out = ft_atoi(to_i);
	ft_strdel(&to_i);
	return (out);
}

static t_lmod	lmod_handler(char *fmt, int *i)
{
	int j;

	j = 0;
	if (fmt[*i] == 'h')
	{
		if (fmt[++(*i)] == 'h')
			j = (*i)++;
		return ((j == *i - 1) ? HH : H);
	}
	else if (fmt[*i] == 'l')
	{
		if (fmt[++(*i)] == 'l')
			j = (*i)++;
		return ((j == *i - 1) ? LL : L);
	}
	else if (fmt[*i] == 'j' || fmt[*i] == 'z')
	{
		(*i)++;
		return ((fmt[*i - 1] == 'j') ? J : Z);
	}
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
	int		width_prec_lmod[3];
	int		out;
	t_lmod	lmod;

	flags = (int *)malloc(3 * sizeof(int));
	ft_bzero(flags, 3 * sizeof(int));
	ft_memset(width_prec_lmod, -1, 3 * sizeof(int));
	out = 0;
	while (IS_PRE(fmt[*i]) && fmt[*i] != '\0')
	{
		flag_handler(&flags, fmt, i);
		width_prec_lmod[0] = (ft_isdigit(fmt[*i])) ? wp_handler(fmt, i) : -1;
		width_prec_lmod[1] = (fmt[*i] == '.') ? wp_handler(fmt, i) : -1;
		if (width_prec_lmod[1] > 0 && flags[1] == 1)
			flags[1] = 0;
		lmod = (IS_LMOD(fmt[*i])) ? lmod_handler(fmt, i) : N;
		width_prec_lmod[2] = (int)lmod;
	}
	if (IS_NUM(fmt[*i]) || IS_LON(fmt[*i]))
		out = num_handler(fmt[(*i)++], args, flags, width_prec_lmod);
	else if (IS_CHR(fmt[*i]) || fmt[*i] == '%')
		out = chr_handler(fmt[(*i)++], args, flags, width_prec_lmod);
	free(flags);
	return (out);
}

int				ft_printf(char *fmt, ...)
{
	va_list	args;
	int		i;
	int		tot;

	i = 0;
	tot = 0;
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			if (fmt[i] != '\0')
				tot += print_handler(fmt, &args, &i);
		}
		else if (fmt[i] != '\0')
		{
			tot += (int)write(1, &fmt[i], 1);
			i++;
		}
	}
	va_end(args);
	return (tot);
}
