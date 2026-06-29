/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 20:17:46 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/06 19:54:30 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "library.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>		// wait()
# include <string.h>		// strerror

# include <signal.h>
# include <errno.h>

void	forking(char *argv, char **envp, int *pipes, int fd);
void	child_process(char *argv, char **envp);
void	free_all(char *path_cmd, char **split);
int		close_pipes(int *pipes, int check);
void	close_std(int exit_code, char *err_comment, char *arg);
bool	here_document(int *argc, char ***argv);

#endif
