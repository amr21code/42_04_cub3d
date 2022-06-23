/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:06 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 13:22:27 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_count_config_elem(t_preerr *check, char *found)
{
	if (!ft_strncmp(found, "NO ", 3))
		check->no++;
	else if (!ft_strncmp(found, "EA ", 3))
		check->ea++;
	else if (!ft_strncmp(found, "SO ", 3))
		check->so++;
	else if (!ft_strncmp(found, "WE ", 3))
		check->we++;
	else if (!ft_strncmp(found, "DO ", 3))
		check->door++;
	else if (!ft_strncmp(found, "F ", 2))
		check->f++;
	else if (!ft_strncmp(found, "C ", 2))
		check->c++;
	else
		ft_printerror("Error\nInvalid config elements");
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

int	c3d_check_config_elem_line(char *rd, t_preerr *check, int fd)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strlen(rd) > 1)
	{
		while (*rd)
		{
			tmp = skip_whitespaces(rd);
			if (ft_strchr("NSWEDFC", *tmp))
			{
				c3d_count_config_elem(check, tmp);
				break ;
			}
			else if (ft_strchr(tmp, '1'))
				return (0);
			else
			{
				close(fd);
				c3d_single_desctruct(rd);
				ft_printerror("Error\nInvalid config elements 2");
			}
		}
	}
	return (1);
}
