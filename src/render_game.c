#include "so_long.h"
//record how many collectible is in the map
//change macro to store floor pixels
//resize according to 64(change tile to 64 too)
//try to draw all the assets correctly

static void load_texture(t_game *game)
{
	game->texture->floor = mlx_load_png("images/floor.png");
	game->image->floor = mlx_texture_to_image(game->mlx, game->texture->floor);
	mlx_resize_image(game->image->floor, TILE, TILE);
	game->texture->wall = mlx_load_png("images/wall.png");
	game->image->wall = mlx_texture_to_image(game->mlx, game->texture->wall);
	mlx_resize_image(game->image->wall, TILE, TILE);
	game->texture->player = mlx_load_png("images/sprite.png");
	game->image->player = mlx_texture_to_image(game->mlx, game->texture->player);
	mlx_resize_image(game->image->player, TILE, TILE);
	game->texture->collectible = mlx_load_png("images/collectable1.png");
	game->image->collectible = mlx_texture_to_image(game->mlx, game->texture->collectible);
	mlx_resize_image(game->image->collectible, TILE * 0.8, TILE * 0.8);
	//and then convert to image and resize
}

void render_game(t_game *game)
{
	int x;
	int y;

	x = 0;
	if (!game)
		return ; //free
	game->texture = ft_calloc(1, sizeof(t_texture *));
	game->image = ft_calloc(1, sizeof(t_image *));

	load_texture(game);
	while(game->map->grid[x] != NULL)
	{
		y = 0;
		while(game->map->grid[x][y] )
		{
			mlx_image_to_window(game->mlx, game->image->floor, y * TILE, x * TILE);
			if(game->map->grid[x][y] == '1')
				mlx_image_to_window(game->mlx, game->image->wall, y * TILE, x * TILE);
			else if(game->map->grid[x][y] == 'P')
				mlx_image_to_window(game->mlx, game->image->player, y * TILE, x * TILE);
			else if(game->map->grid[x][y] == 'C')
				mlx_image_to_window(game->mlx, game->image->collectible, y * TILE, x * TILE);
			y++;
		}
		x++;
	}
	//mlx_key_hook(game->mlx, render_game, void* param);
	mlx_loop(game->mlx);
}