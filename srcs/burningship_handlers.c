/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 13:29:29 by svilau            #+#    #+#             */
/*   Updated: 2016/10/07 15:08:06 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>
#include "../mlx-lib/mlx.h"

void	bs_key_push_handler_2(int keycode, void *param)
{
	t_data_bs	*data;

	data = (t_data_bs*)param;
	data->move_scale = 8 / data->zoom;
	if (keycode == 3 && data->keys_pushed.f == 1)
		data->keys_pushed.f = 0;
	else if (keycode == 3 && data->keys_pushed.f == 0)
		data->keys_pushed.f = 1;
	if (keycode == 13)
		data->middley -= data->move_scale;
	if (keycode == 0)
		data->middlex += data->move_scale;
	if (keycode == 1)
		data->middley += data->move_scale;
	if (keycode == 2)
		data->middlex -= data->move_scale;
}

int		bs_key_push_handler(int keycode, void *param)
{
	t_data_bs	*data;

	data = (t_data_bs*)param;
	if (keycode == 53)
	{
		free(data);
		exit(0);
	}
	if (keycode == 8 && data->keys_pushed.c == 0)
		data->keys_pushed.c = 1;
	else if (keycode == 8 && data->keys_pushed.c == 1)
		data->keys_pushed.c = 0;
	if (keycode == 14)
		data->zoom += bs_zoom_scale('+');
	if (keycode == 12 && data->zoom > 200)
		data->zoom -= bs_zoom_scale('-');
	bs_key_push_handler_2(keycode, data);
	test_cuda_bs(data, data->zoom);
	return (0);
}

void	bs_event_handler(t_mlx mini_l, t_img img)
{
	t_data_bs *data;

	data = NULL;
	data = (t_data_bs*)malloc(sizeof(t_data_bs) * 1);
	data->mini_l = mini_l;
	data->img = img;
	data->zoom = 200;
	data->move_scale = 0.01;
	data->middlex = 0;
	data->middley = 0;
	data->keys_pushed.c = 0;
	data->keys_pushed.rmb = 0;
	data->keys_pushed.space = 0;
	data->keys_pushed.f = 0;
	mlx_hook(data->mini_l.win, 2, 2, bs_key_push_handler, data);
	mlx_hook(data->mini_l.win, 6, 6, bs_mouse_move_handler, data);
	mlx_mouse_hook(data->mini_l.win, bs_mouse_push_handler, data);
	mlx_hook(data->mini_l.win, 5, 5, bs_mouse_release_handler, data);
	mlx_string_put(data->mini_l.mlx, data->mini_l.win, 100, 200, WHITE,
			"Hello, move cursor or press any key to get going...");
}
