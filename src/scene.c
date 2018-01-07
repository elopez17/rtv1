/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 18:47:13 by eLopez            #+#    #+#             */
/*   Updated: 2018/01/06 19:13:26 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	norm_vect(t_vect v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

static t_rgb	color_at(t_ray *intersection, int index, t_rtv1 *rt)
{
	t_obj	*tmp;
	t_vect	dist;
	float	dist_mag;
	double	*intersects;
	t_ray	shadow;

	if (index == -1)
		return ((t_rgb){0, 0, 0});
	shadow.origin = intersection->origin;
	shadow.dir = normalize(add_vect(rt->light, invert(intersection->origin)));
	tmp = rt->obj;
	while (--index >= 0)
		tmp = tmp->next;
	dist = add_vect(rt->light, invert(intersection->origin));
	dist_mag = sqrt((dist.x * dist.x) + (dist.y * dist.y) + (dist.z * dist.z));
	intersects = findintersects(shadow, rt);
	while (++index < rt->nodes)
		if (intersects[index] > 0.00000001 && intersects[index] <= dist_mag)
		{
			ft_memdel((void**)&intersects);
			return (checklight(tmp, intersection, rt->light, 1));
		}
	ft_memdel((void**)&intersects);
	return (checklight(tmp, intersection, rt->light, 0));
}

static int	winningobject(double *intersects, int nodes)
{
	double	max;
	int		i;
	int		index;

	i = -1;
	max = -1;
	index = 0;
	if (nodes == 0)
		return (-1);
	while (++i < nodes)
		if (intersects[i] > max)
			max = intersects[i];
	if (max < 0.00000001)
		return (-1);
	while (--i >= 0)
		if (intersects[i] >= 0.00000001 && intersects[i] <= max)
		{
			max = intersects[i];
			index = i;
		}
	return (index);
}

static void	setxy(t_rtv1 *rt, t_ray *ray, t_xy *pixel)
{
	t_xy		dir;
	
	dir.x = pixel->x / rt->w.width;
	dir.y = (rt->w.height - pixel->y) / rt->w.height;
	ray->origin = rt->cam.pos;
	ray->dir = normalize(add_vect(rt->cam.dir, add_vect(mult_vect(rt->cam.right, dir.x - 0.5), mult_vect(rt->cam.down, dir.y - 0.5))));
}

void	scene(t_rtv1 *rt)
{
	t_xy		pixel;
	t_ray		ray;
	double		*intersects;
	t_ray		intersection;
	int			index;

	pixel.y = -1;
	while(++pixel.y < rt->w.height)
	{
		pixel.x = -1;
		while(++pixel.x < rt->w.width)
		{
			setxy(rt, &ray, &pixel);
			intersects = findintersects(ray, rt);
			if ((index = winningobject(intersects, rt->nodes)) != -1)
			{
				intersection.origin = add_vect(ray.origin, mult_vect(ray.dir,
							intersects[index]));
				intersection.dir = ray.dir;
			}
			putpixel(rt, pixel.x, pixel.y, color_at(&intersection, index, rt));
			ft_memdel((void**)&intersects);
		}
	}
}
