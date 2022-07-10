/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw_bg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:24:01 by anruland          #+#    #+#             */
/*   Updated: 2022/07/10 17:05:22 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief draws upper half of the window in ceiling color and the
 * lower half in floor color
 * 
 * @param cub 
 */
void	c3d_draw_square(t_data *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->mlx.height / 2)
	{
		j = 0;
		while (j < cub->mlx.width)
		{
			c3d_draw_px(&cub->images[5], j, i, cub->color_ceilling);
			j++;
		}
		i++;
	}
	while (i < cub->mlx.height)
	{
		j = 0;
		while (j < cub->mlx.width)
		{
			c3d_draw_px(&cub->images[5], j, i, cub->color_floor);
			j++;
		}
		i++;
	}
}

/**
 * @brief initialisies the maze images and draws the background
 * 
 * @param cub 
 */
void	c3d_draw_bg(t_data *cub)
{
	cub->images[5].img = mlx_new_image(cub->mlx.mlx, \
		cub->mlx.width, cub->mlx.height);
	cub->images[5].data = mlx_get_data_addr(cub->images[5].img, \
		&cub->images[5].bpp, &cub->images[5].size_x, &cub->images[5].endian);
	c3d_draw_square(cub);
}
