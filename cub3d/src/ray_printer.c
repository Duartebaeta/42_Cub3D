/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:52:48 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/03/07 21:17:14 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	print_ray(float x, float y, float angle)
{
	float	counter;
	int		ray_x;
	int		ray_y;

	counter = 0;
	ray_x = (int)(rd(x + counter * cos(angle)) - 0.00001);
	ray_y = rd(y + counter * sin(angle));
	while (cub()->map[ray_y][ray_x] && cub()->map[ray_y][ray_x] != '1')
	{
		counter += 0.05;
		ray_x = (int)(rd(x + counter * cos(angle)) - 0.00001);
		ray_y = rd(y + counter * sin(angle));
	}
	// printf("%i, %i\n", ray_x, ray_y);
	if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -90 || (int)to_deg(angle) == 270 || (int)to_deg(angle) == -270)
		handle_ninety(x, y, angle);
	else if (((int)to_deg(angle) > -90 && (int)to_deg(angle) < 90) || (int)to_deg(angle) < -270 || (int)to_deg(angle) > 270)
		right_ray(ray_x, ray_y, angle);
	else
		left_ray(ray_x, ray_y, angle);
}

void	handle_ninety(float x, float y, float angle)
{
	float counter;
	if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -270)
	{
		counter = roundf(y) - y <= 0 ? 1.0 + (roundf(y) - y) : roundf(y) - y;
		y += counter;
		while(cub()->map[(int)y][(int)x] != '1')
			y++, counter++;
		for (int i = cub()->player.y * ZOOM; i <= y * ZOOM; i++)
			my_mlx_pixel_put(cub()->img_2d, x * ZOOM, i, create_trgb(1, 255, 0, 0));

	}
	else
	{
		counter = roundf(y) - y <= 0 ? (roundf(y) - y) : 1.0 - (roundf(y) - y);
		if (counter < 0)
			counter *= -1;
		y -= counter;
		while(cub()->map[rd(y)][rd(x)] != '1')
			y--, counter++;
		y++;
		for (int i = cub()->player.y * ZOOM; i > y * ZOOM; i--)
			my_mlx_pixel_put(cub()->img_2d, x * ZOOM, i, create_trgb(1, 255, 0, 0));
	}
}

void	left_ray(int ray_x, int ray_y, float angle)
{
	float y_len;
	float x_len;
	if (is_onx(ray_x, ray_y, angle))
	{
		y_len = cub()->player.y - (float)ray_y - 1;
		if (((int)to_deg(angle) < 180 && (int)to_deg(angle) > 90) || (int)to_deg(angle) < -180)
			y_len++;
		x_len = y_len / tan(angle);
	}
	else
	{
		x_len = cub()->player.x - (float)ray_x - 1;
		y_len = x_len * tan(angle);
	}
	float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
	for (int i = 0; i <= ray_len * ZOOM; i++)
	{
		int new_x = round(cub()->player.x * ZOOM + i * cos(angle));
		int new_y = round(cub()->player.y * ZOOM + i * sin(angle));
		my_mlx_pixel_put(cub()->img_2d, new_x, new_y, create_trgb(1, 255, 0, 0));
	}
}

void	right_ray(int ray_x, int ray_y, float angle)
{
	float y_len;
	float x_len;
	if (is_onx(ray_x, ray_y, angle))
	{
		y_len = (float)ray_y - cub()->player.y + 1;
		if (((int)to_deg(angle) < 90 && (int)to_deg(angle) > 0) || (int)to_deg(angle) < -270)
			y_len--;
		x_len = y_len / tan(angle);
	}
	else
	{
		x_len = (float)ray_x - cub()->player.x;
		y_len = x_len * tan(angle);
	}
	float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
	for (int i = 0; i <= ray_len * ZOOM; i++)
	{
		int new_x = round(cub()->player.x * ZOOM + i * cos(angle));
		int new_y = round(cub()->player.y * ZOOM + i * sin(angle));
		my_mlx_pixel_put(cub()->img_2d, new_x, new_y, create_trgb(1, 255, 0, 0));
	}
}

static int	lateral_check(int x, int y, float angle)
{
	if (is_right(angle) == 1)
	{
		if (cub()->map[y][x - 1] == '1')
			return 0;
		return 1;
	}
	else
	{
		if (cub()->map[y][x + 1] == '1')
			return 0;
		return 1;
	}
}

int	is_onx(int ray_x, int ray_y, float angle)
{
	int new_angle = (int)to_deg(angle);
	float	counter;
	int		new_x;
	int		new_y;

	counter = 0;
	new_x = rd(cub()->player.x + counter * cos(angle));
	new_y = rd(cub()->player.y + counter * sin(angle));
	counter += 0.05;
	//print_square(cub(), ray_x * 32, ray_y * 32, create_trgb(0.3, 100, 255 ,100));
	if (lateral_check(ray_x, ray_y, angle) == 1)
		return 0;
	while (cub()->map[new_y][new_x] && cub()->map[new_y][new_x] != '1')
	{
		//print_square(cub(), new_x * 32, new_y * 32, create_trgb(1, 100, 100 ,100));
		if ((new_angle >= 0 && new_angle <= 180) || (new_angle <= -180))
		{
			if (new_x == ray_x && new_y == ray_y - 1)
				return 1;
		}
		else
		{
			if (new_x == ray_x && new_y == ray_y + 1)
				return 1;
		}
		new_x = rd(cub()->player.x + counter * cos(angle));
		new_y = rd(cub()->player.y + counter * sin(angle));
		counter += 0.05;
	}
	//print_square(cub(), new_x * 32, new_y * 32, create_trgb(1, 100, 100 ,0));
	return 0;
}
