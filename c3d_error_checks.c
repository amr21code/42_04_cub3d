/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:11 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 14:01:37 by anruland         ###   ########.fr       */
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
		ft_char_replace(rd, '\n', ' ');
		if (i == start || i == len)
			c3d_pre_destructor(fd, line, rd, c3d_first_last(rd));
		if (i > start)
			c3d_pre_destructor(fd, line, rd, c3d_check_line(line, rd));
		c3d_single_desctruct(line);
		line = rd;
		rd = get_next_line(fd);
	}
	c3d_single_desctruct(line);
}

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

int	c3d_check_line(char *prev, char *line)
{
	int	i;
	int	len;
	int	errno;

	errno = 0;
	len = ft_strlen(line);
	i = 0;
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
		{
			errno = c3d_check_surroundings(line, prev, i);
			if (errno)
				return (errno);
		}
		if (prev[i] == ' ')
		{
			errno = c3d_check_surroundings(prev, line, i);
			if (errno)
				return (errno);
		}
		i++;
	}
	return (0);
}

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
			ft_printf("first_last %s\n", line);
			return (MAP_WALLS);
		}
		i++;
	}
	return (0);
}

int	c3d_valid_map_char(char c)
{
	if (!ft_strchr(" NSWDE10", c))
	{
		ft_printf("c: %c", c);
		return (MAP_INV_CHAR);
	}
	return (0);
}
