#include "so_long.h"
void	init_struct(t_so_long *map)
{
	map->fd = -1;
}
int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}