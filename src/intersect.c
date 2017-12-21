#include <rtv1.h>

double	findinterplane(t_ray ray, t_plane plane)
{
	double	a;
	double	b;

	a = dot_prod(ray.dir, plane.norm);
	if (a == 0)
		return (-1);
	else
	{
		b = dot_prod(plane.norm, add_vert(ray.origin, invert(mult_vert(plane.norm, plane.dist))));
		return (-1 * b / a);
	}
}

t_vert	sphere_norm(t_sphere sphere, t_vert point)
{
	t_vert	normal;

	normal = normalize(add_vert(point, invert(sphere.pos)));
	return (normal);
}

double	findintersphere(t_ray ray, t_sphere sphere)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;

	a = 1;
	b = (2 * (ray.origin.x - sphere.pos.x) * ray.dir.x) + (2 * (ray.origin.y - sphere.pos.y) * ray.dir.y) + (2 * (ray.origin.z - sphere.pos.z) * ray.dir.z);
	c = pow(ray.origin.x - sphere.pos.x, 2) + pow(ray.origin.y - sphere.pos.y, 2) + pow(ray.origin.z - sphere.pos.z, 2) - (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * c;
	if (discriminant > 0)
	{
		root = ((-1 * b - sqrt(discriminant)) / 2) - 0.0000001;
		if (root > 0)
		{
			return (root);
		}
		else
		{
			root = ((sqrt(discriminant) - b) / 2) - 0.0000001;
			return (root);
		}
	}
	else
	{
		return (-1);
	}
}

double	*findintersects(t_ray ray, t_rtv1 *rt)
{
	double	*intersects;
	int		i;
	t_obj	*objects;

	i = -1;
	objects = rt->obj;
	intersects = (double*)malloc(sizeof(double) * rt->nodes);
	while (++i < rt->nodes)
	{
		(i != 0) ? objects = objects->next : 0;
		if (objects->type == 1)
			intersects[i] = findintersphere(ray, objects->u.sphere);
		else if (objects->type == 2)
			intersects[i] = findinterplane(ray, objects->u.plane);
		else if (objects->type == 3)
			;//intersects[i] = findintercone(ray, objects->u.cone);
		else
			;//intersects[i] = findintercylinder(ray, objects->u.cylinder);
	}
	return (intersects);
}
