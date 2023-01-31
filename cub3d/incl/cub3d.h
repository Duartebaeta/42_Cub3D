#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>

/* ERROR CODES */
# define NUM_ARGS 2

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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		fd;

}t_texture;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	int			fd;
	int			map_x;
	int			map_y;
	char		*filename;
	char		**input;
	char		**map;
	t_image		*img;
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	int			floor[3];
	int			ceiling[3];

} t_cub3d;

/* FILE PARSING */
int		arg_checker(t_cub3d *cub3d);
int		main(int argc, char **argv);
char	*get_next_line(int fd);
int		check_textures(t_cub3d *cub3d, char *line, int counter);
/* UTILS */
void	*protected_calloc(size_t count, size_t size);
int		array_len(char **array);
t_cub3d	*cub(void);
char	*join_multiples(char **array, int start, int end);
/* ERROR HANDLING */
void program_errors(char *errname, bool clear, bool stop);
void clear_data(void);

#endif
