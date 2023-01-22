#include "cub3d.h"

void program_errors(char *errname, bool clear, bool stop)
{
	perror(errname);
	if (clear)
		clear_data();
	if (stop)
		exit(EXIT_FAILURE);
}

void clear_data(void)
{
	//TODO: Implement me
}
