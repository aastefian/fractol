/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:42:15 by svilau            #+#    #+#             */
/*   Updated: 2016/10/05 11:31:32 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include "../mlx-lib/mlx.h"
#include <stdlib.h>

void			ju_instructions(void)
{
	ft_putstr("(C) - CUDA on/off\n");
	ft_putstr("(F) - Change colour theme\n");
	ft_putstr("(Z) - Zoom mode on/off\n");
	ft_putstr("(E / Q) / (MouseWheel)- Zoom in/out\n");
	ft_putstr("(Mouse Button Press) - Reset zoom level and center ");
	ft_putstr("fractal\n");
	ft_putstr("(W-A-S-D) / (RMB + mouse_move) - Naviguer dans le ");
	ft_putstr("fractal (uniquement en mode zoom)\n");
	ft_putstr("(SPACE) - Change between fractal presets\n");
}

void			md_instructions(void)
{
	ft_putstr("(C) - CUDA on/off\n");
	ft_putstr("(F) - Change colour theme\n");
	ft_putstr("(E / Q) / (MouseWheel)- Zoom in/out\n");
	ft_putstr("(Mouse Button Press) - Reset zoom level and center ");
	ft_putstr("fractal\n");
	ft_putstr("(W-A-S-D) / (RMB + mouse_move) - Naviguer dans le fractal\n");
}

void			bs_instructions(void)
{
	ft_putstr("(C) - CUDA on/off\n");
	ft_putstr("(F) - Change colour theme\n");
	ft_putstr("(E / Q) / (MouseWheel)- Zoom in/out\n");
	ft_putstr("(Mouse Button Press) - Reset zoom level and center ");
	ft_putstr("fractal\n");
	ft_putstr("(W-A-S-D) / (RMB + mouse_move) - Naviguer dans le fractal\n");
}

void			fractol(char *av)
{
	t_mlx	mini_l;
	t_img	img_1;
	int		i;

	if (ft_strcmp(av, "ju") != 0 && ft_strcmp(av, "bs") != 0 &&
		ft_strcmp(av, "md") != 0)
		put_err();
	i = 0;
	mini_l.mlx = mlx_init();
	mini_l.win = mlx_new_window(mini_l.mlx, DEF_WIN_WIDTH, DEF_WIN_HEIGHT,
			"Fractol Beta v1.0");
	img_1.img = mlx_new_image(mini_l.mlx, DEF_WIN_WIDTH, DEF_WIN_HEIGHT);
	img_1.data = mlx_get_data_addr(img_1.img, &img_1.bits_per_pixel,
			&img_1.size_line, &img_1.endian);
	if (ft_strcmp(av, "bs") == 0)
		bs_event_handler(mini_l, img_1);
	else if (ft_strcmp(av, "ju") == 0)
		julia_event_handler(mini_l, img_1);
	else if (ft_strcmp(av, "md") == 0)
		md_event_handler(mini_l, img_1);
	hsv_to_rgb_int(120, 1, 1);
	mlx_loop(mini_l.mlx);
}

int				main(int ac, char **av)
{
	int i;

	i = -1;
	if (ac == 1)
		put_err();
	else
	{
		if (ft_strcmp(av[1], "ju") == 0)
			ju_instructions();
		if (ft_strcmp(av[1], "md") == 0)
			md_instructions();
		if (ft_strcmp(av[1], "bs") == 0)
			bs_instructions();
		fractol(av[1]);
	}
	return (0);
}
