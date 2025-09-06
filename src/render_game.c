#include "so_long.h"
//record how many map->collectable is in the map
//change macro to store floor pixels
//resize according to 64(change tile to 64 too)
//try to draw all the assets correctly

static bool load_texture(t_game *game)
{
	game->texture = ft_calloc(1, sizeof(t_texture));
	game->image = ft_calloc(1, sizeof(t_image));
	if (!game->texture || !game->image)
		return (false);
	game->texture->floor = mlx_load_png("images/floor.png");
	game->texture->wall = mlx_load_png("images/wall.png");
	game->texture->player = mlx_load_png("images/sprite.png");
	game->texture->collectable = mlx_load_png("images/collectable1.png");
	game->texture->exit = mlx_load_png("images/exit.png");
	if (!game->texture->floor || !game->texture->wall ||
		!game->texture->player || !game->texture->collectable || !game->texture->exit)
		return (false);
	game->image->floor = mlx_texture_to_image(game->mlx, game->texture->floor);
	game->image->player = mlx_texture_to_image(game->mlx, game->texture->player);
	game->image->wall = mlx_texture_to_image(game->mlx, game->texture->wall);
	game->image->collectable = mlx_texture_to_image(game->mlx, game->texture->collectable);
	game->image->exit = mlx_texture_to_image(game->mlx, game->texture->exit);
	if (!game->image->floor || !game->image->wall ||
		!game->image->player || !game->image->collectable || !game->image->exit)
		return (false);
	mlx_resize_image(game->image->floor, TILE, TILE);
	mlx_resize_image(game->image->wall, TILE, TILE);
	mlx_resize_image(game->image->player, TILE, TILE);
	mlx_resize_image(game->image->collectable, TILE * 0.8, TILE * 0.8);
	mlx_resize_image(game->image->exit, TILE, TILE);
	return (true);
}
static void draw_map(t_game *game)
{
	int x;
	int y;

	x = 0;
	while(game->map->grid[x] != NULL)
	{
		y = 0;
		while(game->map->grid[x][y] )
		{
			mlx_image_to_window(game->mlx, game->image->floor, y * TILE, x * TILE);
			if(game->map->grid[x][y] == '1')
				mlx_image_to_window(game->mlx, game->image->wall, y * TILE, x * TILE);
			else if(game->map->grid[x][y] == 'C')
				mlx_image_to_window(game->mlx, game->image->collectable, y * TILE, x * TILE);
			else if(game->map->grid[x][y] == 'E')
			{
				mlx_image_to_window(game->mlx, game->image->exit, y * TILE, x * TILE);
				game->image->exit->instances[0].enabled = false;
			}
			y++;
		}
		x++;
	}
	mlx_image_to_window(game->mlx, game->image->player, game->map->playerx * TILE, game->map->playery * TILE);
}
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
	if (position == 'C')
	{
		collect_item(game, dest_y, dest_x);
		printf("c:%zu\n", game->map->collectable);
	}
	if (game->map->collectable == 0)
		game->image->exit->instances[0].enabled = true;
	if (game->map->collectable == 0 && position == 'E')
		mlx_close_window(game->mlx);
	//check x or y and move the instance
	//print and count the move
}
void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;
	int	x;
	int y;

	game = param;
	x = game->map->playerx;
	y = game->map->playery;
	if(keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if(keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(game, x, y - 1);
	else if(keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(game, x, y + 1);
	else if(keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(game, x - 1, y);
	else if(keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(game, x + 1, y);
	x = game->map->playerx;
	y = game->map->playery;
}
void render_game(t_game *game)
{
	init_game(game);
	if (!game)
		return ; //free
	if (!load_texture(game))
		return ; //destroy and exit
	draw_map(game);
	mlx_key_hook(game->mlx, &key_hook, game);
}