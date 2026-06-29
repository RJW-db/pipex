/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 13:36:39 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 15:47:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*charb;

	charb = b;
	while (len--)
		*charb++ = (unsigned char)c;
	return (b);
}

// int	main(void)
// {
// 	char str[20] = "Hello, World!";
// 	printf("Before memset: %s\n", str);

// 	ft_memset(str, 'A', ft_strlen(str));
// 	printf("After memset: %s\n", str);

// 	return (0);
// }
