/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_error_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:11 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 15:05:19 by anruland         ###   ########.fr       */
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
		{
			line = c3d_unify_map_len(line, rd);
			rd = c3d_unify_map_len(rd, line);
			c3d_pre_destructor(fd, line, rd, c3d_check_line(line, rd));
		}
		c3d_single_desctruct(line);
		line = rd;
		rd = get_next_line(fd);
	}
	c3d_single_desctruct(line);
}

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
		{
			errno = c3d_check_surroundings(line, prev, i);
			if (errno)
				return (errno);
		}
		// ft_printf("i %d len %d\nprev %s-\nline %s-\n",i, len, prev, line);
		// ft_printf("prev[%d] %c\n",i, *prev[i]);
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
