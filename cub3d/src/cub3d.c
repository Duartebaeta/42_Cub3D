#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return 2;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	arg_checker(argv[1], data);

	return 0;
}
