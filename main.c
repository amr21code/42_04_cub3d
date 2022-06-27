/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:21:32 by anruland          #+#    #+#             */
/*   Updated: 2022/06/27 11:16:17 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*cub;

	c3d_pre_error_check(ac, av);
	c3d_check_map(c3d_check_config_elem(av[1]), av[1]);
	cub = (t_data *)malloc(sizeof(t_data));
	if (!cub)
		ft_printerror("Error\nMalloc of Cub struct failed\n");
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
	{
		c3d_single_desctruct(cub);
		ft_printerror("Error\nMLX init failed\n");
	}
	c3d_init_cub(cub, av[1]);
	c3d_load_tex(cub);
	c3d_init_win(cub);
	// mlx_key_hook(cub->mlx.win, sl_input, &cub);
	mlx_hook(cub->mlx.win, 17, 0, c3d_destructor, cub);
	mlx_loop(cub->mlx.mlx);
}
