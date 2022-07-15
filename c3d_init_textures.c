/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_init_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:00:54 by anruland          #+#    #+#             */
/*   Updated: 2022/07/15 15:05:47 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief saves the texture path in the struct cub
 * 
 * @param cub 
 * @param elem 
 */
void	c3d_init_save_tex_path(t_data *cub, char *elem)
{
	char	*tex_idx;
	char	*tmp;
	int		i;

	i = 0;
	tex_idx = "NESWDO";
	while (i < TEX - 2)
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

/**
 * @brief loads texture in image in struct data
 * 
 * @param data 
 */
void	c3d_load_tex(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (i < TEX - 2)
	{
		fd = open(data->images[i].path, O_RDONLY);
		c3d_init_sprite(data->mlx.mlx, &data->images[i]);
		if (!data->images[i].img)
			ft_printerror("Error\nFailed loading texture");
		i++;
		close(fd);
	}
}

/**
 * @brief converts xpm file in mlx image
 * 
 * @param mlx 
 * @param image 
 */
void	c3d_init_sprite(void *mlx, t_image *image)
{
	image->img = mlx_xpm_file_to_image(mlx, image->path,
			&image->size_x, &image->size_y);
	image->data = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_size, &image->endian);
}
