/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:06 by anruland          #+#    #+#             */
/*   Updated: 2022/06/21 16:11:02 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_count_config_elem(t_preerr *check, char found)
{
	if (found == 'N')
		check->no++;
	else if (found == 'E')
		check->ea++;
	else if (found == 'S')
		check->so++;
	else if (found == 'W')
		check->we++;
	else if (found == 'D')
		check->door++;
	else if (found == 'F')
		check->f++;
	else if (found == 'C')
		check->c++;
}

void	c3d_errors_config_elem(t_preerr check)
{
	if (check.no != 1)
		ft_printerror("Error\nConfig Element \"NO\" invalid");
	else if (check.ea != 1)
		ft_printerror("Error\nConfig Element \"EA\" invalid");
	else if (check.so != 1)
		ft_printerror("Error\nConfig Element \"SO\" invalid");
	else if (check.we != 1)
		ft_printerror("Error\nConfig Element \"WE\" invalid");
	else if (check.door != 1)
		ft_printerror("Error\nConfig Element \"DO\" invalid");
	else if (check.f != 1)
		ft_printerror("Error\nConfig Element \"F\" invalid");
	else if (check.c != 1)
		ft_printerror("Error\nConfig Element \"C\" invalid");
}