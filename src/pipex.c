/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/18 16:18:13 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pipex.h"

// - fd == -1 is in child process, because the other commands should still work.
static void	infile(char **argv, char **envp, int *pipes)
{
	int		fd;
	int		fd_check;

	if (pipe(pipes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY, 0666);
	fd_check = 0;
	if (fd == -1)
		fd_check = -1;
	else if (dup2(fd, STDIN_FILENO) == -1)
	{
		close_std(EXIT_SUCCESS, "dup2(fd, STDIN_FILENO)", strerror(errno));
		if (close(fd) == -1)
			perror("close(fd)");
		close_pipes(pipes, EXIT_FAILURE);
	}
	if (fd_check != -1 && close(fd) == -1)
	{
		close_std(EXIT_SUCCESS, "close(fd)", strerror(errno));
		close_pipes(pipes, EXIT_SUCCESS);
	}
	forking(argv[2], envp, pipes, fd_check);
}

static pid_t	forking_out(char *argv, char **envp)
{
	const pid_t	pid = fork();

	if (pid == -1)
	{
		close_std(EXIT_FAILURE, "zsh:", strerror(errno));
	}
	else if (pid == 0)
	{
		child_process(argv, envp);
	}
	if (close(STDIN_FILENO) == -1)
	{
		perror("close(STDIN_FILENO)");
	}
	if (close(STDOUT_FILENO) == -1)
	{
		perror("close(STDOUT_FILENO)");
	}
	return (pid);
}

static pid_t	outfile(int argc, char **argv, char **envp)
{
	int		fd_flags;
	int		fd;
	pid_t	pid;

	if (argv[0][0] == '0')
		fd_flags = O_CREAT | O_APPEND | O_WRONLY;
	else
		fd_flags = O_CREAT | O_TRUNC | O_WRONLY;
	fd = open(argv[argc - 1], fd_flags, 0777);
	if (fd == -1)
	{
		ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), argv[argc - 1]);
		close_std(EXIT_FAILURE, NULL, NULL);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		close_std(EXIT_FAILURE, "zsh:", strerror(errno));
	}
	if (close(fd) == -1)
	{
		perror("close(fd)");
	}
	pid = forking_out(argv[argc - 2], envp);
	return (pid);
}

int	pipex(int argc, char **argv, char **envp)
{
	int		pipes[2];
	int		i;
	pid_t	pid;
	int		status;

	infile(argv, envp, pipes);
	i = 1;
	while (i < argc - 4)
	{
		if (pipe(pipes) == -1)
		{
			close_std(EXIT_FAILURE, "pipe:", strerror(errno));
		}
		forking(argv[i + 2], envp, pipes, STDIN_FILENO);
		i++;
	}
	pid = outfile(argc, argv, envp);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
	{
		continue ;
	}
	return (status);
}
