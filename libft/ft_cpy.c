/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cpy.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 15:59:31 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 17:54:53 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

size_t	ft_cpy_str(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

size_t	ft_cpy_num(char *dst, const char *src, size_t num)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && num > 0)
	{
		dst[i] = src[i];
		i++;
		num--;
	}
	return (i);
}

size_t	ft_cpy_n_chr(char *dst, const char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = c;
		i++;
	}
	return (i);
}
