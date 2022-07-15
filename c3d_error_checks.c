/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:11 by anruland          #+#    #+#             */
/*   Updated: 2022/07/15 12:24:30 by djedasch         ###   ########.fr       */
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

/**
 * @brief checks if the map is valid
 * 
 * @param start 
 * @param path 
 */
void	c3d_check_map(int start, char *path)
{
	int			fd;
	char		*line;
	t_maperr	check;
	char		*rd;

	check.errno = 0;
	check.players = 0;
	check.len = ft_linecount(path);
	line = NULL;
	fd = open(path, O_RDONLY);
	rd = c3d_check_map2(&check, fd, start, line);
	if (check.players != 1)
		check.errno = MAP_PLAYER;
	c3d_pre_destructor(fd, line, rd, check.errno);
	close(fd);
	c3d_single_desctruct(line);
}

char	*c3d_check_map2(t_maperr *check, int fd, int start, char *line)
{
	int		i;
	char	*rd;

	i = 0;
	rd = get_next_line(fd);
	while (rd)
	{
		i++;
		ft_char_replace(rd, '\n', ' ');
		if (i == start || i == check->len)
			c3d_pre_destructor(fd, line, rd, c3d_first_last(rd));
		if (i > start)
		{
			check->players += c3d_check_string(rd, "NSEW", 1);
			line = c3d_unify_map_len(line, rd);
			rd = c3d_unify_map_len(rd, line);
			c3d_check_errno(line, rd, check);
		}
		c3d_single_desctruct(line);
		line = rd;
		rd = get_next_line(fd);
	}
	return (rd);
}

void	c3d_check_errno(char *line, char *rd, t_maperr *check)
{
	if (!ft_char_in_str(line, '1') && ft_char_in_str(rd, '1'))
		check->errno = MAP_INVALID;
	if (check->errno == 0)
		check->errno = c3d_check_line(line, rd);
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
