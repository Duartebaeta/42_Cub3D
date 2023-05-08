/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:26 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/08 21:43:29 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	close_window(int param)
{
	exit(param);
	return (1);
}

int	key_press(int keycode, t_cub3d *cub3d)
{
	(void)cub3d;
	if (keycode == KEY_W)
		cub()->movement.w = 1;
	if (keycode == KEY_A)
		cub()->movement.a = 1;
	if (keycode == KEY_S)
		cub()->movement.s = 1;
	if (keycode == KEY_D)
		cub()->movement.d = 1;
	if (keycode == KEY_RIGHT)
		cub()->movement.right = 1;
	if (keycode == KEY_LEFT)
		cub()->movement.left = 1;
	if (keycode == KEY_M)
		cub()->minimap = !cub()->minimap;
	if (keycode == KEY_ESC)
		close_window(1);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub3d)
{
	(void)cub3d;
	if (keycode == KEY_W)
		cub()->movement.w = 0;
	if (keycode == KEY_A)
		cub()->movement.a = 0;
	if (keycode == KEY_S)
		cub()->movement.s = 0;
	if (keycode == KEY_D)
		cub()->movement.d = 0;
	if (keycode == KEY_RIGHT)
		cub()->movement.right = 0;
	if (keycode == KEY_LEFT)
		cub()->movement.left = 0;
	return (0);
}

int	ft_hook(t_cub3d *cub3d)
{
	(void)cub3d;
	if (cub()->movement.w)
		move(0);
	if (cub()->movement.a)
		move(-M_PI_2);
	if (cub()->movement.s)
		move(M_PI);
	if (cub()->movement.d)
		move(M_PI_2);
	if (cub()->movement.left)
		cub()->player.angle -= M_PI / 36;
	if (cub()->movement.right)
		cub()->player.angle += M_PI / 36;
	if (cub()->player.angle >= 2 * M_PI
		|| cub()->player.angle <= -2 * M_PI)
		cub()->player.angle = 0;
	draw_imgs();
	return (0);
}

int	generate_map(t_cub3d *cub3d)
{
	int	test;
	test = 1;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, W_3D, H_3D, "teste");
	cub3d->minimap = false;
	mlx_clear_window(cub3d->mlx, cub3d->win);
	init_imgs();
	visualizer(cub());
	draw_imgs();
	mlx_hook(cub3d->win, 02, 1L << 0, &key_press, &cub3d);
	mlx_hook(cub3d->win, 03, 1L << 1, &key_release, &cub3d);
	mlx_loop_hook(cub3d->mlx, &ft_hook, &cub3d);
	mlx_hook(cub3d->win, 17, 0L, close_window, &test);
	mlx_loop(cub3d->mlx);
	return (1);
}
