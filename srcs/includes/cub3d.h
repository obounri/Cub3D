/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:59:39 by obounri           #+#    #+#             */
/*   Updated: 2021/03/17 07:58:55 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>

# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC 53
# define IDS "RNOSOWEEASFC"
# define MAP_CHARS "012NSWE- "
# define INIT "NESW"
# define MOVESPEED 0.8
# define ROT 0.1
# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define U_DIV 1
# define V_DIV 1

typedef struct	s_spr
{
	int				x;
	int				y;
}				t_spr;

typedef struct	s_bmp
{
	int				size;
	char			*img;
	unsigned char	header[14];
	unsigned char	info[40];
	unsigned char	pad[3];
	int				color;
	int				fd;
}				t_bmp;

typedef struct	s_textures
{
	void			*textn;
	int				*textn_data;
	void			*texts;
	int				*texts_data;
	void			*textw;
	int				*textw_data;
	void			*texte;
	int				*texte_data;
	void			*text_sp;
	int				*text_sp_data;
	int				w;
	int				h;
	int				bpp;
	int				line_length;
	int				endian;
}				t_text;

typedef	struct	s_vect
{
	double			x;
	double			y;
}				t_vect;

typedef	struct	s_intvect
{
	int				x;
	int				y;
}				t_intvect;

typedef struct	s_wall
{
	t_vect			raydir;
	t_vect			sidedist;
	t_vect			deltadist;
	t_intvect		map;
	t_intvect		step;
	t_intvect		tex;
	double			camerax;
	double			perpwalldist;
	double			wallx;
	double			iter;
	double			texpos;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				color;
}				t_wall;

typedef struct	s_sp
{
	t_vect			sprite;
	t_vect			transform;
	t_intvect		drawstart;
	t_intvect		drawend;
	t_intvect		tex;
	double			invdet;
	int				spritescreenx;
	int				v_movescreen;
	int				sprite_height;
	int				sprite_width;
	int				stripe;
	int				d;
	int				color;
}				t_sp;

typedef struct	s_specs
{
	t_vect			pos;
	t_vect			dir;
	t_vect			plane;
	t_text			*textures;
	t_spr			*sprites;
	void			*mlx_ptr;
	void			*mlx_win;
	void			*buff;
	int				*buff_data;
	int				bpp;
	int				line_length;
	int				endian;
	int				w_map;
	int				h_map;
	int				rx;
	int				ry;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	int				floor;
	int				ceiling;
	char			*parsed;
	char			**map;
	double			*z_buffer;
	int				num_prites;
	int				*sprite_order;
	double			*sprite_distance;
	int				save;
}				t_specs;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
size_t			ft_strlen(const char *str);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strchr(const char *s, char c);
int				ft_isdigit(int c);

void			init(t_specs *specs);
int				destroy_exit(t_specs *specs);
void			render_update(t_specs *specs);
void			draw(t_specs *specs);
void			init_direction_ns(int a, int b, t_specs *specs);
void			init1(t_specs *specs, t_wall *wall, int i);
void			init2(t_specs *specs, t_wall *wall);
void			hit_wall(t_specs *specs, t_wall *wall);
void			error_exit(char *error);
void			r_err(t_specs *specs, char **infos);
void			path_ok_sprite(t_specs *specs, char **infos);
void			path_ok_no(t_specs *specs, char **infos);
void			path_ok_we(t_specs *specs, char **infos);
void			path_ok_so(t_specs *specs, char **infos);
void			path_ok_ea(t_specs *specs, char **infos);
int				create_rgb(t_specs *specs, char *rgb);
void			check_map(t_specs *specs);
void			check_duplicate(t_specs *specs, char *id);
char			*add_line(char *line, int len, int len_map, t_specs *specs);
void			init_map(t_specs *specs);
void			parser(int ac, char **av, t_specs *specs);
void			buffer_to_bmp(t_specs *specs);
void			draw_wall(t_specs *specs);
void			draw_sprites(t_specs *specs);
int				get_next_line(int fd, char **line);

#endif
