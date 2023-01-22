#include "cub3d.h"

//ENOENT

static void	get_input(int fd, t_data *data)
{
	char	*map;
	char	*tmp;
	char	*gnl_tmp;

	map = ft_strdup("");
	gnl_tmp = get_next_line(fd);
	while (gnl_tmp != NULL)
	{
		if (ft_strlen(gnl_tmp) != 0)
		{
			tmp = ft_strjoin(map, gnl_tmp);
			free(map);
			map = ft_strdup(tmp);
			free(tmp);
		}
		free(gnl_tmp);
		gnl_tmp = get_next_line(fd);
	}
	free(gnl_tmp);
	data->map = ft_split(map, '\n');
	free(map);
}

int	arg_checker(char *filename, t_data *data)
{
	int	fd;

	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL)
		return (3);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
		{
			printf("Error, %s does not exist.\n", filename);
			return (1);
		}
		return (2);
	}
	get_input(fd, data);
	for (size_t i = 0; data->map[i]; i++)
	{
		printf("%s\n", data->map[i]);
	}
	return 0;
}
