#include "cub3d.h"

int main(int argc, char **argv)
{
	t_cub3d *cub3d;

	if (argc != 2)
		return (NUM_ARGS);
	cub3d = protected_calloc(1, sizeof(t_cub3d));
	cub3d->filename = argv[1];
	printf("%i\n", arg_checker(cub3d));
	return (EXIT_SUCCESS);
}
