#include "so_long.h"
static void open_map(t_map *map)
{
	map->fd = open(map->file_name, O_RDONLY);
	if (map->fd == -1)
	{
		perror(map->file_name);
		exit(EXIT_FAILURE);
	}
}
static void validate_file(t_map *map)
{
	int	len;

	if (!map->file_name || map->file_name[1] == '\0')
		exit (EXIT_FAILURE);
	len = ft_strlen(map->file_name);
	if (map->file_name[len - 4] != '.' || map->file_name[len - 3] != 'b'
	|| map->file_name[len - 2] != 'e' || map->file_name[len - 1] != 'r')
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

static void count_map_rows(t_map *map) //NULL GUARD FOR WHILE LOOP
{
	open_map(map);
	while (1)
	{
		map->line = get_next_line(map->fd);
		if (!map->line)
			break;
		map->row++;
		free(map->line);
	}
	close(map->fd);
}
static void str_trimming(t_map *map)
{
	size_t x;
	size_t y;
	size_t len;

	x = 0;
	y = 0;
	while (map->grid[x] != NULL)
	{
		len = ft_strlen(map->grid[x] );
		if (len > 0 && map->grid[x][len - 1] == '\n')
			map->grid[x][len - 1] = '\0';
		x++;
	}
}
static void build_map(t_map *map)
{
	size_t	x;

	x = 0;
	map->grid = malloc ((map->row + 1) * sizeof(char *));
	if (!map->grid)
		return ;//change to safe free and exit
	open_map(map);
	while (x < map->row)
	{
		map->grid[x] = get_next_line(map->fd);
		if (!map->grid)
			break;
		x++;
	}
	map->grid[x] = NULL;
	str_trimming(map);
	close(map->fd);
}

int	main(int argc, char	**argv)
{
	t_game	game;
	t_map 	map;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		exit (EXIT_FAILURE);
	}

	init_struct(argv[1], &map);
	validate_file(&map);
	count_map_rows(&map);
	build_map(&map);
	check_map(&map);
	check_path(&map);
	game.map = &map;
	game.mlx = mlx_init(TILE * map.col, TILE * map.row, "SO_LONG", true);
	if(!game.mlx)
	{
		return(EXIT_FAILURE); //FREE
	}
	render_game(&game);
}
