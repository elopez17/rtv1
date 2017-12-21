#include <rtv1.h>

static t_rgb	color_at(int index, t_obj *objects)
{
	t_obj	*tmp;

	if (index == -1)
		return ((t_rgb){0, 0, 0});
	tmp = objects;
	while (--index >= 0)
		tmp = tmp->next;
	if (tmp->type == 1)
		return (tmp->u.sphere.clr);
	else if (tmp->type == 2)
		return (tmp->u.plane.clr);
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
			index = winningobject(intersects, rt->nodes);
			putpixel(rt, pixel.x, pixel.y, color_at(index, rt->obj));
			ft_memdel((void**)&intersects);
		}
	}
}
