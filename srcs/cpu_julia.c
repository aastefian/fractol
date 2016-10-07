/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_julia.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 11:57:20 by svilau            #+#    #+#             */
/*   Updated: 2016/09/19 13:18:55 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include <stdlib.h>

unsigned int	coordinate_iterations_julia(t_data_julia *data, int row,
		int col, t_com c)
{
	float			zn_1r;
	float			zn_1i;
	float			zn_r;
	float			zn_i;
	unsigned int	iteration;

	iteration = 0;
	zn_1r = (((float)(((col) - DEF_WIN_WIDTH / 2 + 1) * 2) /
		(float)((DEF_WIN_WIDTH - 2) / 2)) / data->zoom) - data->middlex;
	zn_1i = (((float)((DEF_WIN_HEIGHT / 2 - (row) - 1) * 2) /
		(float)((DEF_WIN_HEIGHT - 2) / 2)) / data->zoom) - data->middley;
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

void			cpu_julia(t_data_julia *data, unsigned int **a_h, t_com c)
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
			a_d[index] = coordinate_iterations_julia(data, row, col, c);
			col++;
		}
		row++;
	}
	ft_memcpy(*a_h, a_d, size);
}
