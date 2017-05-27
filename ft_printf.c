/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:57:26 by bpuschel          #+#    #+#             */
/*   Updated: 2017/05/26 15:10:26 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int print_handler(char *fmt, va_list args, int i)
{
	
}

int	ft_printf(char *fmt, ...)
{
	va_list args;
	int i;
	int tot;

	i = -1;
	tot = 0;
	va_start(args, fmt);
	while (fmt[++i] != '\0')
	{
		if (fmt[i] == '%')
			tot += print_handler(fmt, args, i);
		else
			write(1, &fmt[i], 1);
	}
	va_end(args);
	return (i + tot - 1);
}
