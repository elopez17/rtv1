#include <rtv1.h>

t_vert	cone_norm(t_cone cone, t_vert point)
{
	t_vert	normal;

	normal = add_vert(point, invert(cone.pos));
	normal = add_vert(normal, invert(mult_vert(cone.dir, dot_prod(cone.dir, normal))));
	return (normalize(normal));
}

double	findintercone(t_ray ray, t_cone cone)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt[2];

	a = pow(cos(cone.a), 2) * sqr_vert(diff_vert(ray.dir, mult_vert(cone.dir, dot_prod(ray.dir, cone.dir)))) -
		pow(sin(cone.a), 2) * dot_prod(ray.dir, cone.dir) * dot_prod(ray.dir, cone.dir);
	b = 2 * pow(cos(cone.a), 2) * dot_prod(diff_vert(ray.dir, mult_vert(cone.dir, dot_prod(ray.dir, cone.dir))), 
		diff_vert(diff_vert(ray.origin, cone.pos), mult_vert(cone.dir, dot_prod(diff_vert(ray.origin, cone.pos), cone.dir))))
		- 2 * pow(sin(cone.a), 2) * dot_prod(ray.dir, cone.dir) * dot_prod(diff_vert(ray.origin, cone.pos), cone.dir);
	c = pow(cos(cone.a), 2) * sqr_vert(diff_vert(diff_vert(ray.origin, cone.pos), mult_vert(cone.dir, dot_prod(diff_vert(ray.origin, cone.pos), cone.dir)))) -
		pow(sin(cone.a), 2) * dot_prod(diff_vert(ray.origin, cone.pos), cone.dir) * dot_prod(diff_vert(ray.origin, cone.pos), cone.dir);
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		rslt[0] = (-b - sqrt(d)) / (2 * a);
		rslt[1] = (-b + sqrt(d)) / (2 * a);
		if (rslt[0] >= 0.00000001)
			return (rslt[0]);
		return ((rslt[1] >= 0.00000001) ? rslt[1] : -1);
	}
	return (-1);
}

t_vert	cylinder_norm(t_cylinder cylinder, t_vert point)
{
	t_vert	normal;

	normal = diff_vert(point, cylinder.pos);
	normal = diff_vert(normal, mult_vert(cylinder.dir, dot_prod(cylinder.dir, normal)));
	return (normalize(normal));
}

double	findintercylinder(t_ray ray, t_cylinder cylinder)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt[2];

	a = sqr_vert(diff_vert(ray.dir, mult_vert(cylinder.dir, 
					dot_prod(ray.dir, cylinder.dir))));
	b = 2 * dot_prod(diff_vert(ray.dir, mult_vert(cylinder.dir, 
dot_prod(ray.dir, cylinder.dir))), diff_vert(diff_vert(ray.origin, cylinder.pos)
, mult_vert(cylinder.dir, dot_prod(diff_vert(ray.origin, cylinder.pos), 
cylinder.dir))));
	c = sqr_vert(diff_vert(diff_vert(ray.origin, cylinder.pos), mult_vert(cylinder.dir, 
		dot_prod(diff_vert(ray.origin, cylinder.pos), cylinder.dir)))) - cylinder.radius * cylinder.radius;
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		rslt[0] = (-b - sqrt(d)) / (2 * a);
		rslt[1] = (-b + sqrt(d)) / (2 * a);
		if (rslt[0] >= 0.00000001)
			return (rslt[0]);
		return ((rslt[1] >= 0.00000001) ? rslt[1] : -1);
	}
	return (-1);
}
