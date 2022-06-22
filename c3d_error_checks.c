/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:11 by anruland          #+#    #+#             */
/*   Updated: 2022/06/22 17:08:04 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (!c3d_check_config_elem_line(rd, &check, fd))
		{
			c3d_single_desctruct(rd);
			break ;
		}
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
	c3d_errors_config_elem(check);
	return (lines);
}

void	c3d_check_map(int start, char *path)
{
	int		fd;
	int		i;
	char	*line;
	int		len;
	char	*rd;

	line = NULL;
	len = ft_linecount(path);
	i = 0;
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		i++;
		if (i == start + 1 || i == len)
			c3d_pre_destructor(fd, line, rd, c3d_first_last(rd));
		if (i > start + 1)
			c3d_pre_destructor(fd, line, rd, c3d_check_line(line, rd));
		c3d_single_desctruct(line);
		line = rd;
		rd = get_next_line(fd);
	}
	c3d_single_desctruct(line);
}

int	c3d_check_line(char *prev, char *line)
{
	int	i;
	int	len_prev;
	int	len;

	len_prev = ft_strlen(prev);
	len = ft_strlen(line);
	i = 0;
	while (line[i])
	{
		if (c3d_valid_map_char(line[i]) > 0)
			return (MAP_INV_CHAR);
		else if (line[i] == ' ')
		{
			if (i < len_prev && prev[i] != '1' && prev[i] != ' ')
				return (MAP_WALLS);
			if (i > 0 && line[i - 1] != '1' && line[i - 1] != ' ')
				return (MAP_WALLS);
			if (i + 1 < len && line[i + 1] != '1' && line[i + 1] != ' ')
				return (MAP_WALLS);
			if (i > 0 && i - 1 < len_prev && prev[i - 1] != '1' && prev[i - 1] != ' ')
				return (MAP_WALLS);
			if (i + 1 < len_prev && prev[i + 1] != '1' && prev[i + 1] != ' ')
				return (MAP_WALLS);
		}
		i++;
	}
	return (0);
}

int	c3d_first_last(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
			return (MAP_WALLS);
		i++;
	}
	return (0);
}

int	c3d_valid_map_char(char c)
{
	if (!ft_strchr(" NSWDE10", c))
		return (MAP_INV_CHAR);
	return (0);
}
