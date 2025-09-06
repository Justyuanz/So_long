#include "so_long.h"

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
	resize_image(game);
	return (true);
}
static void resize_image(t_game *game)
{
	mlx_delete_texture(game->texture->floor);
	mlx_delete_texture(game->texture->wall);
	mlx_delete_texture(game->texture->player);
	mlx_delete_texture(game->texture->collectable);
	mlx_delete_texture(game->texture->exit);
	free(game->texture);
    game->texture = NULL;
	mlx_resize_image(game->image->floor, TILE, TILE);
	mlx_resize_image(game->image->wall, TILE, TILE);
	mlx_resize_image(game->image->player, TILE, TILE);
	mlx_resize_image(game->image->collectable, TILE * 0.8, TILE * 0.8);
	mlx_resize_image(game->image->exit, TILE, TILE);
	
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
}
void render_game(t_game *game)
{
	init_game(game);
	if (!game)
	{
		free_game(&game);
		exit_with_msg("Error init game\n");
	}
	if (!load_texture(game))
	{
		free_game(&game);
		exit_with_msg("Error load textures\n");
	}
	draw_map(game);
	mlx_key_hook(game->mlx, &key_hook, game);
}
