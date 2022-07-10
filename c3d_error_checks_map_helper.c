/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks_map_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:11:06 by anruland          #+#    #+#             */
/*   Updated: 2022/07/10 17:48:10 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief checks that the characters in line are space or 1
 * 
 * @param line 
 * @return int 
 */
int	c3d_first_last(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_c(line, '\n');
	while (i < len)
	{
		if (line[i] != ' ' && line[i] != '1')
		{
			return (MAP_WALLS);
		}
		i++;
	}
	return (0);
}

/**
 * @brief checks that the character c is a valid map character
 * 
 * @param c 
 * @return int 
 */
int	c3d_valid_map_char(char c)
{
	if (!ft_char_in_str(" NSWDE10", c))
	{
		return (MAP_INV_CHAR);
	}
	return (0);
}

/**
 * @brief checks that the characters around a space in the map are space or 1
 * 
 * @param line 
 * @param prev 
 * @param i 
 * @return int 
 */
int	c3d_check_surroundings(char *line, char *prev, int i)
{
	int	len;
	int	len_prev;

	len = ft_strlen(line);
	len_prev = ft_strlen(prev);
	if (i > 0 && !ft_char_in_str(" 1", line[i - 1]))
		return (MAP_WALLS);
	if (i + 1 < len && !ft_char_in_str(" 1", line[i + 1]))
		return (MAP_WALLS);
	if (i < len_prev && !ft_char_in_str(" 1", prev[i]))
	{
		return (MAP_WALLS);
	}
	if (i > 0 && i - 1 < len_prev && !ft_char_in_str(" 1", prev[i - 1]))
		return (MAP_WALLS);
	if (i + 1 < len_prev && !ft_char_in_str(" 1", prev[i + 1]))
		return (MAP_WALLS);
	return (0);
}

/**
 * @brief adds spaces at the end of the shorter line
 *  until they have the same length
 * 
 * @param check 
 * @param comp 
 * @return char* 
 */
char	*c3d_unify_map_len(char *check, char *comp)
{
	int		len;
	int		len_check;
	char	*tmp;

	len = ft_strlen(comp);
	len_check = ft_strlen(check);
	if (len > len_check)
	{
		tmp = ft_strndup_char(check, len, ' ');
		c3d_single_desctruct(check);
		return (tmp);
	}
	return (check);
}

/**
 * @brief checks if the line includes only valid characters and 
 * that the walls are closed
 * 
 * @param prev 
 * @param line 
 * @return int 
 */
int	c3d_check_line(char *prev, char *line)
{
	int	i;
	int	len;
	int	errno;

	errno = 0;
	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (c3d_valid_map_char(line[i]) > 0)
			return (MAP_INV_CHAR);
		if (i == 0 || i == len - 1)
		{
			if (!ft_char_in_str(" 1", line[i]))
				return (MAP_WALLS);
		}
		if (line[i] == ' ')
			errno = c3d_check_surroundings(line, prev, i);
		if (prev[i] == ' ' && !errno)
			errno = c3d_check_surroundings(prev, line, i);
		if (errno)
			return (errno);
		i++;
	}
	return (0);
}
