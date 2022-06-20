/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:21:43 by anruland          #+#    #+#             */
/*   Updated: 2022/06/20 15:41:10 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define TEX 5

# ifdef __linux__
// Linux
enum e_keys
{
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_W = 119,
	// KEY_ARR_LEFT = ,
	// KEY_ARR_RIGHT = ,
	KEY_ESCAPE = 65307
};
# else
// Mac
enum e_keys
{
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	// KEY_ARR_LEFT = ,
	// KEY_ARR_RIGHT = ,
	KEY_ESCAPE = 53
};
# endif

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
	char	*path;
}	t_map;

typedef struct s_image
{
	void	*img;
	char	*data;
	char	*path;
	int		bpp;
	int		line_size;
	int		endian;
	int		size_x;
	int		size_y;
}	t_image;

typedef struct s_player
{
	int	collected;
	int	x;
	int	y;
}	t_player;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	t_image		images[TEX];
	t_player	player;
	int			color_floor;
	int			color_ceilling;
}	t_data;

#endif
