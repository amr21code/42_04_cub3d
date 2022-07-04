/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:40:45 by anruland          #+#    #+#             */
/*   Updated: 2022/07/04 19:09:19 by anruland         ###   ########.fr       */
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
	int		i;
	t_color	cols;
	int		color;

	ray.tex_pos = 0;
	i = cub->mlx.height / 2 - height / 2;
	while (i < cub->mlx.height / 2 + height / 2)
	{
		ray.tex_y = (int)ray.tex_pos;
		ray.tex_pos += ray.tex_step;
		cols.t = cub->images[0].data[((cub->images[0].bpp * cub->images[0].line_size) * ray.tex_y + ray.tex_x)];
		cols.r = cub->images[0].data[((cub->images[0].bpp * cub->images[0].line_size) * ray.tex_y + ray.tex_x) + 1];
		cols.g = cub->images[0].data[((cub->images[0].bpp * cub->images[0].line_size) * ray.tex_y + ray.tex_x) + 2];
		cols.b = cub->images[0].data[((cub->images[0].bpp * cub->images[0].line_size) * ray.tex_y + ray.tex_x) + 3];
		color = c3d_create_trgb(cols.t, cols.r, cols.g, cols.b);
		printf("i %d x %d color %d step %f wallh %d\n", i, x, ray.tex_y, ray.tex_step, ray.wallh);
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
