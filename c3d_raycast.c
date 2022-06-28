/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:50:01 by anruland          #+#    #+#             */
/*   Updated: 2022/06/28 14:07:28 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_init_rays(t_rays *ray)
{
	ray->hit = 0;
	ray->ray_len = 0;
	ray->wallh = 0;
}

void	c3d_raycast(t_data *cub)
{
	int		i;
	t_rays	ray;

	i = 0;
	ray.cplane.x = 0;
	ray.cplane.y = 0.66;
	c3d_init_rays(&ray);
	while (i < cub->mlx.width - 1)
	{
		// init start
		ray.pos.x = cub->player.pos.x;
		ray.pos.y = cub->player.pos.y;
		ray.cam = 2 * i / (double)cub->mlx.width - 1;
		ray.dir.x = cub->player.view.x + ray.cplane.x * ray.cam;
		ray.dir.y = cub->player.view.y + ray.cplane.y * ray.cam;
		ray.delta.x = c3d_abs(c3d_div(1.0, ray.dir.x));
		ray.delta.y = c3d_abs(c3d_div(1.0, ray.dir.y));
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.side.x = (cub->player.pos.x - ray.pos.x) * ray.delta.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side.x = (ray.pos.x + 1.0 - cub->player.pos.x) * ray.delta.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.side.y = (cub->player.pos.y - ray.pos.y) * ray.delta.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side.y = (ray.pos.y + 1.0 - cub->player.pos.y) * ray.delta.y;
		}
		// init end
		// algo start
		while (ray.hit == 0)
		{
			if (ray.side.x < ray.side.y)
			{
				ray.side.x += ray.delta.x;
				ray.pos.x += ray.step.x;
				ray.wallside = 0;
			}
			else
			{
				ray.side.y += ray.delta.y;
				ray.pos.y += ray.step.y;
				ray.wallside = 1;
			}
			// printf("i %d - TEST x %f y %f\n", i, ray.pos.x, ray.pos.y);
			if (cub->map.map[(int)ray.pos.y][(int)ray.pos.x] == '1')
				ray.hit = 1;
		}
		printf("i %d TEST side %f, delta %f\n", i, ray.side.y, ray.delta.y);
		printf("i %d TEST side %f, delta %f\n", i, ray.side.x, ray.delta.x);
		if (ray.wallside == 0)
			ray.dist = (ray.side.x - ray.delta.x);
		else
			ray.dist = (ray.side.y - ray.delta.y);
		// algo end
		ray.wallh = c3d_calc_wallheight(cub, ray.dist);
		c3d_draw_col(cub, i, ray.wallh);
		i++;
	}
}

int	c3d_calc_wallheight(t_data *cub, double len_ray)
{
	int	wallh;

	wallh = cub->images[0].size_y / (int)(len_ray * 512);
	return (wallh);
}
