/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:50:01 by anruland          #+#    #+#             */
/*   Updated: 2022/07/07 16:38:08 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief inits ray struct
 * 
 * @param ray 
 */
void	c3d_init_rays(t_rays *ray, t_data *cub)
{
	ray->ray_len = 0;
	ray->wallh = 0;
	ray->texnum = 0;
	ray->tex_size = cub->images[0].size_x;
}

void	c3d_raycast(t_data *cub)
{
	int		i;
	t_rays	ray;

	i = 0;
	ray.cplane.x = 0.66 * cub->player.view.y * -1;
	ray.cplane.y = 0.66 * cub->player.view.x;
	c3d_init_rays(&ray, cub);
	while (i < cub->mlx.width)
	{
		// init start
		ray.hit = 0;
		ray.pos.x = (int)cub->player.pos.x;
		ray.pos.y = (int)cub->player.pos.y;
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
			if (cub->map.map[(int)ray.pos.y][(int)ray.pos.x] == '1')
				ray.hit = 1;
			else if (cub->map.map[(int)ray.pos.y][(int)ray.pos.x] == 'D')
				ray.hit = 2;
		}
		if (ray.wallside == 0)
		{
			ray.dist = (ray.side.x - ray.delta.x);
			ray.wallx = ray.pos.y + ray.dist * ray.dir.y;
			if (ray.dir.x < 0)
				ray.tex_idx = E;
			else
				ray.tex_idx = W;
		}
		else
		{
			ray.dist = (ray.side.y - ray.delta.y);
			ray.wallx = ray.pos.x + ray.dist * ray.dir.x;
			if (ray.dir.y < 0)
				ray.tex_idx = N;
			else
				ray.tex_idx = S;
		}
		if (ray.hit == 2)
			ray.tex_idx = D;
		ray.wallx -= (int)ray.wallx;
		ray.tex_x = (int)(ray.wallx * (double)ray.tex_size);
		if ((ray.wallside == 0 && ray.dir.x > 0)
			|| (ray.wallside == 1 && ray.dir.y < 0))
			ray.tex_x = ray.tex_size - ray.tex_x - 1;
		ray.wallh = c3d_calc_wallheight(cub, ray.dist);
		ray.tex_step = (double)ray.tex_size / ray.wallh;
		// algo end
		c3d_draw_col(cub, i, ray.wallh, ray);
		i++;
	}
}

/**
 * @brief calculates wall height
 * 
 * @param cub 
 * @param len_ray 
 * @return int 
 */
double	c3d_calc_wallheight(t_data *cub, double len_ray)
{
	double	wallh;

	wallh = (cub->mlx.height / len_ray);
	return (wallh);
}
