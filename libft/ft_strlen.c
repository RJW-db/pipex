/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 13:51:38 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 15:47:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

// int main(void)
// {
//     char *c;

//     c = "52ewwefewf";
//     printf("%lu", ft_strlen(c));

//     return (0);
// }