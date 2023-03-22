/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:17:59 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/03/22 23:08:41 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void send_rays(float angle);
t_point vertical_intersection(t_ray ray);
t_point horizontal_intersection(t_ray ray);
bool is_angle_up(float angle);
bool is_angle_right(float angle);
float norm_angle(float angle);
bool hit_wall(t_ray ray);
float points_distance(float x1, float y1, float x2, float y2);
t_point find_wall_intersection(t_ray ray);

// static float v_handle_ninety(float x, float y, float angle)
// {
// 	float counter;
// 	if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -270)
// 	{
// 		counter = roundf(y) - y < 0 ? 1.0 + (roundf(y) - y) : roundf(y) - y;
// 		y += counter;
// 		while(cub()->map[(int)y][(int)x] != '1')
// 			y++, counter++;
// 	}
// 	else
// 	{
// 		counter = roundf(y) - y < 0 ? (roundf(y) - y) : 1.0 - (roundf(y) - y);
// 		if (counter < 0)
// 			counter *= -1;
// 		y -= counter;
// 			while(cub()->map[rd(y)][rd(x)] != '1')
// 				y--, counter++;
// 		}
// 		return counter;
// 	}

// 	static float	v_left_ray(int ray_x, int ray_y, float angle)
// 	{
// 		float y_len;
// 		float x_len;
// 		if (!cub()->ray.vert)
// 		{
// 			y_len = cub()->player.y - (float)ray_y - 1;
// 			if (((int)to_deg(angle) < 180 && (int)to_deg(angle) > 90) || (int)to_deg(angle) < -180)
// 			{
// 				y_len++;
// 			}
// 			x_len = y_len / tan(angle);
// 		}
// 		else
// 		{
// 			x_len = cub()->player.x - (float)ray_x - 1;
// 			y_len = x_len * tan(angle);
// 		}
// 		float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
// 		return ray_len;
// 	}

// 	static float	v_right_ray(int ray_x, int ray_y, float angle)
// 	{
// 		float y_len;
// 		float x_len;
// 		if (!cub()->ray.vert)
// 		{
// 			y_len = (float)ray_y - cub()->player.y + 1;
// 			if (((int)to_deg(angle) < 90 && (int)to_deg(angle) > 0) || (int)to_deg(angle) < -270)
// 				y_len--;
// 			x_len = y_len / tan(angle);
// 		}
// 		else
// 		{
// 			x_len = (float)ray_x - cub()->player.x;
// 			y_len = x_len * tan(angle);
// 		}
// 		float ray_len = sqrtf(powf(x_len, 2) + powf(y_len, 2));
// 		return ray_len;
// 	}

// 	float	get_ray_dist(float x, float y, float angle)
// 	{
// 		float	counter;
// 		int		ray_x;
// 		int		ray_y;

// 		counter = 0;
// 		ray_x = rd(x + counter * cos(angle));
// 		ray_y = rd(y + counter * sin(angle));
// 		while (cub()->map[ray_y][ray_x] && cub()->map[ray_y][ray_x] != '1')
// 		{
// 			counter += 0.25;
// 			ray_x = rd(x + counter * cos(angle));
// 			ray_y = rd(y + counter * sin(angle));
// 		}
// 		if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -90 || (int)to_deg(angle) == 270 || (int)to_deg(angle) == -270)
// 			return(v_handle_ninety(x, y, angle));
// 		else if (((int)to_deg(angle) > -90 && (int)to_deg(angle) < 90) || (int)to_deg(angle) < -270 || (int)to_deg(angle) > 270)
// 			return(v_right_ray(ray_x, ray_y, angle));
// 		else
// 			return(v_left_ray(ray_x, ray_y, angle));
// 	}

// 	static float	plane_dist(float ray_len, float angle)
// 	{
// 		float plane;
// 		float new_ang;

// 		if (angle < cub()->player.angle)
// 		{
// 			new_ang = to_radian(to_deg(cub()->player.angle) - 90) + angle;
// 			plane = sin(new_ang) * ray_len;
// 		}
// 		else
// 		{
// 			new_ang = to_radian(to_deg(cub()->player.angle) + 90) - angle;
// 			plane = sin(new_ang) * ray_len;
// 		}
// 		return plane;
// 	}

// 	static void vertical_line(int x, int start, int end, int color)
// 	{
// 		while (start <= end)
// 		{
// 			my_mlx_pixel_put(cub()->img_3d, x, start, color);
// 			start++;
// 		}
// 	}

