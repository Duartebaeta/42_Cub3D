/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:17:59 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/02/27 18:20:46 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static float	v_handle_ninety(float x, float y, float angle)
{
	float counter;
	if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -270)
	{
		counter = roundf(y) - y < 0 ? 1.0 + (roundf(y) - y) : roundf(y) - y;
		y += counter;
		while(cub()->map[(int)y][(int)x] != '1')
			y++, counter++;
	}
	else
	{
		counter = roundf(y) - y < 0 ? (roundf(y) - y) : 1.0 - (roundf(y) - y);
		if (counter < 0)
			counter *= -1;
		y -= counter;
		while(cub()->map[rd(y)][rd(x)] != '1')
			y--, counter++;
	}
	return counter;
}

static float	v_left_ray(int ray_x, int ray_y, float angle)
{
	float y_len;
	float x_len;
	if (is_onx(ray_x, ray_y, angle))
	{
		y_len = cub()->player.y - (float)ray_y - 1;
		if (((int)to_deg(angle) < 180 && (int)to_deg(angle) > 90) || (int)to_deg(angle) < -180)
		{
			y_len++;
		}
		x_len = y_len / tan(angle);
	}
	else
	{
		x_len = cub()->player.x - (float)ray_x - 1;
		y_len = x_len * tan(angle);
	}
	float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
	return ray_len;
}

static float	v_right_ray(int ray_x, int ray_y, float angle)
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
	return ray_len;
}

float	get_ray_dist(float x, float y, float angle)
{
	float	counter;
	int		ray_x;
	int		ray_y;

	counter = 0;
	ray_x = rd(x + counter * cos(angle));
	ray_y = rd(y + counter * sin(angle));
	while (cub()->map[ray_y][ray_x] && cub()->map[ray_y][ray_x] != '1')
	{
		counter += 0.25;
		ray_x = rd(x + counter * cos(angle));
		ray_y = rd(y + counter * sin(angle));
	}
	if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -90 || (int)to_deg(angle) == 270 || (int)to_deg(angle) == -270)
		return(v_handle_ninety(x, y, angle));
	else if (((int)to_deg(angle) > -90 && (int)to_deg(angle) < 90) || (int)to_deg(angle) < -270 || (int)to_deg(angle) > 270)
		return(v_right_ray(ray_x, ray_y, angle));
	else
		return(v_left_ray(ray_x, ray_y, angle));
}

static float	plane_dist(float ray_len, float angle, int x)
{
	float plane;
	float new_ang;

	if (x <= W_3D / 2)
	{
		new_ang = to_radian(to_deg(cub()->player.angle) - 90) + angle;
		plane = sin(new_ang) * ray_len;
	}
	else
	{
		new_ang = to_radian(to_deg(cub()->player.angle) + 90) - angle;
		plane = sin(new_ang) * ray_len;
	}
	return plane;
}

static void vertical(int x, int start, int end, int color)
{
	while (start <= end)
	{
		
	}
}

void	visualizer(t_cub3d *cub3d)
{
	float min_ang = to_radian(to_deg(cub3d->player.angle) - 33);

	for (int x = 0; x < W_3D; x++)
	{
		float ray_angle;
		float ray_dist;
		float camera_dist;

		if (x <= W_3D / 2)
			ray_angle = min_ang + (to_radian((float)(66.0 / W_3D) * x));
		else
			ray_angle = cub3d->player.angle + (to_radian((float)(66.0 / W_3D) * x));

		ray_dist = get_ray_dist(cub3d->player.x, cub3d->player.y, ray_angle);
		camera_dist = plane_dist(ray_dist, ray_angle, x);

		int lineHeight = (int)(H_3D / camera_dist);
		int drawStart = -lineHeight / 2 + H_3D / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + H_3D / 2;
		if(drawEnd >= H_3D)drawEnd = H_3D - 1;
	}
}