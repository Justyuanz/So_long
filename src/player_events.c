#include"so_long.h"

void collect_item(t_game *game, int dest_y, int dest_x)
{
	size_t	i;

	i = 0;
	while ( i < game->collectable_count)
	{
		if (game->image->collectable->instances[i].x == dest_x * TILE &&
			game->image->collectable->instances[i].y == dest_y * TILE)
			{
				if (game->image->collectable->instances[i].enabled == true)
					game->map->collectable--;
				game->image->collectable->instances[i].enabled = false;
				break;
			}
		i++;
	}

}

void move_player(t_game *game, int dest_x, int dest_y)
{
	char	position;

	position = game->map->grid[dest_y][dest_x];
	if (position == '1')
		return;
	game->map->playerx = dest_x;
	game->map->playery = dest_y;
	game->image->player->instances[0].x = dest_x * TILE;
	game->image->player->instances[0].y = dest_y * TILE;
	//add move count
	if (position == 'C')
		collect_item(game, dest_y, dest_x);
	if (game->map->collectable == 0)
		game->image->exit->instances[0].enabled = true;
	if (game->map->collectable == 0 && position == 'E')
		mlx_close_window(game->mlx);
}
