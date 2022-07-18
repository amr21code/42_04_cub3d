/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:06 by anruland          #+#    #+#             */
/*   Updated: 2022/07/18 18:00:41 by anruland         ###   ########.fr       */
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
	else if (!ft_strncmp(found, "DC ", 3))
		check->door_c++;
	else if (!ft_strncmp(found, "F ", 2))
		check->f++;
	else if (!ft_strncmp(found, "C ", 2))
		check->c++;
	else
		check->invalid = 1;
}

void	c3d_print_errors(int errno)
{
	if (errno == 2)
		ft_printerror("Error\nWrong amount of north texture");
	else if (errno == 3)
		ft_printerror("Error\nWrong amount of east texture");
	else if (errno == 4)
		ft_printerror("Error\nWrong amount of south texture");
	else if (errno == 5)
		ft_printerror("Error\nWrong amount of west texture");
	else if (errno == 6)
		ft_printerror("Error\nWrong amount of door texture");
	else if (errno == 7)
		ft_printerror("Error\nWrong amount of floor color");
	else if (errno == 8)
		ft_printerror("Error\nWrong amount of ceilling color");
	else if (errno == 9)
		ft_printerror("Error\nWrong characters in color");
	else if (errno == 10)
		ft_printerror("Error\nWrong range of color");
	else if (errno == 11)
		ft_printerror("Error\nCan't open texture file");
	else
		ft_printerror("Error\nWrong config elements");
}

/**
 * @brief prints error if invalid config elements 
 * 
 * @param check 
 */
void	c3d_errors_config_elem(t_preerr check)
{
	if (check.invalid != 0)
		c3d_print_errors(check.invalid);
	if (check.no != 1)
		check.invalid = 2;
	else if (check.ea != 1)
		check.invalid = 3;
	else if (check.so != 1)
		check.invalid = 4;
	else if (check.we != 1)
		check.invalid = 5;
	else if (check.door_c != 1)
		check.invalid = 6;
	else if (check.f != 1)
		check.invalid = 7;
	else if (check.c != 1)
		check.invalid = 8;
	if (check.invalid != 0)
		c3d_print_errors(check.invalid);
}

/**
 * @brief checks if color is in the range of [0,255]
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

/**
 * @brief checks if there is more than one number between commas
 * 
 * @param str 
 * @param last_nbr 
 * @param check 
 * @return int 
 */
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
