/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:26 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/02/16 19:13:17 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	close_window(int param)
{
	exit(param);
	return (1);
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
	print_player(cub(), cub()->player.x * 32, cub()->player.y * 32, 11);
	return (0);
}

int	generate_map(t_cub3d *cub3d)
{
	int	test;

	test = 1;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, (cub()->map_x + 1) * 32,
			cub()->map_y * 32, "teste");
	mlx_clear_window(cub3d->mlx, cub3d->win);
	print_lines(cub3d);
	print_player(cub3d, cub3d->player.x * 32, cub3d->player.y * 32, 11);
	mlx_key_hook(cub3d->win, keyhook, &cub3d);
	mlx_hook(cub3d->win, 17, 0L, close_window, &test);
	mlx_loop(cub3d->mlx);
	return (1);
}
