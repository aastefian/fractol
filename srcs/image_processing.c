/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:16:37 by svilau            #+#    #+#             */
/*   Updated: 2016/09/20 10:02:11 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include "../mlx-lib/mlx.h"

void	pixel_to_image_l_endian(t_mlx mini_l, t_img img_1, t_2d_p pixel)
{
	unsigned int color1;
	unsigned int color2;
	unsigned int color3;

	color1 = mlx_get_color_value(mini_l.mlx, pixel.color);
	color2 = color1;
	color3 = color1;
	img_1.data += pixel.x * (img_1.bits_per_pixel / 8) + pixel.y
		* img_1.size_line;
	*img_1.data &= 0x00000000;
	color1 &= 0x000000FF;
	*img_1.data = color1;
	img_1.data++;
	*img_1.data &= 0x00000000;
	color2 &= 0x0000FF00;
	color2 >>= 8;
	*img_1.data = color2;
	img_1.data++;
	*img_1.data &= 0x00000000;
	color3 &= 0x00FF0000;
	color3 >>= 16;
	*img_1.data = color3;
}

void	pixel_to_image_handler(t_mlx mini_l, t_img img_1, t_2d_p pixel)
{
	if (img_1.endian == 1)
		ft_putstr("This part needs to be implemented for big endian\n");
	else
		pixel_to_image_l_endian(mini_l, img_1, pixel);
}
