/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:09:26 by bpuschel          #+#    #+#             */
/*   Updated: 2017/05/26 18:01:00 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# define IS_FLAG(x) (x == '#' || x == '0' || x == '-' || x == '+' || x == ' ')
# define IS_LMOD(x) (x == 'h' || x == 'l' || x == 'j' || x == 'z')
/*
** The enumerator e_conv is used to store the different conversions as their
** type for greater readability in the code.
*/
typedef enum	e_conv
{
	STR = 's',
	W_STR = 'S',
	PTR = 'p',
	NUM = 'd',
	LON = 'D',
	INT = 'i',
	OCT = 'o',
	L_OCT = 'O',
	U_INT = 'u',
	U_LON = 'U',
	HEX = 'x',
	C_HEX = 'X',
	CHR = 'c',
	W_CHR = 'C'
}				t_conv;

int	ft_printf(char *fmt, ...);

#endif
