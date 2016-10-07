/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:42:37 by svilau            #+#    #+#             */
/*   Updated: 2016/09/30 17:03:05 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define DEF_WIN_WIDTH 802
# define DEF_WIN_HEIGHT 802
# define DEF_CPU_MAX_ITERATIONS 500
# define DEF_GPU_MAX_ITERATIONS 1000
# define ZOOM_SCALE 10
# define WHITE 16777215

typedef struct		s_mlx
{
	void *mlx;
	void *win;
}					t_mlx;

typedef struct		s_2d_p
{
	int x;
	int y;
	int color;
}					t_2d_p;

typedef struct		s_rgb
{
	int r;
	int g;
	int b;
}					t_rgb;

typedef struct		s_com
{
	double r;
	double i;
}					t_com;

typedef struct		s_img
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data;
}					t_img;

typedef struct		s_keys
{
	int f;
	int c;
	int x;
	int z;
	int rmb;
	int space;
}					t_keys;

typedef struct		s_list
{
	t_com			c;
	struct s_list	*next;
}					t_list;

typedef struct		s_data_julia
{
	int		mx;
	int		my;
	float	zoom;
	float	middlex;
	float	middley;
	float	move_scale;
	t_mlx	mini_l;
	t_img	img;
	t_keys	keys_pushed;
	t_list	*julia_sets;
	t_com	const_ju;
}					t_data_julia;

typedef struct		s_data_bs
{
	float	zoom;
	float	middlex;
	float	middley;
	float	move_scale;
	t_mlx	mini_l;
	t_img	img;
	t_keys	keys_pushed;
}					t_data_bs;

typedef struct		s_data_md
{
	float	zoom;
	float	middlex;
	float	middley;
	float	move_scale;
	t_mlx	mini_l;
	t_img	img;
	t_keys	keys_pushed;
}					t_data_md;

void				md_put_err_free(t_data_md *data);
void				ju_put_err_free(t_data_julia *data);
t_list				*ft_create_elem(double cr, double ci);
void				ft_list_push_back(t_list **begin_list, double cr,
										double ci);
t_list				*ft_list_last(t_list *begin_list);
int					hsv_handler(int iteration);
int					hsv_to_rgb_int(float h, float s, float v);
void				put_err(void);
int					sign(float x);
float				ju_zoom_scale(char type);
float				bs_zoom_scale(char type);
float				md_zoom_scale(char type);
float				scale_increase_x(t_data_julia *data, char type);
float				scale_increase_y(t_data_julia *data, char type);
float				bs_scale_increase_x(t_data_bs *data, char type);
float				bs_scale_increase_y(t_data_bs *data, char type);
float				md_scale_increase_x(t_data_md *data, char type);
float				md_scale_increase_y(t_data_md *data, char type);
void				move_scale(float *move_scale, char type);
int					bs_mouse_push_handler(int button, int x, int y,
													void *param);
int					bs_mouse_release_handler(int button, int x, int y,
													void *param);
int					bs_mouse_move_handler(int mx, int my, void *param);
int					md_mouse_push_handler(int button, int x, int y,
													void *param);
int					md_mouse_release_handler(int button, int x, int y,
													void *param);
int					md_mouse_move_handler(int mx, int my, void *param);
int					julia_mouse_push_handler(int button, int x, int y,
												void *param);
int					julia_mouse_release_handler(int button, int x, int y,
												void *param);
int					julia_mouse_move_handler(int mx, int my, void *param);
int					int_gradient(unsigned int iteration);
void				test_cuda_julia(t_data_julia *data, float zoom, int zx,
									int zy);
void				julia_event_handler(t_mlx mini_l, t_img img);
void				bs_event_handler(t_mlx mini_l, t_img img);
void				md_event_handler(t_mlx mini_l, t_img img);
void				pixel_to_image_handler(t_mlx mini_l, t_img img,
											t_2d_p pixel);
float				cursor_axes_coordinates_x(int x);
float				cursor_axes_coordinates_y(int y);

unsigned int		coordinate_iterations_julia(t_data_julia *data, int row,
		int col, t_com c);
void				cpu_julia(t_data_julia *data, unsigned int **a_h, t_com c);

unsigned int		coordinate_iterations_bs(t_data_bs *data,
		t_com c);
void				cpu_bs(t_data_bs *data, unsigned int **a_h);
void				cpu_md(t_data_md *data, unsigned int **a_h);

void				const_julia(t_data_julia *dat, int mx, int my);
void				test_cuda_julia(t_data_julia *data, float zoom, int mx,
									int my);
void				color_image_julia(t_data_julia *data, unsigned int *a_h);

void				test_cuda_bs(t_data_bs *data, float zoom);
void				test_cuda_md(t_data_md *data, float zoom);
void				color_image_bs(t_data_bs *data,
		unsigned int *a_h);
void				color_image_md(t_data_md *data,
		unsigned int *a_h);
t_com				const_bs(t_data_bs *data, int row, int col);
t_com				const_md(t_data_md *data, int row, int col);
#endif
