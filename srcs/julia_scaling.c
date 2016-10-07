/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_scaling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:30:59 by svilau            #+#    #+#             */
/*   Updated: 2016/09/27 12:34:05 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

float	ju_zoom_scale(char type)
{
	static float	i;
	static int		reduce;

	if (!i || type == '0')
		i = 0;
	if (type == '+' && reduce == 0)
		i += 0.5;
	if (type == '-' && i > 0.5 && reduce == 1)
		i -= 0.5;
	if (type == '+')
		reduce = 0;
	if (type == '-')
		reduce = 1;
	return (i);
}

float	scale_increase_x(t_data_julia *data, char type)
{
	static float	i;
	static int		reduce;

	if (!i || type == '0')
		i = 0;
	if (type == '+' && reduce == 0)
		i += 0.01 / data->zoom;
	if (type == '-' && i < 0.5 / data->zoom && reduce == 1)
		i -= 0.01 / data->zoom;
	if (type == '+')
		reduce = 0;
	if (type == '-')
		reduce = 1;
	return (i);
}

float	scale_increase_y(t_data_julia *data, char type)
{
	static float	i;
	static int		reduce;

	if (!i || type == '0')
		i = 0;
	if (type == '+' && reduce == 0)
		i += 0.01 / data->zoom;
	if (type == '-' && i < 0.5 / data->zoom && reduce == 1)
		i -= 0.01 / data->zoom;
	if (type == '+')
		reduce = 0;
	if (type == '-')
		reduce = 1;
	return (i);
}
