#include "cub3d.h"

char **create_map_from_file(char **file)
{
	char	**map;

	map = ft_strarray_dup(&file[6]);
	for (size_t i = 0; map[i]; i++)
	{
		printf("%s\n", map[i]);
}
	return (map);
}
