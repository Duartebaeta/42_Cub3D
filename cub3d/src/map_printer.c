/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:49:20 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/03/14 19:08:47 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	print_horizontal(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while(++counter < ZOOM)
		my_mlx_pixel_put(cub3d->img_2d, x + counter, y, color);
}

void	print_vertical(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while (++counter < ZOOM)
		my_mlx_pixel_put(cub3d->img_2d, x, y + counter, color);
}

void	print_square(t_cub3d *cub3d, int x, int y, int color)
{
	int counter;

	counter = -1;
	while (++counter < ZOOM)
		print_horizontal(cub3d, x, y + counter, color);
}

void	print_player(t_cub3d *cub3d, float x, float y, int ray)
{
	static const double PI = 3.1415926535;
	double i, angle, x1, y1;

	for(i = 0; i < 360; i += 0.1)
	{
		angle = i;
		int r = ray;
		while (--r)
		{
			x1 = r * cos(angle * PI / 180);
			y1 = r * sin(angle * PI / 180);
			my_mlx_pixel_put(cub3d->img_2d, x + x1, y + y1, create_trgb(1, 70, 120, 20));
		}
	}
	for (float tmp = to_deg(cub3d->player.angle); tmp > to_deg(cub3d->player.angle) - 20; tmp -= 0.1)
	{
		raycast(cub3d->player.x, cub3d->player.y, to_radian(tmp));
	}
	for (float tmp = to_deg(cub3d->player.angle); tmp < to_deg(cub3d->player.angle) + 20; tmp += 0.1)
	{
		raycast(cub3d->player.x, cub3d->player.y, to_radian(tmp));
	}
	raycast(cub3d->player.x, cub3d->player.y, cub3d->player.angle);
}

void	print_lines(t_cub3d *cub3d)
{
	int	counter;
	int	sub;

	counter = -1;
	while(cub3d->map[++counter])
	{
		sub = -1;
		while (cub3d->map[counter][++sub])
		{
			if (cub3d->map[counter][sub] == '1' || cub3d->map[counter][sub] == '0')
			{
				if (cub3d->map[counter][sub] == '1')
					print_square(cub3d, sub * ZOOM, counter * ZOOM, create_trgb(1, 255, 255, 255));
				else
					print_square(cub3d, sub * ZOOM, counter * ZOOM, create_trgb(1, 0, 0, 0));
				print_horizontal(cub3d, sub * ZOOM, counter * ZOOM, create_trgb(1, 255, 255, 255));
				print_horizontal(cub3d, sub * ZOOM, (counter + 1) * ZOOM, create_trgb(1, 255, 255, 255));
				print_vertical(cub3d, sub * ZOOM, counter * ZOOM, create_trgb(1, 255, 255, 255));
				print_vertical(cub3d, (sub + 1) * ZOOM, counter * ZOOM, create_trgb(1, 255, 255, 255));
			}
		}
	}
}
