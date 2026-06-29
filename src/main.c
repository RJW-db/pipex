/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/18 16:18:13 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	exitcode;

	if (argc <= 4)
	{
		writing(STDERR_FILENO, "Not enough arguments\n", 21);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0
		&& here_document(&argc, &argv) == false)
	{
		return (EXIT_FAILURE);
	}
	exitcode = pipex(argc, argv, envp);
	if (WIFEXITED(exitcode) == true)
	{
		exitcode = WEXITSTATUS(exitcode);
	}
	unlink(".tmp.txt");
	return (exitcode);
}
