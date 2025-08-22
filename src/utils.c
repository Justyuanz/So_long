#include "so_long.h"
void	init_struct(t_map *map)
{
	map->fd = -1;
}
int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}