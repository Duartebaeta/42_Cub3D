#include "cub3d.h"

static int parse_textures(t_data *data)
{
	int		counter;
	char	*line;
	char	**tmp;
	char	textures[4][3] = {"NO\0", "SO\0", "WE\0", "EA\0"};

	counter = 0;
	while (counter < 4 && data->input++)
	{
		line = ft_strtrim(*(data->input), " ");
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		tmp = ft_split(line, ' ');
		if (ft_strncmp(textures[counter], tmp[0], 3) != 0)
		{
			ft_strarray_clear(&tmp);
			return (1);
		}
	}

	return (0);
}

static void	get_input(int fd, t_data *data)
{
	char	*input;
	char	*tmp;
	char	*gnl_tmp;

	input = ft_strdup("");
	gnl_tmp = get_next_line(fd);
	while (gnl_tmp != NULL)
	{
		if (ft_strlen(gnl_tmp) != 0)
		{
			tmp = ft_strjoin(input, gnl_tmp);
			free(input);
			input = ft_strdup(tmp);
			free(tmp);
		}
		free(gnl_tmp);
		gnl_tmp = get_next_line(fd);
	}
	free(gnl_tmp);
	data->input = ft_split(input, '\n');
	free(input);
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
	if (parse_textures(data))
		return (1);
	// for (size_t i = 0; data->map[i]; i++)
	// {
	// 	printf("%s\n", data->map[i]);
	// }
	return 0;
}
