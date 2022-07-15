/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:31:30 by anruland          #+#    #+#             */
/*   Updated: 2022/07/15 14:47:39 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief draws one point of the minimap
 * 
 * @param cub 
 * @param y 
 * @param x 
 */
void	c3d_draw_minimap_dot(t_data *cub, int y, int x, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c3d_draw_px(&cub->images[6], j + x, i + y, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief inits the minimap image
 * 
 * @param cub 
 */
void	c3d_init_minimap(t_data *cub)
{
	cub->images[6].img = mlx_new_image(cub->mlx.mlx, \
		cub->map.size_x * 4, cub->map.size_y * 4);
	cub->images[6].data = mlx_get_data_addr(cub->images[6].img, \
		&cub->images[6].bpp, &cub->images[6].size_x, &cub->images[6].endian);
	c3d_draw_map(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, \
		cub->images[6].img, 0, 0);
}

/**
 * @brief draws the minimap
 * 
 * @param cub 
 */
void	c3d_draw_map(t_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map.map[i])
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == '1')
			{
				c3d_draw_minimap_dot(cub, i * 4, j * 4, 0xFFAAAAAA);
			}
			else if (cub->map.map[i][j] == 'P' || cub->map.map[i][j] == 'b')
			{
				c3d_draw_minimap_dot(cub, i * 4, j * 4, 0xFFFF0000);
			}
			else
				c3d_draw_minimap_dot(cub, i * 4, j * 4, 0xFF000000);
			j++;
		}
		i++;
	}
}