static void init_ray(t_cub3d *cub3d, float angle)
{
	cub3d->ray.angle = angle;
	cub3d->ray.hit = false;
	cub3d->ray.right = is_right(angle);
	cub3d->ray.up = is_angle_right(angle);
	cub3d->ray.vert = 0;
}

	void visualizer(t_cub3d *cub3d)
	{
		float curr_angle;
		float angle_step;
		int i;

		curr_angle = to_radian(to_deg(cub3d->player.angle) - (FOV / 2));
		angle_step = to_radian(FOV) / W_3D;
		i = -1;
		while (++i < W_3D)
		{
			send_rays(curr_angle);
			curr_angle += angle_step;
		}

	}

	void send_rays(float angle)
	{
		t_point vert_hit;
		t_point horiz_hit;

		init_ray(cub(), angle);
		vert_hit = vertical_intersection(cub()->ray);
		horiz_hit = horizontal_intersection(cub()->ray);
		if (vert_hit.player_dist < horiz_hit.player_dist)
			printf("Point %f\n", vert_hit.player_dist);
		else
			printf("Point %f\n", horiz_hit.player_dist);
	}

	t_point vertical_intersection(t_ray ray)
	{
		ray.x_coord = floor(cub()->player.x / TILESIZE) * TILESIZE;
		if (ray.right)
			ray.x_coord += TILESIZE;
		ray.y_coord = cub()->player.y + (ray.x_coord - cub()->player.x) * tan(ray.angle);
		ray.step_x = TILESIZE;
		if (!ray.right)
			ray.step_x *= -1;
		ray.step_y = TILESIZE * tan(ray.angle);
		if ((ray.up && ray.right) || (!ray.up && !ray.right))
			ray.step_y *= -1;
		return (find_wall_intersection(ray));
	}

	t_point horizontal_intersection(t_ray ray)
	{
		ray.y_coord = floor(cub()->player.y / TILESIZE) * TILESIZE;
		if (!ray.up)
			ray.y_coord += TILESIZE;
		ray.x_coord = cub()->player.x + (ray.y_coord - cub()->player.y) * tan(ray.angle);
		ray.step_y = TILESIZE;
		if (ray.up)
			ray.step_y *= -1;
		ray.step_x = TILESIZE * tan(ray.angle);
		if ((ray.up && ray.right) || (!ray.up && !ray.right))
			ray.step_y *= -1;
		return (find_wall_intersection(ray));
	}

	bool is_angle_up(float angle)
	{
		if (angle >= 0 && angle <= M_PI)
			return (false);
		else
			return (true);
	}

	bool is_angle_right(float angle)
	{
		if (angle >= M_PI_2 && angle <= (3 * M_PI_2))
			return (false);
		else
			return (true);
	}

	float norm_angle(float angle)
	{
		if (angle >= (2 * M_PI))
		angle -= (2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

t_point find_wall_intersection(t_ray ray)
{
	t_point inter;

	while (true)
	{
		if (hit_wall(ray))
			break;
		ray.x_coord += ray.step_x;
		ray.y_coord += ray.step_y;
	}
	inter.x = ray.x_coord;
	inter.y = ray.y_coord;
	inter.player_dist = points_distance(cub()->player.x, cub()->player.y, ray.x_coord, ray.y_coord);
	return (inter);
}

bool hit_wall(t_ray ray)
{
	int map_x;
	int map_y;

	if (ray.x_coord < 0 || ray.y_coord < 0)
		return (true);
	map_x = (int)floor(ray.x_coord / TILESIZE);
	map_y = (int)floor(ray.y_coord / TILESIZE);
	printf("X :%d\t Y: %d\n", map_x, map_y);
	if (map_x >= W_3D || map_y >= H_3D)
		return (true);
	else if (cub ()->map[map_x][map_y] == '1') //TODO: Corrigir heap buffer overflow
	{
		return (true);
	}
	return (false);
}

float points_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(powf((x2 - x1), 2) + powf((y2 - y1), 2)));
}
	// void	visualizer(t_cub3d *cub3d)
	// {
	// 	float min_ang = to_radian(to_deg(cub3d->player.angle) - (FOV / 2));

	// 	for (int x = 0; x < W_3D; x++)
	// 	{
	// 		float ray_angle;
	// 		float ray_dist;
	// 		float camera_dist;

	// 		if (x <= W_3D / 2)
	// 			ray_angle = min_ang + (to_radian((float)(FOV / W_3D) * x));
	// 		else
	// 			ray_angle = cub3d->player.angle + (to_radian((float)(FOV / W_3D) * x));

	// 		ray_dist = cub()->ray.dist;
	// 		camera_dist = plane_dist(ray_dist, ray_angle);

	// 		int lineHeight = (int)(H_3D / camera_dist);
	// 		int drawStart = -lineHeight / 2 + H_3D / 2;
	// 		if(drawStart < 0)drawStart = 0;
	// 		int drawEnd = lineHeight / 2 + H_3D / 2;
	// 		if(drawEnd >= H_3D)drawEnd = H_3D - 1;
	// 		int color = cub()->ray.vert == 0 ? create_trgb(1, 255, 0, 0) : create_trgb(1, 0, 255, 0);
	// 		vertical_line(x, drawStart, drawEnd, color);
	// 	}
	// }
