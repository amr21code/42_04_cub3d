/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:50:26 by anruland          #+#    #+#             */
/*   Updated: 2022/06/22 16:35:39 by djedasch         ###   ########.fr       */
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
		ft_printerror("Error\nMap needs to be enclose in Walls");
}
