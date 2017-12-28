#include <rtv1.h>

static t_rgb	color_at(t_ray *intersection, int index, t_rtv1 *rt, t_light *lights)
{
	t_obj	*tmp;
	t_vert	light_dir;
	t_vert	dist_to_light;
	float	dist_to_light_mag;
	double	*intersects;
	t_vert	obj_norm;
	double	cosine_ang;
	t_ray	shadow;
	int		shadowed;
	int		i;
	t_rgb	final;

	if (index == -1)
		return ((t_rgb){0, 0, 0});
	shadowed = 0;
	shadow.origin = intersection->origin;
	shadow.dir = normalize(add_vert(lights->pos, invert(intersection->origin)));
	tmp = rt->obj;
	light_dir = add_vert(lights->pos, invert(intersection->origin));
	while (--index >= 0)
		tmp = tmp->next;
	dist_to_light = add_vert(lights->pos, invert(intersection->origin));
	dist_to_light_mag = sqrt((dist_to_light.x * dist_to_light.x) + (dist_to_light.y * dist_to_light.y) + (dist_to_light.z * dist_to_light.z));
	intersects = findintersects(shadow, rt);
	i = -1;
	while (++i < rt->nodes)
		if (intersects[i] > 0 && intersects[i] <= dist_to_light_mag)
		{
			shadowed = 1;
			break ;
		}
	ft_memdel((void**)&intersects);
	if (tmp->type == 1)
	{
		obj_norm = sphere_norm(tmp->u.sphere, intersection->origin);
		cosine_ang = dot_prod(light_dir, obj_norm);
		final = colorscalar(tmp->u.sphere.clr, 0.2);
		if (shadowed == 0)
			final = coloradd(final, colorscalar(colormult(tmp->u.sphere.clr, lights->clr), cosine_ang));
		return (final);
	}
	else if (tmp->type == 2)
	{
		obj_norm = tmp->u.plane.norm;
		cosine_ang = dot_prod(light_dir, obj_norm);
		final = colorscalar(tmp->u.plane.clr, 0.2);
		if (shadowed == 0)
			final = coloradd(final, colorscalar(colormult(tmp->u.plane.clr, lights->clr), cosine_ang));
		return (final);
	}
	else if (tmp->type == 3)
		;//return (tmp->u.cone.clr);
	else
		;//return (tmp->u.cylinder.clr);
	return ((t_rgb){0, 0, 0});
}

static int	winningobject(double *intersects, int nodes)
{
	double	max;
	int		i;
	int		index;

	i = -1;
	max = 0;
	index = 0;
	if (nodes == 0)
		return (-1);
	while (++i < nodes)
		if (intersects[i] > max)
			max = intersects[i];
	if (max > 0)
	{
		while (--i >= 0)
			if (intersects[i] > 0 && intersects[i] <= max)
			{
				max = intersects[i];
				index = i;
			}
		return (index);
	}
	return (-1);
}

static void	setxy(t_rtv1 *rt, t_xy *dir, t_xy *pixel)
{
	if (rt->w.width > rt->w.height)
	{
		dir->x = ((pixel->x + 0.5) / rt->w.width) * rt->asp_ratio - (((rt->w.width - rt->w.height) / (double)rt->w.height) / 2);
		dir->y = ((rt->w.height - pixel->y) + 0.5) / rt->w.height;
	}
	else if (rt->w.height > rt->w.width)
	{
		dir->x = (pixel->x + 0.5) / rt->w.width;
		dir->y = (((rt->w.height - pixel->y) + 0.5) / rt->w.height) / rt->asp_ratio - (((rt->w.height - rt->w.width) / (double)rt->w.width) / 2);
	}
	else
	{
		dir->x = (pixel->x + 0.5) / rt->w.width;
		dir->y = ((rt->w.height - pixel->y) + 0.5) / rt->w.height;
	}
}

void	scene(t_rtv1 *rt)
{
	t_xy		pixel;
	t_xy		dir;
	int			this;
	t_ray		ray;
	t_light		light;
	double		*intersects;
	t_ray		intersection;
	int			index;

	light.pos = (t_vert){-7, 10, -10};
	light.clr = (t_rgb){0xff, 0xff, 0xff};
	pixel.y = -1;
	while(++pixel.y < rt->w.height)
	{
		pixel.x = -1;
		while(++pixel.x < rt->w.width)
		{
			this = pixel.y * rt->w.width + pixel.x;
			setxy(rt, &dir, &pixel);
			ray.origin = rt->cam.pos;
			ray.dir = normalize(add_vert(rt->cam.dir, add_vert(mult_vert(rt->cam.right, dir.x - 0.5), mult_vert(rt->cam.down, dir.y - 0.5))));
			intersects = findintersects(ray, rt);
			if ((index = winningobject(intersects, rt->nodes)) != -1)
			{
				intersection.origin = add_vert(ray.origin, mult_vert(ray.dir, intersects[index]));
				intersection.dir = ray.dir;
			}
			putpixel(rt, pixel.x, pixel.y, color_at(&intersection, index, rt, &light));
			ft_memdel((void**)&intersects);
		}
	}
}
