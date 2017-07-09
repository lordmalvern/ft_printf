/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:05:20 by bpuschel          #+#    #+#             */
/*   Updated: 2017/07/09 13:44:20 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	s_con(char c, va_list *args, int lmod)
{
	if (lmod == L || LON(c))
		return (va_arg(*args, long));
	if (lmod == HH)
		return ((char)va_arg(*args, int));
	if (lmod == H)
		return ((short)va_arg(*args, int));
	if (lmod == LL)
		return (va_arg(*args, long long));
	if (lmod == J)
		return (va_arg(*args, intmax_t));
	if (lmod == Z)
		return (va_arg(*args, ssize_t));
	return (va_arg(*args, int));
}

uintmax_t	u_con(char c, va_list *args, int lmod)
{
	if (lmod == L || U_LON(c) || L_OCT(c))
		return (va_arg(*args, unsigned long));
	if (lmod == HH)
		return ((unsigned char)va_arg(*args, unsigned int));
	if (lmod == H)
		return ((unsigned short)va_arg(*args, unsigned int));
	if (lmod == LL)
		return (va_arg(*args, unsigned long long));
	if (lmod == J)
		return (va_arg(*args, uintmax_t));
	if (lmod == Z)
		return (va_arg(*args, size_t));
	if (PTR(c))
		return ((unsigned long)va_arg(*args, void *));
	return (va_arg(*args, unsigned int));
}
