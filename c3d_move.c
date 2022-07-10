/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:03:23 by anruland          #+#    #+#             */
/*   Updated: 2022/07/10 17:04:42 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_minimap_move(t_data *cub, double x, double y)
{
	int	prev_x;
	int	prev_y;

	prev_x = (int)cub->player.pos.x;
	prev_y = (int)cub->player.pos.y;
	cub->map.map[prev_y][prev_x] = '0';
	cub->map.map[(int)(cub->player.pos.y + y)] \
		[(int)(cub->player.pos.x + x)] = 'P';
	c3d_draw_map(cub);
}

void	c3d_move(t_data *cub, double x, double y)
{
	int	check;

	x = x * cub->player.step;
	y = y * cub->player.step;
	check = c3d_check_move(cub, x, y);
	if (check == 1 || check == 3)
	{
		c3d_minimap_move(cub, x, y);
		cub->player.pos.x += x;
		cub->player.pos.y += y;
	}
}

void	c3d_turn(t_data *cub, double deg)
{
	double	prev;

	prev = cub->player.view.x;
	cub->player.view.x = cub->player.view.y * -1 * deg;
	cub->player.view.y = prev * deg;
}

int	c3d_check_move(t_data *cub, double x, double y)
{
	if (cub->map.map[(int)(cub->player.pos.y + y)] \
		[(int)(cub->player.pos.x + x)] == '1')
		return (0);
	else if (cub->map.map[(int)(cub->player.pos.y + y)] \
		[(int)(cub->player.pos.x + x)] == 'D')
		return (2);
	else if (cub->map.map[(int)(cub->player.pos.y + y)] \
		[(int)(cub->player.pos.x + x)] == 'd')
		return (3);
	return (1);
}
