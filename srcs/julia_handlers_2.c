/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:28:49 by svilau            #+#    #+#             */
/*   Updated: 2016/10/05 11:27:05 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		julia_mouse_push_handler_2(int button, int x, int y, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	if (button == 3)
	{
		data->zoom = 1;
		data->middlex = 0;
		data->middley = 0;
		ju_zoom_scale('0');
	}
	if (button == 1 && data->keys_pushed.rmb == 0)
		data->keys_pushed.rmb = 1;
	return (0);
}

int		julia_mouse_push_handler(int button, int x, int y, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	data->move_scale = 0.03 / data->zoom;
	if (button == 5 && data->keys_pushed.z == 1)
		data->zoom += ju_zoom_scale('+');
	if (button == 4 && data->zoom >= 1 && data->keys_pushed.z == 1)
		data->zoom -= ju_zoom_scale('-');
	if ((button == 4 || button == 5) && data->keys_pushed.z == 1)
	{
		data->middlex -= cursor_axes_coordinates_x(x) * (0.55 / data->zoom);
		data->middley += cursor_axes_coordinates_y(y) * (0.55 / data->zoom);
	}
	if (data->zoom < 1)
		data->zoom = 1;
	julia_mouse_push_handler_2(button, x, y, data);
	test_cuda_julia(data, data->zoom, data->mx, data->my);
	return (0);
}

int		julia_mouse_release_handler(int button, int x, int y, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	if (button == 1 && data->keys_pushed.rmb == 1)
	{
		data->keys_pushed.rmb = 0;
		scale_increase_x(data, '0');
		scale_increase_y(data, '0');
	}
	test_cuda_julia(data, data->zoom, data->mx, data->my);
	return (0);
}

int		julia_mouse_move_handler_2(int mx, int my, void *param)
{
	t_data_julia	*data;
	static int		mx_1;
	static int		my_1;

	data = (t_data_julia*)param;
	if (!mx_1 && !my_1)
	{
		mx_1 = mx;
		my_1 = my;
	}
	if (data->keys_pushed.rmb == 1)
	{
		if (mx >= mx_1 + 5)
			data->middlex -= data->move_scale + scale_increase_x(data, '+');
		else if (mx < mx_1 - 5)
			data->middlex += data->move_scale - scale_increase_x(data, '-');
		if (my >= my_1 + 5)
			data->middley += data->move_scale - scale_increase_y(data, '-');
		else if (my < my_1 - 5)
			data->middley -= data->move_scale + scale_increase_y(data, '+');
	}
	mx_1 = mx;
	my_1 = my;
	return (0);
}

int		julia_mouse_move_handler(int mx, int my, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	if (data->keys_pushed.z != 1)
	{
		data->mx = mx;
		data->my = my;
	}
	julia_mouse_move_handler_2(mx, my, data);
	test_cuda_julia(data, data->zoom, data->mx, data->my);
	return (0);
}
