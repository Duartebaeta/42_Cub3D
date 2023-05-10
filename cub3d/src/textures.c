/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:16:39 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/11 00:05:02 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	load_textures(void)
{
	void	*mlx;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	mlx = cub()->mlx;
	no = cub()->no.addr;
	so = cub()->so.addr;
	we = cub()->we.addr;
	ea = cub()->ea.addr;
	cub()->no.img = mlx_xpm_file_to_image(mlx, no, &cub()->no.w, &cub()->no.h);
	cub()->so.img = mlx_xpm_file_to_image(mlx, so, &cub()->so.w, &cub()->so.h);
	cub()->we.img = mlx_xpm_file_to_image(mlx, we, &cub()->we.w, &cub()->we.h);
	cub()->ea.img = mlx_xpm_file_to_image(mlx, ea, &cub()->ea.w, &cub()->ea.h);
}
