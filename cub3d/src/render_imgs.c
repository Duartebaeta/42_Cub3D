#include "cub3d.h"

static void reset_img2d(void);

void draw_img(void)
{
	t_cub3d *cub3d;

	cub3d = cub();
	reset_img2d();
	print_lines(cub3d);
	print_player(cub3d, cub3d->player.x * 32, cub3d->player.y * 32, 11);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_2d->img, 0, 0);
}

static void reset_img2d(void)
{
	int *image;
	int i;
	t_image *img_2d;

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
