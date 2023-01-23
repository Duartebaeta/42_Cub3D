#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>

typedef struct s_data
{
	char **input;
} t_data;

typedef struct s_coord
{
	float x;
	float y;
	float z;
	bool end;
	int color;
} t_coord;

typedef struct s_image
{
	void *img;
	char *addr;
	int bpp;
	int line_length;
	int endian;
	int max_z;
	int min_z;
	int map_start_x;
	int map_start_y;
	int shift_x;
	int shift_y;
	int palette;
	int projection;
	int zoom;
	double z_zoom;
	double angle;
} t_image;

typedef struct s_cub3d
{
	void *mlx;
	void *win;
	int fd;
	int map_x;
	int map_y;
	char *filename;
	t_coord ***map;
	t_image *img;
} t_cub3d;

int		arg_checker(char *filename, t_data *data);
int		main(int argc, char **argv);
char	*get_next_line(int fd);

#endif
