/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_child_processes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/04/08 19:08:09 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*path_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

// + 2, one for '/' and one for '\0'
static char	*cmd_path_loop(const char *path, char *command, int i, int j)
{
	const int	cmd_len = ft_strlen(command);
	char		*path_cmd;

	while (path[i] != '\0')
	{
		if (path[i] == ':')
		{
			path_cmd = (char *)malloc((i - j + cmd_len + 2) * sizeof(char));
			if (path_cmd == NULL)
			{
				return (NULL);
			}
			ft_strlcpy(path_cmd, &path[j], i - j + 1);
			path_cmd[i - j] = '/';
			ft_strlcpy(&path_cmd[i - j + 1], command, cmd_len + 1);
			if (access(path_cmd, F_OK) == 0)
			{
				return (path_cmd);
			}
			free(path_cmd);
			j = i + 1;
		}
		i++;
	}
	return (NULL);
}

static char	*cmd_path(const char *path, char *command)
{
	int		i;
	int		j;
	char	*command_check;

	j = 0;
	i = 0;
	command_check = cmd_path_loop(path, command, i, j);
	if (command_check == NULL && access(command, F_OK) == 0)
	{
		return (command);
	}
	return (command_check);
}

void	child_process(char *argv, char **envp)
{
	const char	*path = path_env(envp);
	char		*path_cmd;
	char		**split;

	if (path == NULL)
		close_std(EXIT_FAILURE, "\"PATH=\" Couldn't be found in envp", NULL);
	if (ft_strlen(argv) == 0)
	{
		close_std(EXIT_FAILURE, "argv had an empty string \"\"", NULL);
	}
	split = ft_split(argv, ' ');
	if (split == NULL)
	{
		close_std(EXIT_FAILURE, "malloc failed in ft_split", NULL);
	}
	path_cmd = cmd_path(path, split[0]);
	if (path_cmd == NULL)
	{
		free_all(path_cmd, split);
		close_std(127, "zsh: command not found:", argv);
	}
	execve(path_cmd, split, envp);
	free_all(path_cmd, split);
	close_std(EXIT_FAILURE, "execve:", strerror(errno));
}
