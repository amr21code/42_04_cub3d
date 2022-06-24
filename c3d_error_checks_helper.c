/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:06 by anruland          #+#    #+#             */
/*   Updated: 2022/06/24 07:54:53 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief counts the config elements of one line
 * 
 * @param check 
 * @param found 
 */
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

/**
 * @brief prints error if invalid config elements 
 * 
 * @param check 
 */
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

/**
 * @brief checks if number is in the range of [0,255]
 * 
 * @param color 
 * @return int 
 */
int	c3d_check_rgb_range(int color)
{
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

int	c3d_check_between_elem(char *str, int last_nbr, t_preerr *check)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	j = 0;
	tmp = NULL;
	tmp = skip_whitespaces(str);
	i = (tmp - str);
	i += ft_nbrlen_base_sign((long long)last_nbr, 1, 10);
	len = ft_strlen_c(&str[i], ',');
	while (j < len)
	{
		if (ft_isdigit(str[i + j]))
			check->invalid = 1;
		j++;
	}
	return (i);
}

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
	{
		i += 1;
		if (c3d_check_string(&rd[i], "0123456789, \n", 0))
			check->invalid = 1;
		check->r = ft_atol(&rd[i]);
		i += ft_strlen_c(&rd[i], ',') + 1;
		c3d_check_between_elem(&rd[i], check->r, check);
		check->g = ft_atol(&rd[i]);
		c3d_check_between_elem(&rd[i], check->g, check);
		i += ft_strlen_c(&rd[i], ',') + 1;
		check->b = ft_atol(&rd[i]);
		c3d_check_between_elem(&rd[i], check->b, check);
		if (!(c3d_check_rgb_range(check->r)
				&& c3d_check_rgb_range(check->g)
				&& c3d_check_rgb_range(check->b)))
			check->invalid = 1;
	}
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
