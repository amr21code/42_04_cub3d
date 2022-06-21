/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:11 by anruland          #+#    #+#             */
/*   Updated: 2022/06/21 17:00:32 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_pre_error_check(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		ft_printerror("Error\nInvalid Arguments - Usage: ./cub3d map-path");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printerror("Error\nFile not found");
	}
	if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
		ft_printerror("Error\nNot a .cub map");
	close(fd);
}

void	c3d_check_config_elem(char *path)
{
	int			fd;
	char		*rd;
	t_preerr	check;

	rd = NULL;
	c3d_init_preerr(&check);
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		if (!c3d_check_config_elem_line(rd, &check, fd))
		{
			c3d_single_desctruct(rd);
			break ;
		}
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
	c3d_errors_config_elem(check);
}
