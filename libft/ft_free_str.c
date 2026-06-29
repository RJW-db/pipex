/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_str.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 14:38:16 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 17:42:07 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

void	*ft_free_str(char *str)
{
	if (str != NULL)
	{
		free(str);
	}
	return (NULL);
}
