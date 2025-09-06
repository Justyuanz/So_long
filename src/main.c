#include "so_long.h"

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
		free_game(&game);
		exit_with_msg("Error init mlx\n");
	}
	render_game(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	mlx_terminate(game.mlx);
}

