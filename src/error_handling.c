#include "so_long.h"

void exit_with_msg(char *msg)
{	
	if(msg)
		ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void free_map_and_exit(t_map *map, char *msg)
{
	if(map->grid)
		free_2d_arr(map->grid);
	exit_with_msg(msg);
}
void free_game()
{

}