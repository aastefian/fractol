/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 13:26:52 by svilau            #+#    #+#             */
/*   Updated: 2016/10/05 10:59:41 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../mlx-lib/mlx.h"
#include <stdlib.h>
#include <stdio.h>

void	julia_key_push_handler_3(int keycode, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	data->julia_sets = data->julia_sets->next;
	if (keycode == 49)
	{
		data->keys_pushed.z = 1;
		data->keys_pushed.space = 1;
		data->const_ju.r = data->julia_sets->c.r;
		data->const_ju.i = data->julia_sets->c.i;
	}
}

void	julia_key_push_handler_2(int keycode, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	data->move_scale = 0.03 / data->zoom;
	if (keycode == 13 && data->keys_pushed.z == 1)
		data->middley -= data->move_scale;
	if (keycode == 0 && data->keys_pushed.z == 1)
		data->middlex += data->move_scale;
	if (keycode == 1 && data->keys_pushed.z == 1)
		data->middley += data->move_scale;
	if (keycode == 2 && data->keys_pushed.z == 1)
		data->middlex -= data->move_scale;
	if (keycode == 14 && data->keys_pushed.z == 1)
		data->zoom += ju_zoom_scale('+');
	if (keycode == 12 && data->zoom > 1 && data->keys_pushed.z == 1)
		data->zoom -= ju_zoom_scale('-');
	if (keycode == 3 && data->keys_pushed.f == 1)
		data->keys_pushed.f = 0;
	else if (keycode == 3 && data->keys_pushed.f == 0)
		data->keys_pushed.f = 1;
}

int		julia_key_push_handler(int keycode, void *param)
{
	t_data_julia	*data;

	data = (t_data_julia*)param;
	if (keycode == 53)
	{
		free(data);
		exit(0);
	}
	if (keycode == 6 && data->keys_pushed.z == 0)
		data->keys_pushed.z = 1;
	else if (keycode == 6 && data->keys_pushed.z == 1)
		data->keys_pushed.z = 0;
	if (keycode == 7 && data->keys_pushed.x == 0)
		data->keys_pushed.x = 1;
	else if (keycode == 7 && data->keys_pushed.x == 1)
		data->keys_pushed.x = 0;
	if (keycode == 8 && data->keys_pushed.c == 0)
		data->keys_pushed.c = 1;
	else if (keycode == 8 && data->keys_pushed.c == 1)
		data->keys_pushed.c = 0;
	julia_key_push_handler_2(keycode, data);
	julia_key_push_handler_3(keycode, data);
	test_cuda_julia(data, data->zoom, data->mx, data->my);
	return (0);
}

void	julia_set_scroll_prepare(t_data_julia *data)
{
	t_list			*julia_sets;

	julia_sets = NULL;
	ft_list_push_back(&julia_sets, 0.29, -0.01);
	ft_list_push_back(&julia_sets, 0.26, 0);
	ft_list_push_back(&julia_sets, 0.27, 0);
	ft_list_push_back(&julia_sets, -0.03, -0.8);
	ft_list_push_back(&julia_sets, -0.23, -0.77);
	ft_list_push_back(&julia_sets, -0.24, -0.68);
	ft_list_push_back(&julia_sets, -0.29, -0.66);
	ft_list_push_back(&julia_sets, -0.31, -0.67);
	ft_list_push_back(&julia_sets, -0.33, -0.63);
	ft_list_push_back(&julia_sets, -0.35, -0.62);
	ft_list_push_back(&julia_sets, -0.5, -0.52);
	ft_list_push_back(&julia_sets, -0.82, -0.17);
	ft_list_push_back(&julia_sets, -0.82, -0.18);
	ft_list_push_back(&julia_sets, -0.75, -0.04);
	ft_list_push_back(&julia_sets, -0.76, -0.11);
	ft_list_push_back(&julia_sets, -0.76, -0.14);
	ft_list_push_back(&julia_sets, -0.76, -0.07);
	ft_list_last(julia_sets)->next = julia_sets;
	data->julia_sets = julia_sets;
}

void	julia_event_handler(t_mlx mini_l, t_img img)
{
	t_data_julia	*data;

	data = NULL;
	if (!(data = (t_data_julia*)malloc(sizeof(t_data_julia))))
		ju_put_err_free(data);
	data->mini_l = mini_l;
	data->img = img;
	data->zoom = 1;
	data->move_scale = 0.01;
	data->keys_pushed.c = 0;
	data->keys_pushed.z = 0;
	data->keys_pushed.rmb = 0;
	data->keys_pushed.f = 0;
	data->keys_pushed.space = 0;
	data->mx = 0;
	data->my = 0;
	data->middlex = 0;
	data->middley = 0;
	julia_set_scroll_prepare(data);
	mlx_hook(data->mini_l.win, 2, 2, julia_key_push_handler, data);
	mlx_hook(data->mini_l.win, 6, 6, julia_mouse_move_handler, data);
	mlx_mouse_hook(data->mini_l.win, julia_mouse_push_handler, data);
	mlx_hook(data->mini_l.win, 5, 5, julia_mouse_release_handler, data);
	mlx_string_put(data->mini_l.mlx, data->mini_l.win, 100, 200, WHITE,
			"Hello, move the cursor or press any key  to get going...");
}
