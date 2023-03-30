/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:26 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/03/30 23:11:03 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void init_imgs(void);

static int close_window(int param)
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
	draw_imgs();
	visualizer(cub());
	return (0);
}

int	generate_map(t_cub3d *cub3d)
{
	int	test;

	test = 1;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, W_3D, H_3D, "teste");
	mlx_clear_window(cub3d->mlx, cub3d->win);
	init_imgs();
	visualizer(cub());
	draw_imgs();
	mlx_key_hook(cub3d->win, keyhook, &cub3d);
	mlx_hook(cub3d->win, 17, 0L, close_window, &test);
	mlx_loop(cub3d->mlx);
	return (1);
}

static void init_imgs(void)
{
	t_image *img_2d;
	t_image *img_3d;

	img_2d = (t_image *)protected_calloc(sizeof(t_image), 1);
	img_2d->width = W_2D;
	img_2d->height = H_2D;
	img_2d->zoom = ZOOM;
	img_2d->img = mlx_new_image(cub()->mlx, W_2D, H_2D);
	img_2d->addr = mlx_get_data_addr(img_2d->img,
		&img_2d->bpp, &img_2d->line_length, &img_2d->endian);
	img_3d = (t_image *)protected_calloc(sizeof(t_image), 1);
	img_3d->width = W_3D;
	img_3d->height = H_3D;
	img_3d->img = mlx_new_image(cub()->mlx, W_3D, H_3D);
	img_3d->addr = mlx_get_data_addr(img_3d->img,
		&img_3d->bpp, &img_3d->line_length, &img_3d->endian);
	cub()->img_2d = img_2d;
	cub()->img_3d = img_3d;
}
