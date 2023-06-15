/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:28:50 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/15 16:56:15 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/incl/libft.h"
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
# define KEY_M 109
# define KEY_LEFT 65361
# define KEY_UP 38
# define KEY_RIGHT 65363
# define KEY_DOWN 40
# define KEY_SHIFT 65505

/* MAPS SIZES */
# define W_2D 1280
# define H_2D 720
# define W_3D 1600
# define H_3D 1080
# define ZOOM 16

/* COLOURS */
# define BLACK 0x000000

/* CUB3D CONSTANTS */
# define FOV 60.0		// Field of view in degrees
# define PPW 320		// Projection Plane Width
# define PPH 200		// Projection Plane Heigth
# define PPD 277		// Projection Plane Distance
# define PHEIGHT 32		// Player Heigth
# define TILESIZE 32	// Size of Walls, Floors, Ceilings

# ifndef PI
#  define PI  3.141592999999999857863031138549558818340301513671875
# endif

# ifndef PII
#  define PII 6.283184999999999575948095298372209072113037109375
# endif

# ifndef PI3
#  define PI3 4.7123889923095703125
# endif

# ifndef PI2
#  define PI2 1.570796000000000081087137004942633211612701416015625
# endif

typedef struct s_movement
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	right;
	int	left;
	int	sprint;
}	t_movement;

typedef struct s_point
{
	int		x;
	int		y;
	float	player_dist;
}	t_point;

typedef struct s_dpoint
{
	double	x;
	double	y;
	double	player_dist;
}	t_dpoint;

typedef struct s_player
{
	double	x;
	double	y;
	double	map_x;
	double	map_y;
	double	angle;
}	t_player;

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
	bool	end;
	int		color;
}	t_coord;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		map_start_x;
	int		map_start_y;
	int		shift_x;
	int		shift_y;
	int		palette;
	int		projection;
	int		zoom;
	double	z_zoom;
	double	angle;
}	t_image;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	char	*data;
	t_image	img_data;
	int		fd;
	int		w;
	int		h;
}	t_texture;

typedef struct s_ray
{
	double	x_coord;
	double	y_coord;
	double	angle;
	float	step_x;
	float	step_y;
	float	dist;
	int		vert;
	bool	right;
	bool	up;
	bool	hit;
	int		color;
	char	cardinal;
	float	y_dist;
	float	x_dist;
	float	calc_dist;
}	t_ray;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	int			fd;
	int			map_x;
	int			map_y;
	char		*filename;
	char		**file;
	char		**map;
	t_image		*img_2d;
	t_image		*img_3d;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	int			floor[3];
	int			ceiling[3];
	t_player	player;
	int			onx;
	t_ray		ray;
	bool		minimap;
	t_movement	movement;
}	t_cub3d;

int		arg_checker(char *filename);
void	create_map_from_file(t_cub3d *cub3d);
void	check_map(void);
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
int		is_up(float angle);
int		is_right(float angle);
void	init_imgs(void);
void	set_cardinal(float angle);
float	norm_angle(float angle);
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
void	raycast(float x, float y, float angle, t_cub3d *cub3d);
void	init_ray(t_cub3d *cub3d, float angle);
/* 3D VISUALIZING */
void	visualizer(t_cub3d *cub3d);
void	print_minimap(float angle);
/* MOVEMENT */
void	move(double relative_angle);
/* TEXTURES */
void	load_textures(t_cub3d *cub3d);
void	draw_wall_texture(double low_y, double hi_y, int i);

#endif
