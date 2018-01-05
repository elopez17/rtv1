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
		b = dot_prod(plane.norm, add_vect(ray.origin, invert(mult_vect(plane.norm, plane.dist))));
		return (-b / a);
	}
}

t_vect	sphere_norm(t_sphere sphere, t_vect point)
{
	t_vect	normal;

	normal = normalize(add_vect(point, invert(sphere.pos)));
	return (normal);
}

double	findintersphere(t_ray ray, t_sphere sphere)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root[2];

	a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	b = (2 * (ray.origin.x - sphere.pos.x) * ray.dir.x) +
		(2 * (ray.origin.y - sphere.pos.y) * ray.dir.y) +
		(2 * (ray.origin.z - sphere.pos.z) * ray.dir.z);
	c = pow(ray.origin.x - sphere.pos.x, 2) +
		pow(ray.origin.y - sphere.pos.y, 2) +
		pow(ray.origin.z - sphere.pos.z, 2) - (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		root[0] = ((-b - sqrt(discriminant)) / (2 * a));
		root[1] = ((-b + sqrt(discriminant)) / (2 * a));
		if (root[0] >= 0.00000001)
			return (root[0]);
		return ((root[1] >= 0.00000001) ? root[1] : -1);
	}
	return (-1);
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
			intersects[i] = findintercone(ray, objects->u.cone);
		else
			intersects[i] = findintercylinder(ray, objects->u.cylinder);
	}
	return (intersects);
}
