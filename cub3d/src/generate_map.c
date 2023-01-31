/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:26 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/01/31 21:50:13 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int close_window(int param)
{
	exit(param);
	return 1;
}

static void print_horizontal(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while(++counter < 32)
		mlx_pixel_put(cub3d->mlx, cub3d->win, x + counter, y, color);
}
static void print_vertical(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while(++counter < 32)
		mlx_pixel_put(cub3d->mlx, cub3d->win, x, y + counter, color);
}
static void print_square(t_cub3d *cub3d, int x, int y)
{
	int counter;

	counter = -1;
	while (++counter < 32)
		print_horizontal(cub3d, x, y + counter, 0xFFFFF);
}
static void print_player(t_cub3d *cub3d, int x, int y)
{
	int counter;

	counter = -1;
	while (++counter < 32)
		print_horizontal(cub3d, x, y + counter, 0x99999999);
}

static void print_lines(t_cub3d *cub3d)
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
					print_square(cub3d, sub * 32, counter * 32);
				print_horizontal(cub3d, sub * 32, counter * 32, 0xFFFFF);
				print_horizontal(cub3d, sub * 32, (counter + 1) * 32, 0xFFFFF);
				print_vertical(cub3d, sub * 32, counter * 32, 0xFFFFF);
				print_vertical(cub3d, (sub + 1) * 32, counter * 32, 0xFFFFF);
			}
			if (cub3d->map[counter][sub] == 'N')
			{
				printf("was here");
				print_player(cub3d, sub * 32, counter * 32);
				print_horizontal(cub3d, sub * 32, counter * 32, 0xFFFFF);
				print_horizontal(cub3d, sub * 32, (counter + 1) * 32, 0xFFFFF);
				print_vertical(cub3d, sub * 32, counter * 32, 0xFFFFF);
				print_vertical(cub3d, (sub + 1) * 32, counter * 32, 0xFFFFF);
			}
		}
	}
}

int	generate_map(t_cub3d *cub3d)
{
	int test = 1;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub()->map_x * 32, cub()->map_y * 32, "teste");
	mlx_hook(cub3d->win, 17, 0L, close_window, &test);
	print_lines(cub3d);
	mlx_loop(cub3d->mlx);
	return 1;
}