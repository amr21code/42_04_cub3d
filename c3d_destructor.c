/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:50:26 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 13:06:36 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * destroys one single pointer
 * @param str [void *] pointer to free
 */
void	c3d_single_desctruct(void *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	c3d_pre_destructor(int fd, char *line, char *rd, int error)
{
	if (error == 0)
		return ;
	close(fd);
	c3d_single_desctruct(line);
	c3d_single_desctruct(rd);
	if (error == MAP_INV_CHAR)
		ft_printerror("Error\nInvalid Character in Map");
	else if (error == MAP_WALLS)
		ft_printerror("Error\nMap needs to be enclosed in Walls");
}

