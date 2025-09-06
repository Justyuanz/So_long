#include "so_long.h"
//record how many collectable is in the map
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
	if (!game->texture->floor || !game->texture->wall ||
		!game->texture->player || !game->texture->collectable) 
		return (false); 
	game->image->floor = mlx_texture_to_image(game->mlx, game->texture->floor);
	game->image->player = mlx_texture_to_image(game->mlx, game->texture->player);
	game->image->wall = mlx_texture_to_image(game->mlx, game->texture->wall);
	game->image->collectable = mlx_texture_to_image(game->mlx, game->texture->collectable);
	if (!game->image->floor || !game->image->wall ||
		!game->image->player || !game->image->collectable) 
		return (false); 
	mlx_resize_image(game->image->floor, TILE, TILE);
	mlx_resize_image(game->image->wall, TILE, TILE);
	mlx_resize_image(game->image->player, TILE, TILE);
	mlx_resize_image(game->image->collectable, TILE * 0.8, TILE * 0.8);
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
			else if(game->map->grid[x][y] == 'P')
				mlx_image_to_window(game->mlx, game->image->player, y * TILE, x * TILE);
			else if(game->map->grid[x][y] == 'C')
				mlx_image_to_window(game->mlx, game->image->collectable, y * TILE, x * TILE);
			y++;
		}
		x++;
	}	
}
void render_game(t_game *game)
{
	init_game(game);
	if (!game)
		return ; //free
	if (!load_texture(game))
		return ; //destroy and exit
	draw_map(game);
	//mlx_key_hook(game->mlx, render_game, void* param);
	
}