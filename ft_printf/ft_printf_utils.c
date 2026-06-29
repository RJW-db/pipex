/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 14:42:32 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 15:47:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

int	signed_decimal_base(char *str, int n)
{
	const char	store[12] = {0};
	const char	*base = "0123456789";
	char		*number;
	long		negative;

	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	negative = n;
	if (negative < 0)
		negative *= -1;
	number = &((char *)store)[11];
	while (negative != 0)
	{
		*(--number) = base[negative % 10];
		negative /= 10;
	}
	if (n < 0)
		*(--number) = '-';
	return (ft_cpy_str(str, number));
}
