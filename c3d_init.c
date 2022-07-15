/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:11:05 by anruland          #+#    #+#             */
/*   Updated: 2022/07/15 11:41:55 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief inits the preerror struct
 * 
 * @param check 
 */
void	c3d_init_preerr(t_preerr *check)
{
		check->no = 0;
		check->ea = 0;
		check->so = 0;
		check->we = 0;
		check->door_o = 0;
		check->door_c = 0;
		check->f = 0;
		check->c = 0;
		check->invalid = 0;
		check->valid = 0;
		check->start_line = 0;
		check->r = 0;
		check->g = 0;
		check->b = 0;
}

/**
 * @brief inits the cub struct
 * 
 * @param cub 
 */
void	c3d_init_struct(t_data *cub)
{
	cub->color_ceilling = 0;
	cub->color_floor = 0;
	cub->player.pos.x = 0;
	cub->player.pos.y = 0;
	cub->player.view.x = 0;
	cub->player.view.y = 0;
	cub->player.step = 0.2;
	cub->map.size_x = 0;
	cub->map.size_y = 0;
	cub->mlx.width = 1024;
	cub->mlx.height = 768;
}

/**
 * @brief inits cub struct
 * 
 * @param cub 
 * @param path 
 */
void	c3d_init_cub(t_data *cub, char *path)
{
	c3d_init_struct(cub);
	c3d_init_config(cub, path);
	c3d_init_map(cub, path);
}

/**
 * @brief inits config element in cub struct
 * 
 * @param cub 
 * @param path 
 */
void	c3d_init_config(t_data *cub, char *path)
{
	int		fd;
	char	*rd;

	rd = NULL;
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		c3d_init_config_elem(cub, rd);
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
}

/**
 * @brief inits mlx window
 * 
 * @param data 
 */
void	c3d_init_win(t_data *data)
{
	data->mlx.width = 1024;
	data->mlx.height = 768;
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->mlx.width,
			data->mlx.height, "cub3D");
}
