#include "cub3d.h"

int main(int argc, char **argv)
{
	t_cub3d *cub3d;

	if (argc != 2)
		return (NUM_ARGS);
	cub3d = protected_calloc(1, sizeof(t_cub3d));
	cub3d->filename = argv[1];
	printf("%i\n", arg_checker(cub3d));
	printf("Ceiling: %i,%i,%i\n", cub3d->ceiling[0], cub3d->ceiling[1], cub3d->ceiling[2]);
	printf("Floor: %i,%i,%i\n", cub3d->floor[0], cub3d->floor[1], cub3d->floor[2]);
	//free(*(cub3d->input));
	// ft_strarray_clear(&(cub3d->input));
	// free(cub3d);
	return (EXIT_SUCCESS);
}
