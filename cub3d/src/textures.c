/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:16:39 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/14 20:20:37 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static t_texture select_texture(char c);
static __uint32_t get_color(int tex_x, int tex_y, int i, t_texture curr);

void	load_textures(void)
{
	void	*mlx;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	mlx = cub()->mlx;
	no = cub()->no.addr;
	so = cub()->so.addr;
	we = cub()->we.addr;
	ea = cub()->ea.addr;
	cub()->no.img = mlx_xpm_file_to_image(mlx, no, &cub()->no.w, &cub()->no.h);
	cub()->so.img = mlx_xpm_file_to_image(mlx, so, &cub()->so.w, &cub()->so.h);
	cub()->we.img = mlx_xpm_file_to_image(mlx, we, &cub()->we.w, &cub()->we.h);
	cub()->ea.img = mlx_xpm_file_to_image(mlx, ea, &cub()->ea.w, &cub()->ea.h);
}

void	draw_wall_texture(double low_y, double hi_y, int i)
{
	t_texture curr;
	__uint32_t new_color;
	int tex_x;
	int tex_y;
	double counter;

	curr = select_texture(cub()->ray.cardinal);
	tex_x = (int)(cub()->ray.calc_dist * 32.0) % curr.w;
	counter = ceil(low_y) - 1;
	while (++counter <= hi_y)
	{
		tex_y = (int)((counter - low_y) * curr.h / (hi_y - low_y));
		new_color = get_color(tex_x, tex_y, 0, curr);
		my_mlx_pixel_put(cub()->img_3d, i, counter, new_color);
	}
}

static __uint32_t	get_color(int tex_x, int tex_y, int i, t_texture curr)
{
	int bpp;
	int line_size;
	int endian;
	char *data;
	__uint32_t color;

	data = mlx_get_data_addr(curr.img, &bpp, &line_size, &endian);
	bpp /= 8;
	color = 0;
	i = -1;
	while (++i < bpp)
		color |= (unsigned char)data[tex_y * line_size + tex_x * bpp + i] << (8 * i);
	return (color);
}

static t_texture	select_texture(char c)
{
	t_texture curr;

	if (c == 'n')
		curr = cub()->no;
	else if (c == 's')
		curr = cub()->so;
	else if (c == 'w')
		curr = cub()->we;
	else
		curr = cub()->ea;
	return (curr);
}
