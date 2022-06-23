/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:06 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 16:28:54 by anruland         ###   ########.fr       */
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
		check->invalid = 1;
}

void	c3d_errors_config_elem(t_preerr check)
{
	if (check.no != 1)
		check.invalid = 1;
	else if (check.ea != 1)
		check.invalid = 1;
	else if (check.so != 1)
		check.invalid = 1;
	else if (check.we != 1)
		check.invalid = 1;
	else if (check.door != 1)
		check.invalid = 1;
	else if (check.f != 1)
		check.invalid = 1;
	else if (check.c != 1)
		check.invalid = 1;
	if (check.invalid != 0)
		ft_printerror("Error\nInvalid config elements");
}

int	c3d_check_config_elem_line(char *rd, t_preerr *check)
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
				return (1);
			else
			{
				check->invalid = 1;
				return (0);
			}
		}
	}
	return (0);
}


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
