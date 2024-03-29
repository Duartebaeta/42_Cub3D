/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:16:39 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/15 19:57:27 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static t_texture	select_texture(char c)
{
	t_texture	curr;

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

static int	get_color(int tex_x, int tex_y, int i, t_texture *curr)
{
	int			bpp;
	char		*data;
	int			color;
	int			pixel_index;

	data = mlx_get_data_addr(curr->img, &curr->img_data.bpp,
			&curr->img_data.line_length, &curr->img_data.endian);
	bpp = curr->img_data.bpp;
	bpp /= 8;
	color = 0;
	pixel_index = tex_y * curr->w + tex_x;
	i = -1;
	while (++i < bpp)
		color |= data[(pixel_index * bpp) + i] << (8 * i);
	return (color);
}

void	draw_wall_texture(double low_y, double hi_y, int i)
{
	t_texture	curr;
	int			tex_x;
	double		hi_low_diff;
	int			tex_y;
	int			counter;

	curr = select_texture(cub()->ray.cardinal);
	hi_low_diff = (hi_y - low_y);
	tex_x = (int)(cub()->ray.calc_dist * curr.w);
	counter = (int)ceil(low_y) - 1;
	if (counter < 0)
		counter = -1;
	while (++counter <= (int)hi_y && counter <= H_3D)
	{
		tex_y = (int)(((counter - low_y) / hi_low_diff) * curr.h);
		my_mlx_pixel_put(cub()->img_3d, i, counter,
			get_color(tex_x, tex_y, counter, &curr));
	}
}

void	load_textures(t_cub3d *cub3d)
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
	cub3d->no.img = mlx_xpm_file_to_image(mlx, no, &cub()->no.w, &cub()->no.h);
	cub3d->so.img = mlx_xpm_file_to_image(mlx, so, &cub()->so.w, &cub()->so.h);
	cub3d->we.img = mlx_xpm_file_to_image(mlx, we, &cub()->we.w, &cub()->we.h);
	cub3d->ea.img = mlx_xpm_file_to_image(mlx, ea, &cub()->ea.w, &cub()->ea.h);
}
