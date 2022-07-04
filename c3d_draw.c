/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:40:45 by anruland          #+#    #+#             */
/*   Updated: 2022/07/04 14:01:17 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief draws one pixel
 * 
 * @param img 
 * @param x 
 * @param y 
 * @param color 
 */
void	c3d_draw_px(t_image *img, int x, int y, int color)
{
	int		offset;
	char	*px;

	offset = y * img->size_x + x * (img->bpp / 8);
	px = img->data + offset;
	*(unsigned int *)px = color;
}

/**
 * @brief draws one colomn
 * 
 * @param cub 
 * @param x 
 * @param height 
 */
void	c3d_draw_col(t_data *cub, int x, int height)
{
	int	i;

	i = cub->mlx.height / 2 - height / 2;
	while (i < cub->mlx.height / 2 + height / 2)
	{
		c3d_draw_px(&cub->images[5], x, i, 0xFF);
		i++;
	}
}
