/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:49:15 by anruland          #+#    #+#             */
/*   Updated: 2022/07/18 14:40:29 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_input(int keycode, t_data *cub)
{
	if (keycode == KEY_ESCAPE)
		c3d_destructor(cub);
	else if (keycode == KEY_W)
		c3d_move(cub, cub->player.view.x, cub->player.view.y);
	else if (keycode == KEY_A)
		c3d_move(cub, cub->player.view.y, cub->player.view.x * -1);
	else if (keycode == KEY_S)
		c3d_move(cub, cub->player.view.x * -1, cub->player.view.y * -1);
	else if (keycode == KEY_D)
		c3d_move(cub, cub->player.view.y * -1, cub->player.view.x);
	else if (keycode == KEY_ARR_LEFT)
		c3d_turn(cub, 10);
	else if (keycode == KEY_ARR_RIGHT)
		c3d_turn(cub, -10);
	else if (keycode == SPACE)
		c3d_open_door(cub);
	c3d_draw_square(cub);
	c3d_raycast(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, \
		cub->images[TEX - 2].img, 0, 0);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, \
		cub->images[TEX - 1].img, 0, 0);
	return (0);
}

void	c3d_open_door(t_data *cub)
{
	if (c3d_check_move(cub, cub->player.view.x, cub->player.view.y) == 2)
		cub->map.map[(int)(cub->player.pos.y + cub->player.view.y)] \
			[(int)(cub->player.pos.x + cub->player.view.x)] = 'd';
	else if (c3d_check_move(cub, cub->player.view.x, cub->player.view.y) == 3)
		cub->map.map[(int)(cub->player.pos.y + cub->player.view.y)] \
			[(int)(cub->player.pos.x + cub->player.view.x)] = 'D';
}
