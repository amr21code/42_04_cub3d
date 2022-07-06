/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:40:45 by anruland          #+#    #+#             */
/*   Updated: 2022/07/06 16:46:54 by anruland         ###   ########.fr       */
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
void	c3d_draw_col(t_data *cub, int x, int height, t_rays ray)
{
	int				i;
	int				offset;
	unsigned int	color;

	ray.tex_pos = 0.0;
	i = cub->mlx.height / 2 - height / 2;
	while (i < cub->mlx.height / 2 + height / 2)
	{
		ray.tex_y = (int)ray.tex_pos;
		ray.tex_pos += ray.tex_step;
		offset = ray.tex_y * cub->images[ray.tex_idx].line_size \
			+ ray.tex_x * (cub->images[ray.tex_idx].bpp / 8);
		color = *(unsigned int *)(cub->images[ray.tex_idx].data + offset);
		c3d_draw_px(&cub->images[5], x, i, color);
		i++;
	}
}

// /**
//  * @brief draws one colomn
//  * 
//  * @param cub 
//  * @param x 
//  * @param height 
//  */
// void	c3d_draw_col(t_data *cub, int x, int height, t_rays ray)
// {
// 	int	i;

// 	i = cub->mlx.height / 2 - height / 2;
// 	while (i < cub->mlx.height / 2 + height / 2)
// 	{
// 		c3d_draw_px(&cub->images[5], x, i, 0xFF);
// 		i++;
// 	}
// }
