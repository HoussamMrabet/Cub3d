/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:57:39 by hmrabet           #+#    #+#             */
/*   Updated: 2024/10/08 22:50:55 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include "MLX42.h"
# include <math.h>

# define US 32
# define W_SIZE 1200
# define H_SIZE 900
# define FOV (M_PI / 3)

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_block_memory
{
	void					*leak;
	struct s_block_memory	*next;
}	t_block_memory;

typedef struct s_corr
{
	double	x;
	double	y;
	int		color;
}	t_corr;

typedef struct s_player
{
	t_corr	c;
	int		rad; // the size of player
	int		td; // turn direction : 1 to right -1 to left 0 initial and nothing will happen
	int		wd;	// walk direction : 1 to front -1 to back 0 initial and nothing will happen
	int		wd_h;	// walk direction : 1 to right -1 to left 0 initial and nothing will happen
	double	rot_ang; // the angle of rotation should be initialized depanding on N or S or E or W
	double	ms; // move speed initalized by a macro of 3.0
	double	rot_speed; // rotation speed initialized with a macro of 3 * (math.pi/180)	
}	t_player;

typedef struct s_d
{
	int	w;
	int	h;
}	t_d;

typedef struct s_map
{
	char		**map;
	char		**pre_map;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	int			height;
	int			width;
}	t_map;

typedef struct s_ray
{
	t_corr	hit_wall;
	double	ang;
	t_bool	is_w_hited;
	double	distance;
	char	type;
}	t_ray;


typedef struct s_cub3d
{
	char				*input;
	unsigned int		max_fd;
	t_map				map;
	t_block_memory		*collector;
	mlx_t				*m;
	t_player			p;
	mlx_image_t			*img;
	mlx_texture_t		*wall_1;
	mlx_texture_t		*wall_2;
}	t_cub3d;

// GARBAGE COLLECTOR
void		*ft_malloc(t_cub3d *cub, t_block_memory **g, size_t s);
void		ft_free(t_block_memory **memory);
void		ft_exit(char *msg, int status, t_cub3d *cub);
void		close_fds(t_cub3d *cub);

// UTILS
size_t		ft_strlen(const char *s);
t_bool		ft_strchr(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
int			ft_atoi(char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char *s1, char *s2, t_cub3d *cub);
char		*ft_strdup(char *s1, t_cub3d *cub);
char		*ft_substr(t_cub3d *cub, char *s, unsigned int start, size_t len);
char		*ft_strtrim(t_cub3d *cub, char *s1, char *set);
char		*ft_itoa(t_cub3d *cub, int n);
char		**ft_split(char *s, char c, t_cub3d *cub);
t_bool		ft_isal(char c);
t_bool		ft_isnum(char c);
t_bool		ft_isalnum(char c);

// INITIALIZERS
void		init_data(t_cub3d *cub, char **av);

// PARSERS
int			get_map_height(char **splitted, int i);
int			get_big_line(char **splitted, int i);
void		check_map_row(t_cub3d *cub, char *row);
void		check_chars(t_cub3d *cub);
void		check_colors(t_cub3d *cub);
void		parse_map(t_cub3d *cub);
void		parse_identifiers(t_cub3d *cub);
void		init_map(t_cub3d *cub, char **av);

// run mlx
int			lunch_mlx(t_cub3d *cub);
int			put_square(t_corr *corr, t_d *d, t_cub3d *cub, int color);
int			ft_create_color(int r, int g, int b, int a);
void		rneder_map_2d(t_cub3d *cub);
mlx_image_t	*create_image(int w, int h, t_cub3d *cub);
void		render_circle(int x, int y, int color, t_cub3d *cub);
void		put_line(t_corr a, t_corr b, t_cub3d *cub);
void		key_fun(void *params);
void		cam_move(t_cub3d *cub);
void		put_line_v2(t_corr c, int d, double ang, t_cub3d *cub);
void		print_rays(int n, t_cub3d *cub);
void		move_f_b(t_cub3d *c);
void		move_l_r(t_cub3d *c);
void		move(t_cub3d *c);
t_ray		cast_ray_h(t_cub3d *c, double ang,int is_r_down,int is_r_left);
double		get_angle(double ang);
void		get_angl_direction(int *is_r_down, int *is_r_left, double ang);
void 		setup_steps_h(double step[2], int is_r_down, int is_r_left, double ang);
double		calc_distance(t_corr a, t_corr b);
void		setup_steps_v(double step[2], int is_r_down, int is_r_left, double ang);
int			cast_condition(t_corr inter, t_cub3d *c);
t_ray		cast_ray_v(double ang, int is_down, int is_left, t_cub3d *c);
t_ray		which_ray(double ang, t_cub3d *c);
int			return_pixel(t_corr point, mlx_texture_t* t);
void		render_y_of_image(t_corr c, int d, double ang, t_cub3d *cub);
#endif
