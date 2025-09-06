#include "so_long.h"
void	init_struct(char *file, t_map *map)
{
	map->fd = -1;
	map->row = 0;
	map->grid = NULL;
	map->playerx = -1;
    map->playery = -1;
	map->file_name = file;
}
void init_game(t_game *game)
{
    game->image = NULL;
    game->texture = NULL;
}
int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}