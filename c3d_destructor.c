/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:50:26 by anruland          #+#    #+#             */
/*   Updated: 2022/06/27 10:37:46 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * destroys one single pointer
 * @param str [void *] pointer to free
 */
void	c3d_single_desctruct(void *str)
{
	if (str)
		free(str);
	str = NULL;
}

/**
 * frees a pointer to pointer
 * @param argv [char **] pointer to pointer to free
 */
void	c3d_free_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		c3d_single_desctruct((void *)argv[i]);
		i++;
	}
	c3d_single_desctruct((void *)argv);
}

void	c3d_pre_destructor(int fd, char *line, char *rd, int error)
{
	if (error == 0)
		return ;
	close(fd);
	c3d_single_desctruct(line);
	c3d_single_desctruct(rd);
	if (error == MAP_INV_CHAR)
		ft_printerror("Error\nInvalid Character in Map");
	else if (error == MAP_WALLS)
		ft_printerror("Error\nMap needs to be enclosed in Walls");
	else if (error == MAP_PLAYER)
		ft_printerror("Error\nInvalid amount of players");
	else if (error == MAP_INVALID)
		ft_printerror("Error\nInvalid map");
	else
		ft_printerror("Error\nUnknown");
}

void	c3d_destructor(t_data *cub)
{
	int	i;

	i = 0;
	c3d_free_array(cub->map.map);
	c3d_single_desctruct(cub->map.path);
	while (i < TEX)
	{
		c3d_single_desctruct(cub->images[i].path);
		i++;
	}
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	mlx_destroy_display(cub->mlx.mlx);
	c3d_single_desctruct(cub->mlx.mlx);
}
