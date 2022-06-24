/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:21:32 by anruland          #+#    #+#             */
/*   Updated: 2022/06/24 10:53:48 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*cub;

	c3d_pre_error_check(ac, av);
	c3d_check_map(c3d_check_config_elem(av[1]), av[1]);
	cub = (t_data *)malloc(sizeof(t_data));
	c3d_init_cub(cub, av[1]);
}
