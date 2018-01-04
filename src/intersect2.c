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
	double	tmp;

	tmp = tan(50 * (PI/180));
	a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) - (pow(ray.dir.z, 2) * tmp);
	b = 2 * ((ray.origin.x - cone.pos.x) * ray.dir.x + 
(ray.origin.y - cone.pos.y) * ray.dir.y - (ray.origin.z - cone.pos.z) * (ray.dir.z * tmp));
	c = pow((ray.origin.x - cone.pos.x), 2) + pow((ray.origin.y - cone.pos.y), 2)
		- (pow((ray.origin.z - cone.pos.z), 2) * tmp);
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		rslt[0] = (-b - sqrt(d)) / (2 * a);
		rslt[1] = (-b + sqrt(d)) / (2 * a);
		rslt[0] = (rslt[1] >= 0 && rslt[1] < rslt[0]) ? rslt[1] : rslt[0];
	}
	else
		rslt[0] = -1;
	return (rslt[0]);
}

double	findintercylinder(t_ray ray, t_cylinder cylinder)
{
	if (ray.dir.x || cylinder.pos.x)
		;
	return (0);
}
