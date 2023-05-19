/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_imgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:31:29 by jocaetan          #+#    #+#             */
/*   Updated: 2023/05/19 23:27:11 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	reset_img2d(void);
static void	reset_img3d(void);

void	draw_imgs(void)
{
	t_cub3d	*cub3d;

	cub3d = cub();
	reset_img2d();
	reset_img3d();
	visualizer(cub());
	if (cub()->minimap)
	{
		print_lines(cub3d);
		print_player(cub3d, cub3d->player.x * ZOOM,
			cub3d->player.y * ZOOM, ZOOM / 2);
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_3d->img, 0, 0);
}

static void	reset_img2d(void)
{
	int		*image;
	int		i;
	t_image	*img_2d;

	img_2d = cub()->img_2d;
	ft_bzero(img_2d->addr, W_2D * H_2D * (img_2d->bpp / 8));
	image = (int *)(img_2d->addr);
	i = 0;
	while (i < H_2D * H_2D)
	{
		if (i % H_2D)
			image[i] = BLACK;
		i++;
	}
}

static void	reset_img3d(void)
{
	int		*image;
	int		i;
	t_image	*img_3d;

	img_3d = cub()->img_3d;
	ft_bzero(img_3d->addr, W_3D * H_3D * (img_3d->bpp / 8));
	image = (int *)(img_3d->addr);
	i = 0;
	while (i < H_3D * H_3D)
	{
		if (i % H_3D)
			image[i] = BLACK;
		i++;
	}
}

void	init_imgs(void)
{
	t_image	*img_2d;
	t_image	*img_3d;

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
	load_textures(cub());
}
