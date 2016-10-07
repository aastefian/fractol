/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_md.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 12:00:25 by svilau            #+#    #+#             */
/*   Updated: 2016/09/28 12:54:13 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <math.h>

unsigned int	coordinate_iterations_md(t_data_md *data,
		t_com c)
{
	float			zn_1r;
	float			zn_1i;
	float			zn_r;
	float			zn_i;
	unsigned int	iteration;

	zn_1r = 0;
	zn_1i = 0;
	iteration = 0;
	while (iteration < DEF_CPU_MAX_ITERATIONS)
	{
		zn_r = (zn_1r * zn_1r) - (zn_1i * zn_1i) + c.r;
		zn_i = 2 * zn_1r * zn_1i + c.i;
		zn_1r = zn_r;
		zn_1i = zn_i;
		if ((zn_r * zn_r + zn_i * zn_i) > 4)
			break ;
		iteration++;
	}
	return (iteration);
}

void			cpu_md(t_data_md *data, unsigned int **a_h)
{
	int				row;
	int				col;
	int				index;
	unsigned int	*a_d;
	unsigned int	size;

	size = DEF_WIN_WIDTH * DEF_WIN_HEIGHT * sizeof(unsigned int);
	if (!(a_d = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		return ;
	row = 0;
	while (row < DEF_WIN_HEIGHT)
	{
		col = 0;
		while (col < DEF_WIN_WIDTH)
		{
			index = row * DEF_WIN_WIDTH + col;
			a_d[index] = coordinate_iterations_md(data,
					const_md(data, row, col));
			col++;
		}
		row++;
	}
	ft_memcpy(*a_h, a_d, size);
}
