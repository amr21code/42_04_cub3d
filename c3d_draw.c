/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:40:45 by anruland          #+#    #+#             */
/*   Updated: 2022/06/28 13:33:35 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_draw_px(t_image *img, int x, int y, int color)
{
	int		offset;
	char	*px;

	offset = y * img->size_x + x * (img->bpp / 8);
	px = img->data + offset;
	*(unsigned int *)px = color;
}

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
