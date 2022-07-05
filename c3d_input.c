/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:49:15 by anruland          #+#    #+#             */
/*   Updated: 2022/07/05 18:54:24 by anruland         ###   ########.fr       */
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
		c3d_move(cub, cub->player.view.y * -1, cub->player.view.x * -1);
	else if (keycode == KEY_S)
		c3d_move(cub, cub->player.view.x * -1, cub->player.view.y * -1);
	else if (keycode == KEY_D)
		c3d_move(cub, cub->player.view.y, cub->player.view.x);
	else if (keycode == KEY_ARR_LEFT)
		c3d_turn(cub, 1);
	else if (keycode == KEY_ARR_RIGHT)
		c3d_turn(cub, -1);
	c3d_draw_square(cub);
	c3d_raycast(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, \
		cub->images[5].img, 0, 0);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, \
		cub->images[6].img, 0, 0);
	return (0);
}

void	c3d_move(t_data *cub, int x, int y)
{
	if (c3d_check_move(cub, x, y))
	{
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
	printf("V X %f, Y %f\n", cub->player.view.x, cub->player.view.y);
}

int	c3d_check_move(t_data *cub, int x, int y)
{
	if (cub->map.map[(int)cub->player.pos.y + y] \
		[(int)cub->player.pos.x + x] != '1'
		&& cub->map.map[(int)cub->player.pos.y + y] \
		[(int)cub->player.pos.x + x] != 'D')
		return (1);
	return (0);
}
