/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:21:43 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 15:00:54 by anruland         ###   ########.fr       */
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
	KEY_ARR_LEFT = 65363,
	KEY_ARR_RIGHT = 65361,
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
	KEY_ARR_LEFT = 123,
	KEY_ARR_RIGHT = 124,
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

typedef struct s_preerr
{
	int	no;
	int	so;
	int	ea;
	int	we;
	int	door;
	int	c;
	int	f;
}	t_preerr;

enum e_error
{
	MAP_INV_CHAR = 42,
	MAP_WALLS,
};

/*** INITIALISATION ***/
/* c3d_init.c */
void	c3d_init_preerr(t_preerr *check);

/*** ERROR CHECKING ***/
/* c3d_error_checks.c */
void	c3d_pre_error_check(int ac, char **av);
int		c3d_check_config_elem(char *path);
void	c3d_check_map(int start, char *path);
int		c3d_check_line(char *prev, char *line);

/* c3d_error_checks_helper.c */
void	c3d_count_config_elem(t_preerr *check, char *found);
void	c3d_errors_config_elem(t_preerr check);
int		c3d_check_config_elem_line(char *rd, t_preerr *check, int fd);

/* c3d_error_checks_map_helper .c */
int		c3d_valid_map_char(char c);
int		c3d_first_last(char *line);
int		c3d_check_surroundings(char *line, char *prev, int i);
char	*ft_strndup_char(char *src, int len, char c);
char	*c3d_unify_map_len(char *check, char *comp);

/*** DESTRUCTORS ***/
/* c3d_destructor.c */
void	c3d_single_desctruct(void *str);
void	c3d_pre_destructor(int fd, char *line, char *rd, int error);

#endif
