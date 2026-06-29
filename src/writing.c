/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/18 16:18:13 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	writing(int fd, char *str, size_t len)
{
	if (write(fd, str, len) == -1)
	{
		perror("write()");
	}
}
