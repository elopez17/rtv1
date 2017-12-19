#include <rtv1.h>

static int	winningobject(double intersect[2])
{
	double	max;

	if (intersect[0] == -1 && intersect[1] == -1)
		return (-1);
	else if (intersect[0] == -1 && intersect[1] > 0)
	{
		return (1);
	}
	else if (intersect[1] == -1 && intersect[0] > 0)
	{
		return (0);
	}
	else
	{
		max = intersect[0] > intersect[1] ? intersect[0]: intersect[1];
		if (max > 0)
		{
			if (intersect[0] > 0 && intersect[0] <= intersect[1])
				return (0);
			else
				return (1);
		}
		else
			return (-1);
	}
}

void	scene(t_rtv1 *rt)
{
	double		x;
	double		y;
	double		xamt;
	double		yamt;
	int			this;
	double		aspectratio = (double)rt->w.width /(double)rt->w.height;
	t_ray		ray;
	t_sphere	sphere;
	t_plane		plane;
	t_light		light;
	double		intersect[2];
	int			index;

	light.pos = (t_vert){-7, 10, -10};
	light.clr = (t_rgb){0xff, 0xff, 0xff};
	sphere.pos = (t_vert){0, 0, 0};
	sphere.radius = 1;
	sphere.clr = (t_rgb){0x0, 0xff, 0x0};
	plane.norm = (t_vert){0, 1, 0};
	plane.dist = -3;
	plane.clr = (t_rgb){0x7f, 0x7f, 0x7f};
	y = -1;
	while(++y < rt->w.height)
	{
		x = -1;
		while(++x < rt->w.width)
		{
			this = y * rt->w.width + x;
			if (rt->w.width > rt->w.height)
			{
				xamt = ((x + 0.5) / rt->w.width) * aspectratio - (((rt->w.width - rt->w.height) / (double)rt->w.height) / 2);
				yamt = ((rt->w.height - y) + 0.5) / rt->w.height;
			}
			else if (rt->w.height > rt->w.width)
			{
				xamt = (x + 0.5) / rt->w.width;
				yamt = (((rt->w.height - y) + 0.5) / rt->w.height) / aspectratio - (((rt->w.height - rt->w.width) / (double)rt->w.width) / 2);
			}
			else
			{
				xamt = (x + 0.5) / rt->w.width;
				yamt = ((rt->w.height - y) + 0.5) / rt->w.height;
			}
			ray.origin = rt->cam.pos;
			ray.dir = normalize(add_vert(rt->cam.dir, add_vert(mult_vert(rt->cam.right, xamt - 0.5), mult_vert(rt->cam.down, yamt - 0.5))));
			intersect[0] = findinterplane(ray, plane);
			intersect[1] = findintersphere(ray, sphere);
			index = winningobject(intersect);
			if (index == -1)
				putpixel(rt, x, y, 0x0);
			else if (index == 0)
				putpixel(rt, x, y, 0x007f7f7f);
			else
				putpixel(rt, x, y, 0x0000ff00);
		}
	}
}
