/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 16:00:51 by svilau            #+#    #+#             */
/*   Updated: 2016/09/28 11:44:25 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int		hsv_handler(int iteration)
{
	if (iteration > 15 && iteration != 0)
		return (hsv_to_rgb_int(iteration % 359, 1, 1));
	else if (iteration <= 15)
		return (hsv_to_rgb_int(0, ((float)iteration / 15), 1));
	else
		return (hsv_to_rgb_int(0, 0, 1));
}

int		hsv_0_to_120(float h, float c, float x, float m)
{
	t_rgb	rgb;

	if (0 <= h && h < 60)
	{
		rgb.r = (c + m) * 255;
		rgb.g = (x + m) * 255;
		rgb.b = (0 + m) * 255;
	}
	else if (60 <= h && h < 120)
	{
		rgb.r = (x + m) * 255;
		rgb.g = (c + m) * 255;
		rgb.b = (0 + m) * 255;
	}
	return ((rgb.r & 255) << 16) + ((rgb.g & 255) << 8) + (rgb.b & 255);
}

int		hsv_120_to_240(float h, float c, float x, float m)
{
	t_rgb	rgb;

	if (120 <= h && h < 180)
	{
		rgb.r = (0 + m) * 255;
		rgb.g = (c + m) * 255;
		rgb.b = (x + m) * 255;
	}
	else if (180 <= h && h < 240)
	{
		rgb.r = (0 + m) * 255;
		rgb.g = (x + m) * 255;
		rgb.b = (c + m) * 255;
	}
	return ((rgb.r & 255) << 16) + ((rgb.g & 255) << 8) + (rgb.b & 255);
}

int		hsv_240_to_360(float h, float c, float x, float m)
{
	t_rgb	rgb;

	if (240 <= h && h < 300)
	{
		rgb.r = (x + m) * 255;
		rgb.g = (0 + m) * 255;
		rgb.b = (c + m) * 255;
	}
	else if (300 <= h && h < 360)
	{
		rgb.r = (c + m) * 255;
		rgb.g = (0 + m) * 255;
		rgb.b = (x + m) * 255;
	}
	return ((rgb.r & 255) << 16) + ((rgb.g & 255) << 8) + (rgb.b & 255);
}

int		hsv_to_rgb_int(float h, float s, float v)
{
	float	c;
	float	x;
	float	m;
	t_rgb	rgb;

	if (h < 0 || h >= 360 || s < 0 || s > 1 || v < 0 || v > 1)
		return (0);
	c = v * s;
	x = c * (1 - fabs(fmod((h / 60), 2) - 1));
	m = v - c;
	if (0 <= h && h < 120)
		return (hsv_0_to_120(h, c, x, m));
	else if (120 <= h && h < 240)
		return (hsv_120_to_240(h, c, x, m));
	else
		return (hsv_240_to_360(h, c, x, m));
}
