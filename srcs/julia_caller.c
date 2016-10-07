/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_caller.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 12:14:03 by svilau            #+#    #+#             */
/*   Updated: 2016/10/05 11:31:08 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../cudaheader/cuda_ju.h"
#include "../mlx-lib/mlx.h"
#include <stdlib.h>
#include <stdio.h>

void			const_julia_p2(int mx, int my, t_com *c)
{
	if (mx >= 0 && mx <= DEF_WIN_WIDTH && my < 0)
	{
		c->r = -4;
		c->i = -4 + 0.01 * mx;
	}
	else if (mx > DEF_WIN_WIDTH && my > DEF_WIN_HEIGHT)
	{
		c->r = 4;
		c->i = 4;
	}
	else if (mx > DEF_WIN_WIDTH && my <= DEF_WIN_HEIGHT && my >= 0)
	{
		c->r = -4 + 0.01 * my;
		c->i = 4;
	}
	else if (mx <= DEF_WIN_WIDTH && mx >= 0 && my > DEF_WIN_HEIGHT)
	{
		c->r = 4;
		c->i = -4 + 0.01 * mx;
	}
	else
	{
		c->r = -4 + 0.01 * my;
		c->i = -4 + 0.01 * mx;
	}
}

void			const_julia(t_data_julia *data, int mx, int my)
{
	static t_com c;

	if (data->keys_pushed.z == 1)
		return ;
	if (data->keys_pushed.space == 1)
	{
		data->keys_pushed.space = 0;
		return ;
	}
	if (mx < 0 && my < 0)
	{
		c.r = 4;
		c.i = -4;
	}
	else if (mx < 0 && my >= 0 && my <= DEF_WIN_HEIGHT)
	{
		c.r = -4 + 0.01 * my;
		c.i = -4;
	}
	const_julia_p2(mx, my, &c);
	data->const_ju = c;
}

void			ju_pixel_color(t_data_julia *data, t_2d_p *pixel, int iteration)
{
	if (data->keys_pushed.f == 0)
		pixel->color = int_gradient(iteration);
	else
		pixel->color = hsv_handler(iteration);
}

void			color_image_julia(t_data_julia *data, unsigned int *a_h)
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
				ju_pixel_color(data, &pixel, a_h[i * DEF_WIN_WIDTH + j]);
			else
				pixel.color = 0;
			pixel_to_image_handler(data->mini_l, data->img, pixel);
			j++;
		}
		i++;
	}
}

void			test_cuda_julia(t_data_julia *data, float zoom, int mx, int my)
{
	unsigned int	*a_h;
	size_t			size;

	size = DEF_WIN_WIDTH * DEF_WIN_HEIGHT + 1;
	if (!(a_h = (unsigned int*)malloc(sizeof(unsigned int) * size)))
		return ;
	const_julia(data, mx, my);
	if (data->keys_pushed.c == 1)
		cuda_call_julia(a_h, (unsigned int)DEF_WIN_WIDTH,
			(unsigned int)DEF_WIN_HEIGHT, (float)data->middlex,
			(float)data->middley, (float)zoom,
			data->const_ju, (unsigned int)1000, 0);
	else
		cpu_julia(data, &a_h, data->const_ju);
	color_image_julia(data, a_h);
	mlx_put_image_to_window(data->mini_l.mlx, data->mini_l.win,
			data->img.img, 0, 0);
	free(a_h);
}
