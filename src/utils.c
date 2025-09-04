#include "so_long.h"
void	init_struct(char *file, t_map *map)
{
	map->fd = -1;
	map->row = 0;
	map->grid = NULL;
	map->file_name = file;
}
int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}