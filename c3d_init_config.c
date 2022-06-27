/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_init_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:59:10 by anruland          #+#    #+#             */
/*   Updated: 2022/06/27 10:59:54 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	c3d_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
