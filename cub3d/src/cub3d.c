#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return (NUM_ARGS);
	data = protected_calloc(1, sizeof(t_data));
	arg_checker(argv[1], data);

	return (EXIT_SUCCESS);
}
