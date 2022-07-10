/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_helper2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:07:02 by anruland          #+#    #+#             */
/*   Updated: 2022/07/10 17:41:41 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_check_colors(char *rd, t_preerr *check, int i)
{
	if (c3d_check_string(&rd[i], "0123456789, \n", 0))
		return (1);
	check->r = ft_atol(&rd[i]);
	c3d_check_between_elem(&rd[i], check->r, check);
	i += ft_strlen_c(&rd[i], ',') + 1;
	check->g = ft_atol(&rd[i]);
	c3d_check_between_elem(&rd[i], check->g, check);
	i += ft_strlen_c(&rd[i], ',') + 1;
	check->b = ft_atol(&rd[i]);
	c3d_check_between_elem(&rd[i], check->b, check);
	if (!(c3d_check_rgb_range(check->r)
			&& c3d_check_rgb_range(check->g)
			&& c3d_check_rgb_range(check->b)))
		return (1);
	return (0);
}

/**
 * @brief checks if path or color is correct
 * 
 * @param rd 
 * @param check 
 */
void	c3d_check_config_elem_details(char *rd, t_preerr *check)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	fd = 0;
	tmp = NULL;
	if (check->invalid != 0)
		return ;
	if (rd[i + 1] && rd[i + 1] == ' ')
		check->invalid = c3d_check_colors(rd, check, ++i);
	else if (ft_char_in_str("NSEWD", rd[i]))
	{
		i += 2;
		tmp = ft_strtrim(&rd[i], " \n");
		fd = open(tmp, O_RDONLY);
		c3d_single_desctruct(tmp);
		if (fd > -1)
			close(fd);
		else
			check->invalid = 1;
	}
	else
		check->invalid = 1;
}

/**
 * @brief checks number and format of config elements of one line
 * 
 * @param rd line that is checked
 * @param check struct in which the number of config elements is counted
 * @return int 
 */
int	c3d_check_config_elem_line(char *rd, t_preerr *check)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strlen(rd) > 1)
	{
		while (*rd)
		{
			tmp = skip_whitespaces(rd);
			if (ft_char_in_str("NSWEDFC", *tmp))
			{
				c3d_count_config_elem(check, tmp);
				c3d_check_config_elem_details(tmp, check);
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

/**
 * @brief checks input arguments
 * 
 * @param ac 
 * @param av 
 */
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
