/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_scaling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:34:56 by svilau            #+#    #+#             */
/*   Updated: 2016/09/28 12:52:25 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

float	bs_zoom_scale(char type)
{
	static float	i;
	static int		reduce;

	if (!i || type == '0')
		i = 0;
	if (type == '+' && reduce == 0)
		i += 40;
	if (type == '-' && i > 40 && reduce == 1)
		i -= 40;
	if (type == '+')
		reduce = 0;
	if (type == '-')
		reduce = 1;
	return (i);
}

float	bs_scale_increase_x(t_data_bs *data, char type)
{
	static float	i;
	static int		reduce;

	if (!i || type == '0')
		i = 0;
	if (type == '+' && reduce == 0)
		i += 0.3 / data->zoom;
	if (type == '-' && i < 5 / data->zoom && reduce == 1)
		i -= 0.3 / data->zoom;
	if (type == '+')
		reduce = 0;
	if (type == '-')
		reduce = 1;
	return (i);
}

float	bs_scale_increase_y(t_data_bs *data, char type)
{
	static float	i;
	static int		reduce;

	if (!i || type == '0')
		i = 0;
	if (type == '+' && reduce == 0)
		i += 0.3 / data->zoom;
	if (type == '-' && i < 5 / data->zoom && reduce == 1)
		i -= 0.3 / data->zoom;
	if (type == '+')
		reduce = 0;
	if (type == '-')
		reduce = 1;
	return (i);
}
