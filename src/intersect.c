#include <rtv1.h>

double	findinterplane(t_ray ray, t_vert norm)
{
	double	a;
	double	b;

	a = dot_prod(ray.dir, norm);
	if (a == 0)
		return (-1);
	else
	{
		b = dot_prod(norm, add_vert(ray.origin, invert(mult_vert(norm, a))));
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
