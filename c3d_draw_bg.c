/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw_bg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:24:01 by anruland          #+#    #+#             */
/*   Updated: 2022/06/28 10:40:53 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	c3d_draw_bg(t_data *cub)
{
	cub->images[5].img = mlx_new_image(cub->mlx.mlx, \
		cub->mlx.width, cub->mlx.height);
	cub->images[5].data = mlx_get_data_addr(cub->images[5].img, \
		&cub->images[5].bpp, &cub->images[5].size_x, &cub->images[5].endian);
	c3d_draw_square(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, \
		cub->images[5].img, 0, 0);
}
