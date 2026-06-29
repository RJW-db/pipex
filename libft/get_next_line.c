/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 14:22:32 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 17:42:44 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

static size_t	str_len_newline(const char *str)
{
	size_t	n;

	if (!str)
		return (0);
	n = 0;
	while (str[n] && str[n] != '\n')
		n++;
	if (str[n] == '\n')
		return (n + 1);
	return (n);
}

static int	copy_check(char *dest, const char *src, bool *nl_check)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		if (dest[i] == '\n')
		{
			dest[++i] = '\0';
			*nl_check = true;
			return (i);
		}
		i++;
	}
	dest[i] = '\0';
	*nl_check = false;
	return (i);
}

static char	*str_merge(const char *nl, char *buf, bool *nl_check, int rd)
{
	char		*ret;
	size_t		len;

	buf[rd] = '\0';
	if (buf[0] == '\0')
		return ((char *)nl);
	len = str_len_newline(nl) + str_len_newline(buf);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (ft_free_str((char *)nl));
	len = copy_check(ret, nl, nl_check);
	len = copy_check(ret + len, buf, nl_check);
	while (*(buf + len) != '\0')
	{
		*buf = *(buf + len);
		buf++;
	}
	*buf = '\0';
	free((char *)nl);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buff[MAX_FDS][BUFFER_SIZE + 1];
	char		*new_line;
	int			rd;
	bool		nl_check;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = NULL;
	rd = BUFFER_SIZE;
	new_line = str_merge(new_line, buff[fd], &nl_check, BUFFER_SIZE);
	if (new_line && nl_check == true)
		return (new_line);
	while (rd == BUFFER_SIZE)
	{
		rd = read(fd, buff[fd], BUFFER_SIZE);
		if (rd >= 0)
			new_line = str_merge(new_line, buff[fd], &nl_check, rd);
		if (rd < 0 || !new_line || *new_line == '\0')
			return (ft_free_str(new_line));
		if (nl_check == true)
			return (new_line);
	}
	return (new_line);
}
