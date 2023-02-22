#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>
# include <math.h>

/* ERROR CODES */
# define NUM_ARGS 2

/* KEY CODES */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_UP 38
# define KEY_RIGHT 65363
# define KEY_DOWN 40

/* MAPS SIZES */
# define W_2D 1000
# define H_2D 1000
# define W_3D 1000
# define H_3D 1000

/* COLOURS */
#define BLACK 0x000000

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
} t_player;

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
	int width;
	int height;
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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		fd;

}t_texture;

typedef struct s_cub3d
{
	void *mlx;
	void *win;
	int fd;
	int map_x;
	int map_y;
	char *filename;
	char **file;
	char **map;
	t_image *img_2d;
	t_image *img_3d;
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	int		floor[3];
	int		ceiling[3];
	t_player	player;
} t_cub3d;

int		arg_checker(char *filename);
void	create_map_from_file(t_cub3d *cub3d);
void	check_map();
int		main(int argc, char **argv);
char	*get_next_line(int fd);
int		check_textures(t_cub3d *cub3d, char *line, int counter);
/* UTILS */
void	*protected_calloc(size_t count, size_t size);
bool	ft_isspace(int c);
int		array_len(char **array);
int		create_trgb(int t, int r, int g, int b);
float	to_deg(float radian);
int		rd(float n);
float	to_radian(float degree);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	draw_imgs(void);
t_cub3d	*cub(void);
/* ERROR HANDLING */
void	program_errors(char *errname, bool clear, bool stop);
void	clear_data(void);
/*MAP GENERATING*/
int		generate_map(t_cub3d *cub3d);
int		keyhook(int keycode, t_cub3d *cub3d);
void	print_horizontal(t_cub3d *cub3d, int x, int y, int color);
void	print_vertical(t_cub3d *cub3d, int x, int y, int color);
void	print_square(t_cub3d *cub3d, int x, int y, int color);
void	print_player(t_cub3d *cub3d, float x, float y, int r);
void	print_lines(t_cub3d *cub3d);
/*RAYCASTING*/
void	print_ray(float x, float y, float angle);
void	handle_ninety(float x, float y, float angle);
void	left_ray(int ray_x, int ray_y, float angle);
void	right_ray(int ray_x, int ray_y, float angle);
int		is_onx(int ray_x, int ray_y, float angle);

#endif
