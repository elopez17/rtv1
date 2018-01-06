/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 20:06:13 by eLopez            #+#    #+#             */
/*   Updated: 2018/01/05 19:37:38 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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
	t_ray	inter;

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
	q.d = q.b * q.b - 4 * q.a * q.c;
	if (q.d >= 0)
	{
		q.rslt[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
		q.rslt[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
		inter.dir = ray.dir;
		inter.origin = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[0]));
		if (cone.h - len_vect(diff_vect(diff_vect(inter.origin, cone.pos)
, diff_vect(diff_vect(inter.origin, cone.pos), mult_vect(cone.dir,
dot_prod(cone.dir, diff_vect(inter.origin, cone.pos)))))) < 0)
		{
			inter.origin = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[1]));
			if (cone.h - len_vect(diff_vect(diff_vect(inter.origin, cone.pos)
, diff_vect(diff_vect(inter.origin, cone.pos), mult_vect(cone.dir,
dot_prod(cone.dir, diff_vect(inter.origin, cone.pos)))))) < 0)
				return (-1);
		}
		if (q.rslt[0] >= 0.00000001)
			return (q.rslt[0]);
		return ((q.rslt[1] >= 0.00000001) ? q.rslt[1] : -1);
	}
	return (-1);
}

t_vect	cylinder_norm(t_cylinder cylinder, t_vect point)
{
	t_vect	normal;

	normal = diff_vect(point, cylinder.pos);
	normal = diff_vect(normal, mult_vect(cylinder.dir, dot_prod(cylinder.dir,
					normal)));
	return (normalize(normal));
}

double	findintercylinder(t_ray ray, t_cylinder cylinder)
{
	t_quad	q;
	t_ray	inter;

	q.a = sqr_vect(diff_vect(ray.dir, mult_vect(cylinder.dir,
					dot_prod(ray.dir, cylinder.dir))));
	q.b = 2 * dot_prod(diff_vect(ray.dir, mult_vect(cylinder.dir,
dot_prod(ray.dir, cylinder.dir))), diff_vect(diff_vect(ray.origin, cylinder.pos)
, mult_vect(cylinder.dir, dot_prod(diff_vect(ray.origin, cylinder.pos),
cylinder.dir))));
	q.c = sqr_vect(diff_vect(diff_vect(ray.origin, cylinder.pos),
mult_vect(cylinder.dir, dot_prod(diff_vect(ray.origin, cylinder.pos),
cylinder.dir)))) - cylinder.radius * cylinder.radius;
	q.d = q.b * q.b - 4 * q.a * q.c;
	if (q.d >= 0)
	{
		q.rslt[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
		q.rslt[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
		inter.dir = ray.dir;
		inter.origin = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[0]));
		if (cylinder.h - len_vect(diff_vect(diff_vect(inter.origin, cylinder.pos)
, mult_vect(cylinder_norm(cylinder, inter.origin), cylinder.radius))) < 0)
		{
			inter.origin = add_vect(ray.origin, mult_vect(ray.dir, q.rslt[1]));
			if (cylinder.h - len_vect(diff_vect(diff_vect(inter.origin,
cylinder.pos), mult_vect(cylinder_norm(cylinder, inter.origin),
cylinder.radius))) < 0)
				return (-1);
		}
		if (q.rslt[0] >= 0.00000001)
			return (q.rslt[0]);
		return ((q.rslt[1] >= 0.00000001) ? q.rslt[1] : -1);
	}
	return (-1);
}
