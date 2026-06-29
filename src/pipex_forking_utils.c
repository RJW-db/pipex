/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_forking_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/18 13:16:17 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pipex.h"

static void	parent(int *pipes)
{
	if (dup2(pipes[0], STDIN_FILENO) == -1)
	{
		close_std(EXIT_SUCCESS, "dup2:", strerror(errno));
		close_pipes(pipes, EXIT_FAILURE);
	}
	close_pipes(pipes, EXIT_SUCCESS);
}

//	The STDIN has already been set before entering this function,
//	it will be set to either the infile or read end of the pipe, e.g.
//	pipes[0]. In the child you will use the first STDIN and write to the
//	STDOUT (pipes[1]), while in the parent you set the STDIN to the
//	connection of this pipe (pipes[0]) 
void	forking(char *argv, char **envp, int *pipes, int fd)
{
	const pid_t	pid = fork();

	if (pid == -1)
	{
		close_std(EXIT_SUCCESS, "zsh:", strerror(errno));
		close_pipes(pipes, EXIT_FAILURE);
	}
	else if (pid > 0)
		parent(pipes);
	else
	{
		if (fd == -1)
		{
			ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), argv);
			close_pipes(pipes, EXIT_FAILURE);
		}
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
		{
			close_std(EXIT_SUCCESS, "dup2:", strerror(errno));
			close_pipes(pipes, EXIT_FAILURE);
		}
		close_pipes(pipes, EXIT_SUCCESS);
		child_process(argv, envp);
	}
}

void	free_all(char *path_cmd, char **split)
{
	short	i;

	if (path_cmd != NULL && split != NULL)
	{
		if (ft_strncmp(path_cmd, split[0], ft_strlen(path_cmd)) != 0)
		{
			free (path_cmd);
		}
	}
	if (split != NULL)
	{
		i = 0;
		while (split[i] != NULL)
		{
			free(split[i]);
			++i;
		}
		free (split);
	}
}

int	close_pipes(int *pipes, int check)
{
	int	err;

	err = 0;
	if (close(pipes[0]) == -1)
	{
		perror("close(pipes[0])");
		err = EXIT_FAILURE;
	}
	if (close(pipes[1]) == -1)
	{
		perror("close(pipes[1])");
		err = EXIT_FAILURE;
	}
	if (check == -1 || err == -1)
	{
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	close_std(int exit_code, char *err_comment, char *arg)
{
	if (err_comment != NULL && arg != NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s %s\n", err_comment, arg);
	}
	else if (err_comment != NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", err_comment);
	}
	if (close(STDIN_FILENO) == -1)
	{
		perror("close(STDIN_FILENO)");
	}
	if (close(STDOUT_FILENO) == -1)
	{
		perror("close(STDOUT_FILENO)");
	}
	if (exit_code != 0)
	{
		exit(exit_code);
	}
}
