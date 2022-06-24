/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:11 by anruland          #+#    #+#             */
/*   Updated: 2022/06/24 12:05:13 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/**
 * @brief checks if input file is correct
 * 
 * @param path path of input file
 * @return int 
 */
int	c3d_check_config_elem(char *path)
{
	int			fd;
	char		*rd;
	t_preerr	check;
	int			lines;

	lines = 0;
	rd = NULL;
	c3d_init_preerr(&check);
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		lines++;
		if (check.invalid == 0 && check.valid == 0)
		{
			check.start_line = lines;
			check.valid = c3d_check_config_elem_line(rd, &check);
		}
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
	c3d_errors_config_elem(check);
	return (check.start_line);
}

void	c3d_check_map(int start, char *path)
{
	int			fd;
	char		*line;
	char		*rd;
	int			i;
	t_maperr	check;

	check.errno = 0;
	check.players = 0;
	line = NULL;
	check.len = ft_linecount(path);
	i = 0;
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		i++;
		ft_char_replace(rd, '\n', ' ');
		if (i == start || i == check.len)
			c3d_pre_destructor(fd, line, rd, c3d_first_last(rd));
		if (i > start)
		{
			check.players += c3d_check_string(rd, "NSEW", 1);
			line = c3d_unify_map_len(line, rd);
			rd = c3d_unify_map_len(rd, line);
			if (!ft_char_in_str(line, '1') && ft_char_in_str(rd, '1'))
				check.errno = MAP_INVALID;
			if (check.errno == 0)
				check.errno = c3d_check_line(line, rd);
		}
		c3d_single_desctruct(line);
		line = rd;
		rd = get_next_line(fd);
	}
	if (check.players != 1)
		check.errno = MAP_PLAYER;
	c3d_pre_destructor(fd, line, rd, check.errno);
	close(fd);
	c3d_single_desctruct(line);
}

/**
 * flag = 1: counts the number of players
 * flag = 0: 1 for invalid string, 0 for valid
 */
int	c3d_check_string(char *rd, char *str, int flag)
{
	int	i;
	int	players;

	i = 0;
	players = 0;
	while (rd[i])
	{
		if (flag == 1)
			players += ft_char_in_str(str, rd[i]);
		else if (!ft_char_in_str(str, rd[i]))
			return (1);
		i++;
	}
	return (players);
}
