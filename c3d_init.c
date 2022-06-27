/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:11:05 by anruland          #+#    #+#             */
/*   Updated: 2022/06/27 10:52:47 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_init_preerr(t_preerr *check)
{
		check->no = 0;
		check->ea = 0;
		check->so = 0;
		check->we = 0;
		check->door = 0;
		check->f = 0;
		check->c = 0;
		check->invalid = 0;
		check->valid = 0;
		check->start_line = 0;
		check->r = 0;
		check->g = 0;
		check->b = 0;
}

void	c3d_init_struct(t_data *cub)
{
	cub->color_ceilling = 0;
	cub->color_floor = 0;
	cub->player.pos.x = 0;
	cub->player.pos.y = 0;
	cub->player.view.x = 0;
	cub->player.view.y = 0;
	cub->map.size_x = 0;
	cub->map.size_y = 0;
	cub->mlx.width = 1024;
	cub->mlx.height = 768;
}

int	c3d_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	c3d_init_save_tex_path(t_data *cub, char *elem)
{
	char	*tex_idx;
	char	*tmp;
	int		i;

	i = 0;
	tex_idx = "NESWD";
	while (i < 5)
	{
		if (*elem == tex_idx[i])
		{
			elem += 2;
			tmp = ft_strtrim(elem, " \n");
			cub->images[i].path = tmp;
		}
		i++;
	}
}

void	c3d_init_save_colors(t_data *cub, char *elem)
{
	int		fc;
	t_color	c;

	fc = 0;
	if (*elem == 'C')
		fc = 1;
	elem += 1;
	c.r = ft_atol(elem);
	elem += ft_strlen_c(elem, ',') + 1;
	c.g = ft_atol(elem);
	elem += ft_strlen_c(elem, ',') + 1;
	c.b = ft_atol(elem);
	if (fc == 1)
		cub->color_ceilling = c3d_create_trgb(255, c.r, c.g, c.b);
	else
		cub->color_floor = c3d_create_trgb(255, c.r, c.g, c.b);
}

void	c3d_init_config_elem(t_data *cub, char *rd)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	tmp = skip_whitespaces(rd);
	if (ft_char_in_str("NSWED", *tmp))
		c3d_init_save_tex_path(cub, tmp);
	else if (ft_char_in_str("FC", *tmp))
		c3d_init_save_colors(cub, tmp);
	else if (ft_char_in_str("1", *tmp))
	{
		len = ft_strlen(rd);
		if (len > cub->map.size_x)
			cub->map.size_x = len;
		cub->map.size_y++;
	}
}

void	c3d_save_map(t_data *cub, char *line, int y)
{
	int		i;

	i = 0;
	cub->map.map[y] = (char *)ft_calloc(cub->map.size_x + 1, sizeof(char));
	while (line[i])
	{
		if (line[i] != '\n')
			cub->map.map[y][i] = line[i];
		if (!ft_char_in_str(" 01D\n", line[i]))
		{
			cub->player.pos.x = i;
			cub->player.pos.y = y;
			if (line[i] == 'E')
				cub->player.view.x = 1;
			else if (line[i] == 'W')
				cub->player.view.x = -1;
			else if (line[i] == 'N')
				cub->player.view.y = 1;
			else if (line[i] == 'S')
				cub->player.view.y = -1;
		}
		i++;
	}
}

void	c3d_init_map(t_data *cub, char *path)
{
	int		fd;
	char	*rd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	rd = NULL;
	cub->map.map = (char **)ft_calloc(cub->map.size_y + 1, sizeof(char *));
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		tmp = skip_whitespaces(rd);
		if (*tmp == '1')
		{
			c3d_save_map(cub, rd, i);
			i++;
		}
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
}

void	c3d_init_config(t_data *cub, char *path)
{
	int		fd;
	char	*rd;

	rd = NULL;
	fd = open(path, O_RDONLY);
	rd = get_next_line(fd);
	while (rd)
	{
		c3d_init_config_elem(cub, rd);
		c3d_single_desctruct(rd);
		rd = get_next_line(fd);
	}
	close(fd);
}

void	c3d_init_cub(t_data *cub, char *path)
{
	c3d_init_config(cub, path);
	c3d_init_map(cub, path);
}

void	c3d_load_tex(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (i < TEX)
	{
		fd = open(data->images[i].path, O_RDONLY);
		c3d_init_sprite(data->mlx.mlx, &data->images[i]);
		if (!data->images[i].img)
			ft_printerror("Error\nFailed loading texture");
		i++;
		close(fd);
	}
}

void	c3d_init_sprite(void *mlx, t_image *image)
{
	image->img = mlx_xpm_file_to_image(mlx, image->path,
			&image->size_x, &image->size_y);
}

void	c3d_init_win(t_data *data)
{
	data->mlx.width = 1024;
	data->mlx.height = 768;
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->mlx.width,
			data->mlx.height, "cub3D");
}
