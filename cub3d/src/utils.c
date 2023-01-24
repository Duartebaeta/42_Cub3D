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


// Function to join multiple strings that belong to the same array with a space between them
char	*join_multiples(char **array, int start, int end)
{
	char	*tmp;
	char	*ret;

	if (start > array_len(array))
		return (NULL);
	ret = ft_strdup(array[start]);
	while (++start <= end && array[start])
	{
		tmp = ft_strjoin(ret, array[start]);
		free(ret);
		ret = tmp;
		free(tmp);
		if (start == end || array[start + 1] == NULL)
			continue ;
		tmp = ft_strjoin(ret, " ");
		free(ret);
		ret = tmp;
		free(tmp);
	}
	return (ret);
}