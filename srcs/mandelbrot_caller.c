/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md_caller.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 12:20:04 by svilau            #+#    #+#             */
/*   Updated: 2016/09/30 10:29:15 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../cudaheader/cuda_md.h"
#include "../mlx-lib/mlx.h"
#include <stdlib.h>

t_com			const_md(t_data_md *data, int row, int col)
{
	t_com c;

	c.r = ((col - ((float)(DEF_WIN_WIDTH - 2) / 2)) / data->zoom) -
		data->middlex;
	c.i = ((row - ((float)(DEF_WIN_HEIGHT - 2) / 2)) / data->zoom) +
		data->middley;
	return (c);
}

void			md_pixel_color(t_data_md *data, t_2d_p *pixel,
							int iteration)
{
	if (data->keys_pushed.f == 0)
		pixel->color = int_gradient(iteration);
	else
		pixel->color = hsv_handler(iteration);
}

void			color_image_md(t_data_md *data,
		unsigned int *a_h)
{
	int				i;
	int				j;
	t_2d_p			pixel;

	i = 0;
	while (i < DEF_WIN_HEIGHT)
	{
		j = 0;
		while (j < DEF_WIN_WIDTH)
		{
			pixel.x = j;
			pixel.y = i;
			if ((a_h[i * DEF_WIN_WIDTH + j] < DEF_GPU_MAX_ITERATIONS &&
						data->keys_pushed.c == 1) ||
				(a_h[i * DEF_WIN_WIDTH + j] < DEF_CPU_MAX_ITERATIONS &&
					data->keys_pushed.c == 0))
				md_pixel_color(data, &pixel, a_h[i * DEF_WIN_WIDTH + j]);
			else
				pixel.color = 0;
			pixel_to_image_handler(data->mini_l, data->img, pixel);
			j++;
		}
		i++;
	}
}

void			test_cuda_md(t_data_md *data, float zoom)
{
	unsigned int	*a_h;
	int				i;
	int				j;
	size_t			size;
	t_2d_p			pixel;

	i = 0;
	size = DEF_WIN_WIDTH * DEF_WIN_HEIGHT + 1;
	if (!(a_h = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		return ;
	if (data->keys_pushed.c == 1)
		cuda_call_md(a_h, (unsigned int)DEF_WIN_WIDTH,
			(unsigned int)DEF_WIN_HEIGHT, (float)data->middlex,
			(float)data->middley, (float)zoom, (unsigned int)1000, 0);
	else
		cpu_md(data, &a_h);
	color_image_md(data, a_h);
	mlx_put_image_to_window(data->mini_l.mlx, data->mini_l.win,
			data->img.img, 0, 0);
	free(a_h);
}
