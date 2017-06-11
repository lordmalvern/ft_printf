/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:09:26 by bpuschel          #+#    #+#             */
/*   Updated: 2017/06/10 17:25:40 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# define IS_FLAG(x) (x == '#' || x == '0' || x == '-' || x == '+' || x == ' ')
# define IS_LMOD(x) (x == 'h' || x == 'l' || x == 'j' || x == 'z')
# define STR(x) (x == 's')
# define W_STR(x) (x == 'S')
# define PTR(x) (x == 'p')
# define INT(x) (x == 'd' || x == 'i')
# define LON(x) (x == 'D')
# define OCT(x) (x == 'o')
# define L_OCT(x) (x == 'O')
# define U_INT(x) (x == 'u')
# define U_LON(x) (x == 'U')
# define HEX(x) (x == 'x')
# define C_HEX(x) (x == 'X')
# define CHR(x) (x == 'c')
# define W_CHR(x) (x == 'C')
# define IS_NUM(x) (INT(x) || OCT(x) || U_INT(x) || HEX(x) || C_HEX(x))
# define IS_LON(x) (LON(x) || L_OCT(x) || U_LON(x) || PTR(x))
# define IS_CHR(x) (CHR(x) || STR(x) || W_CHR(x) || W_STR(x))

typedef enum	e_lmod
{
	HH,
	H,
	L,
	LL,
	J,
	Z,
	N
}				t_lmod;
int				ft_printf(char *fmt, ...);
char			*ft_itoa_base(intmax_t value, int base, int precision);
char			*ft_utoa_base(uintmax_t value, int base, int precision);
int				num_handler(char c, va_list *args, int *flags, int *wpl);
int				chr_handler(char c, va_list *args, int *flags, int *wpl);
char			*ft_strfill(char *src, const char *fill, size_t len, int dir);
intmax_t		s_con(char c, va_list *args, t_lmod lmod);
uintmax_t		u_con(char c, va_list *args, t_lmod lmod);

#endif
