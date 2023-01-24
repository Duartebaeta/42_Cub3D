#include "cub3d.h"

void *protected_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		program_errors("MALLOC", true, true);
	return (ptr);
}

int	array_len(char **array)
{
	int	counter;

	counter = 0;
	while (array[counter] != NULL)
		counter++;
	return (counter);
}