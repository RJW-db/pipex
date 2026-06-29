/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/23 15:21:31 by rjw           #+#    #+#                 */
/*   Updated: 2024/03/01 15:47:58 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

static char	*ft_str(int sign, int i, int n)
{
	char	*p;

	p = malloc((i + 1 + sign) * sizeof(char));
	if (!p)
		return (NULL);
	p[i + sign] = '\0';
	while (i-- > 0)
	{
		p[i + sign] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		p[0] = '-';
	return (p);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		i;
	int		nn;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	i = 1;
	nn = n;
	while (nn >= 10 || (n == 0 && i == 0))
	{
		nn /= 10;
		i++;
	}
	return (ft_str(sign, i, n));
}
