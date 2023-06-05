/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:16:39 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/05 17:32:11 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static __uint32_t	get_color(int tex_x, int tex_y, int i, t_texture *curr)
{
	int			bpp;
	char		*data;
	__uint32_t	color;

	data = curr->data;
	bpp = curr->img_data.bpp;
	bpp /= 8;
	color = 0;
	i = -1;
	while (++i < bpp)
		color |= (unsigned char)data[tex_y * curr->img_data.line_length + tex_x * bpp + i]
			<< (8 * i);
	return (color);
}

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

void	draw_wall_texture(double low_y, double hi_y, int i)
{
	t_texture	curr;
	int			tex_x;
	double			hi_low_diff;
	int			tex_y;
	int			counter;

	curr = select_texture(cub()->ray.cardinal);
	hi_low_diff = 1.0 / (hi_y - low_y);
	tex_x = (int)(cub()->ray.calc_dist * TILESIZE) % curr.w;
	counter = (int)ceil(low_y) - 1;
	while (++counter <= hi_y)
	{
		tex_y = (int)((counter - low_y) * curr.h * hi_low_diff);
		my_mlx_pixel_put(cub()->img_3d, i, counter, get_color(tex_x, tex_y, counter, &curr));
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
	cub3d->no.data = mlx_get_data_addr(cub3d->no.img, &cub3d->no.img_data.bpp, &cub3d->no.img_data.line_length, &cub3d->no.img_data.endian);
	cub3d->so.img = mlx_xpm_file_to_image(mlx, so, &cub()->so.w, &cub()->so.h);
	cub3d->so.data = mlx_get_data_addr(cub3d->so.img, &cub3d->so.img_data.bpp, &cub3d->so.img_data.line_length, &cub3d->so.img_data.endian);
	cub3d->we.img = mlx_xpm_file_to_image(mlx, we, &cub()->we.w, &cub()->we.h);
	cub3d->we.data = mlx_get_data_addr(cub3d->we.img, &cub3d->we.img_data.bpp, &cub3d->we.img_data.line_length, &cub3d->we.img_data.endian);
	cub3d->ea.img = mlx_xpm_file_to_image(mlx, ea, &cub()->ea.w, &cub()->ea.h);
	cub3d->ea.data = mlx_get_data_addr(cub3d->ea.img, &cub3d->ea.img_data.bpp, &cub3d->ea.img_data.line_length, &cub3d->ea.img_data.endian);
}
