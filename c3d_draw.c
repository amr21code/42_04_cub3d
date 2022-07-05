/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:40:45 by anruland          #+#    #+#             */
/*   Updated: 2022/07/05 18:19:25 by anruland         ###   ########.fr       */
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
	int		offset;
	char	*px;

	ray.tex_pos = 0.0;
	i = cub->mlx.height / 2 - height / 2;
		// printf("%d\n", cub->images[0].bpp);
	while (i < cub->mlx.height / 2 + height / 2)
	{
		// printf("i %d x %d tex_y %d step %f tex_x %d\n", i, x, ray.tex_y, ray.tex_step, ray.tex_x);
		// printf("wallh %d\n", ray.wallh);
		ray.tex_y = (int)ray.tex_pos;
		ray.tex_pos += ray.tex_step;
		// cols.t = cub->images[0].data[(((cub->images[0].bpp / 8) * cub->images[0].line_size) * ray.tex_y + ray.tex_x * (cub->images[0].bpp / 8))];
		// cols.r = cub->images[0].data[(((cub->images[0].bpp / 8) * cub->images[0].line_size) * ray.tex_y + ray.tex_x * (cub->images[0].bpp / 8)) + 1];
		// cols.g = cub->images[0].data[(((cub->images[0].bpp / 8) * cub->images[0].line_size) * ray.tex_y + ray.tex_x * (cub->images[0].bpp / 8)) + 2];
		// cols.b = cub->images[0].data[(((cub->images[0].bpp / 8) * cub->images[0].line_size) * ray.tex_y + ray.tex_x * (cub->images[0].bpp / 8)) + 3];
		offset = ray.tex_y * cub->images[0].line_size + ray.tex_x * (cub->images[0].bpp / 8);
		px = cub->images[0].data + offset;
		cols.t = px[0];
		cols.r = px[1];
		cols.g = px[2];
		cols.b = px[3];
		// printf("t %d -r %d -g %d -b %d\n", cols.t, cols.r, cols.g, cols.b);
		// printf("t %d -r %d -g %d -b %d\n", px[0], px[1], px[2]);
		color = c3d_create_trgb(cols.t, cols.r, cols.g, cols.b);
		// printf("test %d\n", (((cub->images[0].bpp / 4) * cub->images[0].line_size) * ray.tex_y + ray.tex_x * (cub->images[0].bpp / 4)) + 3);
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
