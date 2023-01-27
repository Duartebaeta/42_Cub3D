#include "cub3d.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (NUM_ARGS);
	arg_checker(argv[1]);
	check_map();
	clear_data();
	return (EXIT_SUCCESS);
}
