/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:26 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/02/01 19:29:21 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
static void print_square(t_cub3d *cub3d, int x, int y, int color)
{
	int counter;

	counter = -1;
	while (++counter < 32)
		print_horizontal(cub3d, x, y + counter, color);
}
static int get_ray_len(int x, int y, double angle)
{
	int	counter;
	float	ray_x;
	float	ray_y;

	counter = 0;
	ray_x = x + counter * cos(angle);
	ray_y = y + counter * sin(angle);
	counter++;
	while (cub()->map[(int)ray_y][(int)ray_x] != '1' && cub()->map[(int)ray_y][(int)ray_x])
	{
		printf("%c\n, %f, %f\n", cub()->map[(int)ray_y][(int)ray_x], ray_x, ray_y);
		ray_x = x + counter * cos(angle);
		ray_y = y + counter * sin(angle);
		counter++;
	}
	printf("OUT:: %c\n, %f, %f\n", cub()->map[(int)ray_y][(int)ray_x], ray_x, ray_y);
	return (counter);
}
static void print_ray()
{
	int	len = get_ray_len(cub()->player.x, cub()->player.y, cub()->player.angle);
	printf("LEN:: %i\n", len);
	
	int	counter = -1;
	double	ray_x;
	double	ray_y;

	while (++counter < len)
	{
		ray_x = ((cub()->player.x * 32) + counter * (cos(cub()->player.angle)) * 4) + counter;
		ray_y = ((cub()->player.y * 32) + counter * (sin(cub()->player.angle) * 4)) + counter;
		mlx_pixel_put(cub()->mlx, cub()->win, ray_x, ray_y, create_trgb(1, 255, 0, 0));
	}
}
static void print_player(t_cub3d *cub3d, float x, float y)
{
	// int counter;
	// int	sub;

	// counter = 8;
	// while (++counter < 24)
	// {
	// 	sub = 8;
	// 	while (++sub < 24)
	// 		mlx_pixel_put(cub3d->mlx, cub3d->win, x + sub, y + counter, create_trgb(1, 70, 120 , 20));
	// }
	static const double PI = 3.1415926535;
	double i, angle, x1, y1;

	for(i = 0; i < 360; i += 0.1)
	{
		angle = i;
		int r = 11;
		while (--r)
		{
			x1 = r * cos(angle * PI / 180);
			y1 = r * sin(angle * PI / 180);
			mlx_pixel_put(cub3d->mlx, cub3d->win, x + x1, y + y1, create_trgb(1, 70, 120 , 20));
		}
	}
	print_ray();
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
					print_square(cub3d, sub * 32, counter * 32, create_trgb(1, 255, 255, 255));
				else
					print_square(cub3d, sub * 32, counter * 32, create_trgb(1, 0, 0, 0));
				print_horizontal(cub3d, sub * 32, counter * 32, create_trgb(1, 255, 255, 255));
				print_horizontal(cub3d, sub * 32, (counter + 1) * 32, create_trgb(1, 255, 255, 255));
				print_vertical(cub3d, sub * 32, counter * 32, create_trgb(1, 255, 255, 255));
				print_vertical(cub3d, (sub + 1) * 32, counter * 32, create_trgb(1, 255, 255, 255));
			}
		}
	}
}

int	keyhook(int keycode, t_cub3d *cub3d)
{
	(void)cub3d;
	if (keycode == KEY_W)
		cub()->player.y -= 0.25;
	else if (keycode == KEY_A)
		cub()->player.x -= 0.25;
	else if (keycode == KEY_S)
		cub()->player.y += 0.25;
	else if (keycode == KEY_D)
		cub()->player.x += 0.25;
	else if (keycode == KEY_LEFT)
		cub()->player.angle += 0.25;
	else if (keycode == KEY_RIGHT)
		cub()->player.angle -= 0.25;
	else if (keycode == KEY_ESC)
		close_window(1);
	print_lines(cub());
	print_player(cub(), cub()->player.x * 32, cub()->player.y * 32);
	return (0);
}

int	generate_map(t_cub3d *cub3d)
{
	int test = 1;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub()->map_x * 32, cub()->map_y * 32, "teste");
	mlx_clear_window(cub3d->mlx, cub3d->win);
	print_lines(cub3d);
	print_player(cub3d, cub3d->player.x * 32, cub3d->player.y * 32);
	mlx_key_hook(cub3d->win, keyhook, &cub3d);
	mlx_hook(cub3d->win, 17, 0L, close_window, &test);
	mlx_loop(cub3d->mlx);
	return 1;
}