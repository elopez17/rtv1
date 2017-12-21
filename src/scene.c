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

void	scene(t_rtv1 *rt)
{
	double		x;
	double		y;
	double		xamt;
	double		yamt;
	int			this;
	t_ray		ray;
	t_light		light;
	double		*intersects;
	int			index;

	light.pos = (t_vert){-7, 10, -10};
	light.clr = (t_rgb){0xff, 0xff, 0xff};
	y = -1;
	while(++y < rt->w.height)
	{
		x = -1;
		while(++x < rt->w.width)
		{
			this = y * rt->w.width + x;
			if (rt->w.width > rt->w.height)
			{
				xamt = ((x + 0.5) / rt->w.width) * rt->asp_ratio - (((rt->w.width - rt->w.height) / (double)rt->w.height) / 2);
				yamt = ((rt->w.height - y) + 0.5) / rt->w.height;
			}
			else if (rt->w.height > rt->w.width)
			{
				xamt = (x + 0.5) / rt->w.width;
				yamt = (((rt->w.height - y) + 0.5) / rt->w.height) / rt->asp_ratio - (((rt->w.height - rt->w.width) / (double)rt->w.width) / 2);
			}
			else
			{
				xamt = (x + 0.5) / rt->w.width;
				yamt = ((rt->w.height - y) + 0.5) / rt->w.height;
			}
			ray.origin = rt->cam.pos;
			ray.dir = normalize(add_vert(rt->cam.dir, add_vert(mult_vert(rt->cam.right, xamt - 0.5), mult_vert(rt->cam.down, yamt - 0.5))));
			intersects = findintersects(ray, rt);
			index = winningobject(intersects, rt->nodes);
			putpixel(rt, x, y, color_at(index, rt->obj));
			ft_memdel((void**)&intersects);
		}
	}
}
