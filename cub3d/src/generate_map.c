/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:26 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/02/09 00:35:59 by dhomem-d         ###   ########.fr       */
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
static float handle_ninety(float x, float y)
{
	float counter;
	counter = roundf(y) - y < 0 ? 1.0 + (roundf(y) - y) : roundf(y) - y;
	if (cub()->map[(int)y][(int)x] == '1')
		y++;
	printf("%f\n", counter);
	while(cub()->map[(int)y][(int)x] != '1')
		y++, counter++;
	return (counter);
}
static int get_ray_len(float x, float y, float angle)
{
	int	counter;
	int		ray_x;
	int		ray_y;

	counter = 0;
	ray_x = x + counter * cos(angle);
	ray_y = y + counter * sin(angle);
	counter++;
	while (cub()->map[(int)ray_y][(int)ray_x] != '1' && cub()->map[(int)ray_y][(int)ray_x])
	{
		ray_x = x + counter * cos(angle);
		ray_y = y + counter * sin(angle);
		// print_horizontal(cub(), ray_x * 32, ray_y * 32, create_trgb(1, 0, 0, 255));
		counter++;
	}
	printf("%f\n", angle);
	// printf("%i, %i\n", ray_x, ray_y);
	if (angle < (float)1.570794 && angle > (float)-1.570794 )
	{
		float x_len = (float)ray_x - x;
		float y_len = x_len * tan(angle);
		float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
		for (int i = 0; i <= ray_len * 32; i++)
		{
			int	new_x = round(x * 32 + i * cos(angle));
			int new_y = round(y * 32 + i * sin(angle));
			//printf("%i, %f\n", new_x, cub()->player.x * 32);
			mlx_pixel_put(cub()->mlx, cub()->win, new_x, new_y, create_trgb(1, 255, 0, 0));
		}
	}
	else if (angle == (float)1.570794 || angle == (float)-1.570794)
	{
		float ray_len = handle_ninety(cub()->player.x, cub()->player.y);
		for (int i = 0; i <= ray_len * 32; i++)
		{
			int	new_x = round(x * 32 + i * cos(angle));
			int new_y = round(y * 32 + i * sin(angle));
			//printf("%i, %f\n", new_x, cub()->player.x * 32);
			mlx_pixel_put(cub()->mlx, cub()->win, new_x, new_y, create_trgb(1, 255, 0, 0));
		}
	}
	else
	{
		float x_len = x - (float)ray_x - 1;
		float y_len = x_len * tan(angle);
		float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
		for (int i = 0; i <= ray_len * 32; i++)
		{
			int	new_x = round(x * 32 + i * cos(angle));
			int new_y = round(y * 32 + i * sin(angle));
			//printf("%i, %f\n", new_x, cub()->player.x * 32);
			mlx_pixel_put(cub()->mlx, cub()->win, new_x, new_y, create_trgb(1, 255, 0, 0));
		}
	}
	return 1;
}
static void print_ray()
{
	get_ray_len(cub()->player.x, cub()->player.y, cub()->player.angle);
}
static void print_player(t_cub3d *cub3d, float x, float y)
{
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
		cub()->player.angle -= 0.261799;
	else if (keycode == KEY_RIGHT)
		cub()->player.angle += 0.261799;
	else if (keycode == KEY_ESC)
		close_window(1);
	if (cub()->player.angle >= 6.283175 || cub()->player.angle <= -6.283175)
		cub()->player.angle = 0;
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