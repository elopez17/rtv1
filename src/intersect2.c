#include <rtv1.h>

t_vect	cone_norm(t_cone cone, t_vect point)
{
	t_vect	normal;

	normal = add_vect(point, invert(cone.pos));
	normal = add_vect(normal, invert(mult_vect(cone.dir, dot_prod(cone.dir, normal))));
	return (normalize(normal));
}

double	findintercone(t_ray ray, t_cone cone)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt[2];
	t_ray	inter;

	a = pow(cos(cone.a), 2) * sqr_vect(diff_vect(ray.dir, mult_vect(cone.dir, dot_prod(ray.dir, cone.dir)))) -
		pow(sin(cone.a), 2) * dot_prod(ray.dir, cone.dir) * dot_prod(ray.dir, cone.dir);
	b = 2 * pow(cos(cone.a), 2) * dot_prod(diff_vect(ray.dir, mult_vect(cone.dir, dot_prod(ray.dir, cone.dir))), 
		diff_vect(diff_vect(ray.origin, cone.pos), mult_vect(cone.dir, dot_prod(diff_vect(ray.origin, cone.pos), cone.dir))))
		- 2 * pow(sin(cone.a), 2) * dot_prod(ray.dir, cone.dir) * dot_prod(diff_vect(ray.origin, cone.pos), cone.dir);
	c = pow(cos(cone.a), 2) * sqr_vect(diff_vect(diff_vect(ray.origin, cone.pos), mult_vect(cone.dir, dot_prod(diff_vect(ray.origin, cone.pos), cone.dir)))) -
		pow(sin(cone.a), 2) * dot_prod(diff_vect(ray.origin, cone.pos), cone.dir) * dot_prod(diff_vect(ray.origin, cone.pos), cone.dir);
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		rslt[0] = (-b - sqrt(d)) / (2 * a);
		rslt[1] = (-b + sqrt(d)) / (2 * a);
		inter.dir = ray.dir;
		inter.origin = add_vect(ray.origin, mult_vect(ray.dir, rslt[0]));
		if (cone.h - len_vect(diff_vect(diff_vect(inter.origin, cone.pos)
, diff_vect(diff_vect(inter.origin, cone.pos), mult_vect(cone.dir,
dot_prod(cone.dir, diff_vect(inter.origin, cone.pos)))))) < 0)
		{
			inter.origin = add_vect(ray.origin, mult_vect(ray.dir, rslt[1]));
			if (cone.h - len_vect(diff_vect(diff_vect(inter.origin, cone.pos)
, diff_vect(diff_vect(inter.origin, cone.pos), mult_vect(cone.dir,
dot_prod(cone.dir, diff_vect(inter.origin, cone.pos)))))) < 0)
				return (-1);
		}
		if (rslt[0] >= 0.00000001)
			return (rslt[0]);
		return ((rslt[1] >= 0.00000001) ? rslt[1] : -1);
	}
	return (-1);
}

t_vect	cylinder_norm(t_cylinder cylinder, t_vect point)
{
	t_vect	normal;

	normal = diff_vect(point, cylinder.pos);
	normal = diff_vect(normal, mult_vect(cylinder.dir, dot_prod(cylinder.dir, normal)));
	return (normalize(normal));
}

double	findintercylinder(t_ray ray, t_cylinder cylinder)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	rslt[2];
	t_ray	inter;

	a = sqr_vect(diff_vect(ray.dir, mult_vect(cylinder.dir, 
					dot_prod(ray.dir, cylinder.dir))));
	b = 2 * dot_prod(diff_vect(ray.dir, mult_vect(cylinder.dir, 
dot_prod(ray.dir, cylinder.dir))), diff_vect(diff_vect(ray.origin, cylinder.pos)
, mult_vect(cylinder.dir, dot_prod(diff_vect(ray.origin, cylinder.pos), 
cylinder.dir))));
	c = sqr_vect(diff_vect(diff_vect(ray.origin, cylinder.pos), mult_vect(cylinder.dir, 
		dot_prod(diff_vect(ray.origin, cylinder.pos), cylinder.dir)))) - cylinder.radius * cylinder.radius;
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		rslt[0] = (-b - sqrt(d)) / (2 * a);
		rslt[1] = (-b + sqrt(d)) / (2 * a);
		inter.dir = ray.dir;
		inter.origin = add_vect(ray.origin, mult_vect(ray.dir, rslt[0]));
		if (cylinder.h - len_vect(diff_vect(diff_vect(inter.origin, cylinder.pos)
, mult_vect(cylinder_norm(cylinder, inter.origin), cylinder.radius))) < 0)
		{
			inter.origin = add_vect(ray.origin, mult_vect(ray.dir, rslt[1]));
			if (cylinder.h - len_vect(diff_vect(diff_vect(inter.origin, cylinder.pos)
, mult_vect(cylinder_norm(cylinder, inter.origin), cylinder.radius))) < 0)
				return (-1);
		}
		if (rslt[0] >= 0.00000001)
			return (rslt[0]);
		return ((rslt[1] >= 0.00000001) ? rslt[1] : -1);
	}
	return (-1);
}
