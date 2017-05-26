/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 16:17:19 by bpuschel          #+#    #+#             */
/*   Updated: 2017/03/16 19:31:13 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	static int read_fd(int fd, char **buf, size_t size)
**
**	Clears the buffer or allocates memory to it if null and fills the buffer
**	with size b of content.
*/

static int	read_fd(int fd, char **buf, int *i)
{
	int bytes;

	if (buf[0] == NULL)
		buf[0] = (char *)malloc((BUFF_SIZE + 1) * sizeof(char));
	ft_bzero(buf[0], (BUFF_SIZE + 1) * sizeof(char));
	*i = -1;
	bytes = read(fd, buf[0], BUFF_SIZE);
	if (bytes < 0)
		ft_strdel(buf);
	return (bytes);
}

/*
**	int get_next_line (const int fd, char **line)
**
**	Gets the next line of input from file fd and outputs it to string line.
**
**	File gets read into a static buffer that is then parsed. New lines are
**	valid if ending in '\n' or the end of the file.
**	Returns 1 if there is still more for the program to read, 0 if at the end
**	of the file, and -1 if there is an error.
*/

int			get_next_line(const int fd, char **line)
{
	static char	*d[MAX_FD];
	int			b;
	int			i;
	int			j;
	int			f;

	if (fd < 0)
		return (-1);
	f = fd % MAX_FD;
	i = ft_charindex(d[f], '\n');
	j = -1;
	b = (d[f] == NULL || d[f][i + 1] == '\0') ? read_fd(fd, &d[f], &i) : 1;
	if (b <= 0)
		return (b);
	line[0] = ft_strnew(BUFF_SIZE);
	while ((line[0][++j] = d[f][++i]) != '\n' && b > 0)
	{
		b = (i == BUFF_SIZE - 1) ? read_fd(fd, &d[f], &i) : b;
		line[0] = (b > 0) ? ft_strextend(line, BUFF_SIZE) : line[0];
	}
	line[0][j] = '\0';
	if (i == BUFF_SIZE - 1)
		ft_strdel(&d[f]);
	return ((b < 0) ? b : 1);
}

/*
**	char	*ft_strextend(char *src, int len)
**
**	Creates a new string that is the string src plus len characters.
**	Frees the original string once copied to the new extended string.
**
**	Returns the extended string or NULL if any of the strings are empty.
*/

char		*ft_strextend(char **src, int len)
{
	char	*out;

	if (len <= 0)
		return (src[0]);
	out = ft_strnew(ft_strlen(src[0]) + len);
	if (out == NULL || src[0] == NULL)
		return (NULL);
	ft_strcpy(out, src[0]);
	ft_strdel(src);
	return (out);
}

/*
**	int ft_charindex(char *src, char c)
**
**	Returns the index of char c in string src or -1 if character isn't in src.
*/

int			ft_charindex(char *src, char c)
{
	int i;

	i = 0;
	if (src == NULL)
		return (-1);
	while (src[i] != '\0' && src[i] != c)
		i++;
	if (src[i] == c)
		src[i] = '|';
	return ((src[i] == '|' && i != BUFF_SIZE - 1) ? i : -1);
}
