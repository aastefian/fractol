/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md_handlers_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:41:13 by svilau            #+#    #+#             */
/*   Updated: 2016/09/28 12:51:36 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		md_mouse_push_handler(int button, int x, int y, void *param)
{
	t_data_md	*data;

	data = (t_data_md*)param;
	data->move_scale = 8 / data->zoom;
	if (button == 5)
		data->zoom += md_zoom_scale('+');
	if (button == 4 && data->zoom > 200)
		data->zoom -= md_zoom_scale('-');
	if (button == 4 || button == 5)
	{
		data->middlex -= cursor_axes_coordinates_x(x) * (100 / data->zoom);
		data->middley += cursor_axes_coordinates_y(y) * (100 / data->zoom);
	}
	if (button == 3)
	{
		data->middlex = 0;
		data->middley = 0;
		data->zoom = 200;
		md_zoom_scale('0');
	}
	if (button == 1 && data->keys_pushed.rmb == 0)
		data->keys_pushed.rmb = 1;
	test_cuda_md(data, data->zoom);
	return (0);
}

int		md_mouse_release_handler(int button, int x, int y, void *param)
{
	t_data_md	*data;

	data = (t_data_md*)param;
	if (button == 1 && data->keys_pushed.rmb == 1)
	{
		data->keys_pushed.rmb = 0;
		md_scale_increase_x(data, '0');
		md_scale_increase_y(data, '0');
	}
	test_cuda_md(data, data->zoom);
	return (0);
}

int		md_mouse_move_handler(int mx, int my, void *param)
{
	t_data_md			*data;
	static int			mx_1;
	static int			my_1;

	if (!mx_1 && !my_1)
	{
		mx_1 = mx;
		my_1 = my;
	}
	data = (t_data_md*)param;
	if (data->keys_pushed.rmb == 1)
	{
		if (mx >= mx_1 + 5)
			data->middlex -= data->move_scale + md_scale_increase_x(data, '+');
		else if (mx < mx_1 - 5)
			data->middlex += data->move_scale - md_scale_increase_x(data, '-');
		if (my >= my_1 + 5)
			data->middley += data->move_scale - md_scale_increase_y(data, '-');
		else if (my < my_1 - 5)
			data->middley -= data->move_scale + md_scale_increase_y(data, '+');
	}
	mx_1 = mx;
	my_1 = my;
	test_cuda_md(data, data->zoom);
	return (0);
}
