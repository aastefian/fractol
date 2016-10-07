/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 11:12:41 by svilau            #+#    #+#             */
/*   Updated: 2016/10/05 11:57:18 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

void	put_err(void)
{
	ft_putstr("Usage: ./ft_fractol [param]\n");
	ft_putstr("Availble fractals(parameters) are:\n  -Julia (ju)\n");
	ft_putstr("  -Mandelbrot (md)\n  -Burning Ship (bs)\n");
	exit(0);
}

void	ju_put_err_free(t_data_julia *data)
{
	ft_putstr("Not enough memory\n");
	free(data);
	exit(0);
}

void	md_put_err_free(t_data_md *data)
{
	ft_putstr("Not enough memory\n");
	free(data);
	exit(0);
}

int		sign(float x)
{
	return (x > 0) - (x < 0);
}

int		int_gradient(unsigned int iteration)
{
	int r;
	int g;
	int b;

	if (iteration == 0)
	{
		b = 255;
		g = 255;
		r = 255;
	}
	else
	{
		b = (iteration % 500) * 248;
		g = (iteration % 500) * 248;
		r = (iteration % 500) * 248;
	}
	return ((r & 255) << 16) + ((g & 255) << 8) + (b & 255);
}
