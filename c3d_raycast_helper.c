/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_raycast_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:29:30 by djedasch          #+#    #+#             */
/*   Updated: 2022/07/15 14:12:37 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief calculates step and side
 * 
 * @param ray 
 * @param cub 
 */
void	c3d_calc_steps(t_rays *ray, t_data *cub)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (cub->player.pos.x - ray->pos.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = (ray->pos.x + 1.0 - cub->player.pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (cub->player.pos.y - ray->pos.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = (ray->pos.y + 1.0 - cub->player.pos.y) * ray->delta.y;
	}
}

/**
 * @brief inits ray variables for ray i
 * 
 * @param ray 
 * @param cub 
 * @param i 
 */
void	c3d_init_ray(t_rays *ray, t_data *cub, int i)
{
	ray->hit = 0;
	ray->pos.x = (int)cub->player.pos.x;
	ray->pos.y = (int)cub->player.pos.y;
	ray->cam = 2 * i / (double)cub->mlx.width - 1;
	ray->dir.x = cub->player.view.x + ray->cplane.x * ray->cam;
	ray->dir.y = cub->player.view.y + ray->cplane.y * ray->cam;
	ray->delta.x = c3d_abs(c3d_div(1.0, ray->dir.x));
	ray->delta.y = c3d_abs(c3d_div(1.0, ray->dir.y));
}

/**
 * @brief loops until it hits a wall
 * 
 * @param ray 
 * @param cub 
 */
void	c3d_find_wall(t_rays *ray, t_data *cub)
{
	while (ray->hit == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->pos.x += ray->step.x;
			ray->wallside = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->pos.y += ray->step.y;
			ray->wallside = 1;
		}
		if (cub->map.map[(int)ray->pos.y][(int)ray->pos.x] == '1')
			ray->hit = 1;
		else if (cub->map.map[(int)ray->pos.y][(int)ray->pos.x] == 'D')
			ray->hit = 2;
	}
}

/**
 * @brief checks with wall the ray hit and chooses the correct wall texture
 * 
 * @param ray 
 */
void	c3d_choose_tex(t_rays *ray)
{
	if (ray->wallside == 0)
	{
		ray->dist = (ray->side.x - ray->delta.x);
		ray->wallx = ray->pos.y + ray->dist * ray->dir.y;
		if (ray->dir.x < 0)
			ray->tex_idx = E;
		else
			ray->tex_idx = W;
	}
	else
	{
		ray->dist = (ray->side.y - ray->delta.y);
		ray->wallx = ray->pos.x + ray->dist * ray->dir.x;
		if (ray->dir.y < 0)
			ray->tex_idx = N;
		else
			ray->tex_idx = S;
	}
}
