/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 00:06:40 by eLopez            #+#    #+#             */
/*   Updated: 2017/12/15 21:15:33 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <ft_printf.h>
# include <get_next_line.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)
# define PI 3.14159265
# define KEY1 83
# define KEY2 84
# define KEY3 85
# define KEY4 86
# define KEY5 87
# define KEY6 88
# define KEY7 89
# define KEY8 91
# define KEY9 92
# define KEYMIN 78
# define KEYPLUS 69
# define KEYUP 126
# define KEYDOWN 125
# define KEYESC 53
# define KEYR 15
# define KEYG 5
# define KEYB 11

typedef struct	s_dimensions
{
	int		width;
	int		height;
}				t_dim;

typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
}				t_vert;

typedef struct	s_rgb
{
	int		red;
	int		green;
	int		blue;
}				t_rgb;

typedef struct	s_ray
{
	t_vert	origin;
	t_vert	dir;
}				t_ray;

typedef struct	s_light
{
	t_vert	pos;
	t_rgb	clr;
}				t_light;

typedef struct	s_sphere
{
	t_vert	pos;
	double	radius;
	t_rgb	clr;
}				t_sphere;

typedef struct	s_plane
{
	t_vert	norm;
	double dist;
	t_rgb	clr;
}				t_plane;

typedef struct	s_camera
{
	t_vert	pos;
	t_vert	dir;
	t_vert	right;
	t_vert	down;
	t_vert	look_at;
}				t_cam;

typedef struct	s_object
{
	int				type;
	double			size;
	t_vert			pos;
	t_vert			rot;
	t_rgb			clr;
	struct s_object	*next;
}				t_obj;

typedef struct	s_rtv1
{
	void	*mlx;
	void	*win;
	t_dim	w;
	void	*img;
	int		bpp;
	int		len;
	int		endian;
	char	*addr;
	t_cam	cam;
}				t_rtv1;

void	render(t_rtv1 *rt);
void	drawline(t_rtv1 *rt, t_vert *a, t_vert *b, int color);
void	putpixel(t_rtv1 *rt, int x, int y, int color);
int		key_hook(int key, t_rtv1 **rt);
int		close_hook(t_rtv1 **rt);
int		expose_hook(t_rtv1 **rt);
t_vert  normalize(t_vert v);
t_vert  invert(t_vert v);
double  dot_prod(t_vert v1, t_vert v2);
t_vert  cross_prod(t_vert v1, t_vert v2);
t_vert  add_vert(t_vert v1, t_vert v2);
t_vert  mult_vert(t_vert v, double scalar);
t_vert  diff_vert(t_vert v1, t_vert v2);
double  findinterplane(t_ray ray, t_vert norm);
double  findintersphere(t_ray ray, t_sphere sphere);
t_vert	sphere_norm(t_sphere sphere, t_vert point);
void	scene(t_rtv1 *rt);

#endif