#include "so_long.h"
static void open_map(t_map *map)
{
	map->fd = open(map->file_name, O_RDONLY);
	if (map->fd == -1)
		exit_with_msg("file open error\n");
}
static void validate_file_name(t_map *map)
{
	int	len;

	if (!map || !map->file_name || map->file_name[1] == '\0')
		exit_with_msg("file does not exist\n");
	len = ft_strlen(map->file_name);
	if (len <= 4 || map->file_name[len - 4] != '.' || map->file_name[len - 3] != 'b'
	|| map->file_name[len - 2] != 'e' || map->file_name[len - 1] != 'r')
		exit_with_msg("not a .ber file\n");
}

static void count_map_rows(t_map *map) //double check if the tmp map->line is fully freed
{
	if (!map)
		exit_with_msg("Error\n");
	open_map(map);
	while (1)
	{
		map->line = get_next_line(map->fd);
		if (!map->line)
			break;
		map->row++;
		free(map->line);
		map->line = NULL;
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
	if (!map || !map->grid)
		exit_with_msg("Error\n");
	while (map->grid[x] != NULL)
	{
		len = ft_strlen(map->grid[x] );
		if (len > 0 && map->grid[x][len - 1] == '\n')
			map->grid[x][len - 1] = '\0';
		x++;
	}
}
static void build_map(t_map *map) //first calloc happened here
{
	size_t	x;

	x = 0;
	map->grid = ft_calloc(map->row + 1, sizeof(char *));
	if (!map->grid)
		exit_with_msg("calloc fails\n");
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
static void map_validation(t_map *map)
{
	validate_file_name(&map);
	count_map_rows(&map);
	build_map(&map);
	check_map(&map);
	check_path(&map);
}
int	main(int argc, char	**argv)
{
	t_game	game;
	t_map 	map;

	if (argc != 2)
		exit_with_msg("Error\n");
	init_struct(argv[1], &map);
	map_validation(&map);
	game.map = &map;
	game.mlx = mlx_init(TILE * map.col, TILE * map.row, "SO_LONG", true);
	if(!game.mlx)
	{
		return(EXIT_FAILURE); //FREE
	}
	render_game(&game);
	mlx_loop(game.mlx);
}
//check all the malloc and 
