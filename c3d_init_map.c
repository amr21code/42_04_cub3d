/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_init_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:57:53 by anruland          #+#    #+#             */
/*   Updated: 2022/07/07 14:56:26 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief saves one line of the map and the player position in the struct 
 *  
 * @param cub 
 * @param line 
 * @param y 
 */
void	c3d_save_map(t_data *cub, char *line, int y)
{
	int		i;

	i = 0;
	cub->map.map[y] = (char *)ft_calloc(cub->map.size_x + 1, sizeof(char));
	while (line[i])
	{
		if (line[i] != '\n')
			cub->map.map[y][i] = line[i];
		if (!ft_char_in_str(" 01D\n", line[i]))
		{
			cub->player.pos.x = i + 0.5;
			cub->player.pos.y = y + 0.5;
			if (line[i] == 'E')
				cub->player.view.x = 1;
			else if (line[i] == 'W')
				cub->player.view.x = -1;
			else if (line[i] == 'N')
				cub->player.view.y = -1;
			else if (line[i] == 'S')
				cub->player.view.y = 1;
		}
		i++;
	}
}

/**
 * @brief inits and allocates map
 * 
 * @param cub 
 * @param path 
 */
void	c3d_init_map(t_data *cub, char *path)
{
	int		fd;
	char	*rd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	rd = NULL;
	cub->map.map = (char **)ft_calloc(cub->map.size_y + 1, sizeof(char *));
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		tmp = skip_whitespaces(rd);
		if (*tmp == '1')
		{
			c3d_save_map(cub, rd, i);
			i++;
		}
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
}
