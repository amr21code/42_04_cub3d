/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:21:43 by anruland          #+#    #+#             */
/*   Updated: 2022/07/18 17:53:26 by anruland         ###   ########.fr       */
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

# define TEX 7

// Linux
enum e_keys
{
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_W = 119,
	KEY_ARR_LEFT = 65363,
	KEY_ARR_RIGHT = 65361,
	KEY_ESCAPE = 65307,
	SPACE = 32
};

enum e_tex
{
	N = 0,
	E,
	S,
	W,
	D,
	O
};

typedef struct s_color
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

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
	int		size_x;
	int		size_y;
	char	*path;
}	t_map;

typedef struct s_image
{
	void	*img;
	char	*data;
	int		bpp;
	int		line_size;
	int		endian;
	char	*path;
	int		size_x;
	int		size_y;
}	t_image;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	view;
	double		step;
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

typedef struct s_maperr
{
	int	errno;
	int	players;
	int	len;
}	t_maperr;

typedef struct s_preerr
{
	int		no;
	int		so;
	int		ea;
	int		we;
	int		door_c;
	int		c;
	int		f;
	int		invalid;
	int		valid;
	int		start_line;
	long	r;
	long	g;
	long	b;
}	t_preerr;

enum e_error
{
	MAP_INV_CHAR = 42,
	MAP_WALLS,
	MAP_PLAYER,
	MAP_INVALID,
};

typedef struct s_bg
{
	void	*img;
	char	*addr;
	int		bpp;
	int		x;
	int		endian;
}	t_bg;

typedef struct s_rays
{
	t_vector	pos;
	t_vector	cplane;
	t_vector	dir;
	t_vector	side;
	t_vector	delta;
	t_vector	step;
	double		cam;
	int			hit;
	int			wallside;
	double		ray_len;
	double		dist;
	double		wallh;
	int			texnum;
	double		wallx;
	int			tex_x;
	int			tex_y;
	int			tex_size;
	double		tex_step;
	double		tex_pos;
	int			tex_idx;
}	t_rays;

/**********************/
/*** INITIALISATION ***/
/**********************/
/* c3d_init.c */
void	c3d_init_preerr(t_preerr *check);
void	c3d_init_struct(t_data *cub);
void	c3d_init_cub(t_data *cub, char *path);
void	c3d_init_config(t_data *cub, char *path);
void	c3d_init_win(t_data *data);

/* c3d_init_map.c */
void	c3d_save_map(t_data *cub, char *line, int y);
void	c3d_init_map(t_data *cub, char *path);

/* c3d_init_config.c */
void	c3d_init_config_elem(t_data *cub, char *rd);
void	c3d_init_save_colors(t_data *cub, char *elem);
int		c3d_create_trgb(int t, int r, int g, int b);

/* c3d_init_textures.c */
void	c3d_init_save_tex_path(t_data *cub, char *elem);
void	c3d_load_tex(t_data *data);
void	c3d_init_sprite(void *mlx, t_image *image);

/**********************/
/****** DRAW MAZE *****/
/**********************/
/* c3d_draw.c */
void	c3d_draw_px(t_image *img, int x, int y, int color);
void	c3d_draw_col(t_data *cub, int x, int height, t_rays ray);

/* c3d_draw_bg.c */
void	c3d_draw_bg(t_data *cub);
void	c3d_draw_square(t_data *cub);

/* c3d_draw_minimap.c */
void	c3d_draw_map(t_data *cub);
void	c3d_init_minimap(t_data *cub);

/* c3d_raycast.c */
double	c3d_calc_wallheight(t_data *cub, double len_ray);
void	c3d_raycast(t_data *cub);

/* c3d_raycast_helper.c */
void	c3d_calc_steps(t_rays *ray, t_data *cub);
void	c3d_init_ray(t_rays *ray, t_data *cub, int i);
void	c3d_find_wall(t_rays *ray, t_data *cub);
void	c3d_choose_tex(t_rays *ray, t_data *cub);

/**********************/
/*** INPUT CHECKING ***/
/**********************/
/* c3d_input.c */
int		c3d_input(int keycode, t_data *cub);
void	c3d_open_door(t_data *cub);

/* c3d_move.c */
void	c3d_minimap_move(t_data *cub, double x, double y);
int		c3d_check_move(t_data *cub, double x, double y);
void	c3d_turn(t_data *cub, double deg);
void	c3d_move(t_data *cub, double x, double y);

/**********************/
/*** ERROR CHECKING ***/
/**********************/
/* c3d_error_checks.c */
int		c3d_check_config_elem(char *path);
void	c3d_check_map(int start, char *path);
int		c3d_check_string(char *rd, char *str, int flag);
char	*c3d_check_map2(t_maperr *check, int fd, int start, char *line);
void	c3d_check_errno(char *line, char *rd, t_maperr *check);

/* c3d_error_checks_helper.c */
void	c3d_count_config_elem(t_preerr *check, char *found);
void	c3d_errors_config_elem(t_preerr check);
int		c3d_check_rgb_range(int color);
int		c3d_check_between_elem(char *str, int last_nbr, t_preerr *check);

/* c3d_error_checks_helper2.c */
void	c3d_check_config_elem_details(char *rd, t_preerr *check);
int		c3d_check_config_elem_line(char *rd, t_preerr *check);
void	c3d_pre_error_check(int ac, char **av);

/* c3d_error_checks_map_helper.c */
int		c3d_valid_map_char(char c);
int		c3d_first_last(char *line);
int		c3d_check_surroundings(char *line, char *prev, int i);
char	*c3d_unify_map_len(char *check, char *comp);
int		c3d_check_line(char *prev, char *line);

/**********************/
/**** DESTRUCTORS *****/
/**********************/
/* c3d_destructor.c */
void	c3d_single_desctruct(void *str);
void	c3d_pre_destructor(int fd, char *line, char *rd, int error);
int		c3d_destructor(t_data *cub);
void	c3d_free_array(char **argv);

/**********************/
/******* MISC *********/
/**********************/
/* c3d_math.c */
double	c3d_abs(double nbr);
double	c3d_div(double num, double denom);
double	c3d_deg_to_rad(int deg);

#endif
