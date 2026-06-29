/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_heredoc_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 00:24:53 by rjw           #+#    #+#                 */
/*   Updated: 2024/03/12 16:35:40 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_printf.h"
#include "pipex.h"

static short	buff_write(int fd, char *buff, char *gnl, short i)
{
	while (*gnl != '\0')
	{
		buff[i] = *gnl;
		if (i == BUFF_SIZE - 1)
		{
			writing(fd, buff, BUFF_SIZE);
			i = -1;
		}
		++i;
		++gnl;
	}
	return (i);
}

static void	find_delimiter(char *limiter, int fd)
{
	const size_t	limiter_len = ft_strlen(limiter);
	short			i;
	char			*gnl;
	char			buff[BUFF_SIZE];

	i = 0;
	while (1)
	{
		writing(STDOUT_FILENO, "heredoc> ", 9);
		gnl = get_next_line(STDIN_FILENO);
		if (gnl == NULL || (ft_strncmp(gnl, limiter, limiter_len) == 0
				&& gnl[limiter_len] == '\n'))
		{
			writing(fd, buff, (size_t)i);
			break ;
		}
		i = buff_write(fd, buff, gnl, i);
		free(gnl);
	}
	if (gnl != NULL)
	{
		free(gnl);
	}
}

//	- Using BUFF_SIZE to minimize the use of the write call.
//	- Moving the arguments of bonus one step back so the function pipex()
//	can be reused
bool	here_document(int *argc, char ***argv)
{
	int		fd;
	short	i;

	fd = open(".tmp.txt", O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0777);
	if (fd == -1)
	{
		ft_dprintf(2, "zsh: %s: .tmp.txt\n", strerror(errno));
		return (false);
	}
	find_delimiter((*argv)[2], fd);
	if (close(fd) == -1)
	{
		perror("close(fd)");
		return (false);
	}
	(*argv)[0] = "0";
	(*argv)[1] = ".tmp.txt";
	i = 2;
	while (*argc - 1 > i)
	{
		(*argv)[i] = (*argv)[i + 1];
		++i;
	}
	*argc -= 1;
	return (true);
}
