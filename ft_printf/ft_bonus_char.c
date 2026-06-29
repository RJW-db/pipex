/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bonus_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/09 18:09:43 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/03/01 17:40:55 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

int	chr_bonus_count(t_p *c, t_fl *f)
{
	va_arg(c->va, int);
	if (f->width == 0)
	{
		c->mal++;
	}
	else
	{
		c->mal += f->width;
	}
	return (c->mal);
}

void	chr_bonus(t_p *p, t_fl *f)
{
	if (f->dash == false)
	{
		p->i += ft_cpy_n_chr(p->str + p->i, ' ', f->width - 1);
	}
	p->str[p->i] = va_arg(p->va, int);
	p->i++;
	if (f->dash == true && f->width > 0)
	{
		p->i += ft_cpy_n_chr(p->str + p->i, ' ', f->width - 1);
	}
}
