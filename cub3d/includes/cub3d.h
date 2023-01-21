#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include "../libft/libft.h"


typedef struct s_data
{
	char	**map;
}t_data;

int	arg_checker(char *filename, t_data *data);
int	main(int argc, char **argv);
char	*get_next_line(int fd);

#endif