#include "so_long.h"

static void validate_file_and_open(char *file_name, t_so_long *map)
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
static void read_map(t_so_long *map)
{
	int	i;

	i = 0;
	map->line = "aa";
	while (map->line != NULL)
	{
		map->line = get_next_line(map->fd);
		printf("%s\n", map->line);
		free(map->line);
		i++;
	}
}

int	main(int argc, char	**argv)
{
	t_so_long map;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		exit (EXIT_FAILURE);
	}
	init_struct(&map);
	validate_file_and_open(argv[1], &map);
	read_map(&map);
	
}

/*need to (read) map content
1:width should be >1
2:flag for each character, at least each of them
3:height > 1

• The map must be rectangular.
• The map must be enclosed/surrounded by walls. If it is not, the program must
return an error.
• You must verify if there is a valid path in the map.
• You must be able to parse any kind of map, as long as it respects the above rules.
• Another example of a minimal .ber map:
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
• If any misconfiguration is encountered in the file, the program must exit cleanly,
and return "Error\n" followed by an explicit error message of your choice.
*/