/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:50:01 by anruland          #+#    #+#             */
/*   Updated: 2022/07/15 17:55:21 by anruland         ###   ########.fr       */
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

/**
 * @brief raycast algorithm
 * 
 * @param cub 
 */
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
		c3d_init_ray(&ray, cub, i);
		c3d_calc_steps(&ray, cub);
		c3d_find_wall(&ray, cub);
		c3d_choose_tex(&ray, cub);
		if (ray.hit == 2)
			ray.tex_idx = S + ray.hit;
		ray.wallx -= (int)ray.wallx;
		ray.tex_x = (int)(ray.wallx * (double)ray.tex_size);
		if ((ray.wallside == 0 && ray.dir.x > 0)
			|| (ray.wallside == 1 && ray.dir.y < 0))
			ray.tex_x = ray.tex_size - ray.tex_x - 1;
		ray.wallh = c3d_calc_wallheight(cub, ray.dist);
		ray.tex_step = (double)(ray.tex_size / ray.wallh);
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
