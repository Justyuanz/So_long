#include "so_long.h"

static void validate_file_and_open(char *file_name, t_map *map)
{
	int	len;

	if (!file_name || file_name[1] == '\0')
		exit (EXIT_FAILURE);
	len = ft_strlen(file_name);
	if (file_name[len - 4] != '.' || file_name[len - 3] != 'b'
	|| file_name[len - 2] != 'e' || file_name[len - 1] != 'r')
		exit(EXIT_FAILURE);
	map->fd = open(file_name, O_RDONLY);
	if (map->fd == -1)
	{
		perror(file_name);
		exit(EXIT_FAILURE);
	}
}
char	*strjoin_solong(char *pre_line, char *line)
{
	int		i;
	int		j;
	int		len;
	char	*str;
	if (!pre_line)
		i = 0;
	else
		i = gnl_strlen(pre_line);
	len = gnl_strlen(line);
	str = malloc((i + len + 1) * sizeof(char));
	if (!str)
	{
		free(pre_line);
		return (NULL);
	}
	j = -1;
	while (++j < i)
		str[j] = pre_line[j];
	j = 0;
	while (j < len)
		str[i++] = line[j++];
	str[i] = '\0';
	free(pre_line);
	pre_line = NULL;
	return (str);
}

static void read_and_append_map(t_map *map) //NULL GUARD FOR WHILE LOOP
{
	int	i;

	i = 0;
	map->line = "a";
	while (map->line)
	{
		map->line = get_next_line(map->fd);
		//check length;
		//count 
		free(map->line);
		i++;
	}
	fprintf(stderr, "%s\n", map->append_line);
	free(map->append_line);
}

int	main(int argc, char	**argv)
{
	t_map map;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		exit (EXIT_FAILURE);
	}
	init_struct(&map);
	validate_file_and_open(argv[1], &map);
	read_and_append_map(&map); //now i read map and get the line of characters with '\n'
}
