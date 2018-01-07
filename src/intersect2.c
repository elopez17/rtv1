/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:06:13 by eLopez            #+#    #+#             */
/*   Updated: 2018/01/06 18:53:41 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	pickinter(double inter0, double inter1)
{
	if (inter0 >= 0.00000001)
		return (inter0);
	return ((inter1 >= 0.00000001) ? inter1 : -1);
}


t_vect	cone_norm(t_cone cone, t_vect point)
{
	t_vect	normal;

	normal = add_vect(point, invert(cone.pos));
	normal = add_vect(normal, invert(mult_vect(cone.dir, dot_prod(cone.dir,
						normal))));
	return (normalize(normal));
}

double	findintercone(t_ray ray, t_cone cone)
{
	t_quad	q;
	t_vect	inter;

	q.a = pow(cos(cone.a), 2) * sqr_vect(diff_vect(ray.dir, mult_vect(cone.dir,
dot_prod(ray.dir, cone.dir)))) - pow(sin(cone.a), 2) * dot_prod(ray.dir,
cone.dir) * dot_prod(ray.dir, cone.dir);
	q.b = 2 * pow(cos(cone.a), 2) * dot_prod(diff_vect(ray.dir, mult_vect(
cone.dir, dot_prod(ray.dir, cone.dir))), diff_vect(diff_vect(ray.origin,
cone.pos), mult_vect(cone.dir, dot_prod(diff_vect(ray.origin, cone.pos),
cone.dir)))) - 2 * pow(sin(cone.a), 2) * dot_prod(ray.dir, cone.dir) *
dot_prod(diff_vect(ray.origin, cone.pos), cone.dir);
	q.c = pow(cos(cone.a), 2) * sqr_vect(diff_vect(diff_vect(ray.origin,
cone.pos), mult_vect(cone.dir, dot_prod(diff_vect(ray.origin, cone.pos),
cone.dir)))) - pow(sin(cone.a), 2) * dot_prod(diff_vect(ray.origin, cone.pos),
cone.dir) * dot_prod(diff_vect(ray.origin, cone.pos), cone.dir);
	if ((q.d = q.b * q.b - 4 * q.a * q.c) < 0)
		return (-1);
	q.rslt[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
	q.rslt[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
	inter = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[0]));
	if (cone.h - len_vect(diff_vect(diff_vect(inter, cone.pos), diff_vect(
diff_vect(inter, cone.pos), mult_vect(cone.dir,
dot_prod(cone.dir, diff_vect(inter, cone.pos)))))) < 0)
	{
		inter = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[1]));
		if (cone.h - len_vect(diff_vect(diff_vect(inter, cone.pos)
, diff_vect(diff_vect(inter, cone.pos), mult_vect(cone.dir,
dot_prod(cone.dir, diff_vect(inter, cone.pos)))))) < 0)
			return (-1);
	}
	return (pickinter(q.rslt[0], q.rslt[1]));
}

t_vect	cylinder_norm(t_cylinder cylinder, t_vect point)
{
	t_vect	normal;

	normal = diff_vect(point, cylinder.pos);
	normal = diff_vect(normal, mult_vect(cylinder.dir, dot_prod(cylinder.dir,
					normal)));
	return (normalize(normal));
}

double	findintercylinder(t_ray ray, t_cylinder cyl)
{
	t_quad	q;
	t_vect	inter;

	q.a = sqr_vect(diff_vect(ray.dir, mult_vect(cyl.dir,
					dot_prod(ray.dir, cyl.dir))));
	q.b = 2 * dot_prod(diff_vect(ray.dir, mult_vect(cyl.dir,
dot_prod(ray.dir, cyl.dir))), diff_vect(diff_vect(ray.origin, cyl.pos)
, mult_vect(cyl.dir, dot_prod(diff_vect(ray.origin, cyl.pos),
cyl.dir))));
	q.c = sqr_vect(diff_vect(diff_vect(ray.origin, cyl.pos),
mult_vect(cyl.dir, dot_prod(diff_vect(ray.origin, cyl.pos),
cyl.dir)))) - cyl.radius * cyl.radius;
	if ((q.d = q.b * q.b - 4 * q.a * q.c) < 0)
		return (-1);
	q.rslt[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
	q.rslt[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
	inter = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[0]));
	if (cyl.h - len_vect(diff_vect(diff_vect(inter, cyl.pos)
, mult_vect(cylinder_norm(cyl, inter), cyl.radius))) < 0)
	{
		inter = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[1]));
		if (cyl.h - len_vect(diff_vect(diff_vect(inter, cyl.pos)
, mult_vect(cylinder_norm(cyl, inter), cyl.radius))) < 0)
			return (-1);
	}
	return (pickinter(q.rslt[0], q.rslt[1]));
}
