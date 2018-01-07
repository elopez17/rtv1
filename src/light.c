/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 17:36:04 by eLopez            #+#    #+#             */
/*   Updated: 2018/01/06 18:14:30 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_rgb	checklight2(t_obj *obj, t_ray *intersect, t_vect light, int shadow)
{
	t_vect	light_dir;
	t_vect	obj_norm;
	t_rgb	final;
	double	cos_a;

	light_dir = normalize(add_vect(light, invert(intersect->origin)));
	if (obj->type == 3)
	{
		obj_norm = cone_norm(obj->u.cone, intersect->origin);
		cos_a = dot_prod(light_dir, obj_norm) / norm_vect(light_dir) * norm_vect(obj_norm);
		final = colorscalar(obj->u.cone.clr, 0.2);
		if (shadow == 0 && cos_a >= 0.0f && cos_a <= 1.0f)
			final = coloradd(final, colorscalar(obj->u.cone.clr, cos_a));
		return (final);
	}
	else
	{
		obj_norm = cylinder_norm(obj->u.cylinder, intersect->origin);
		cos_a = dot_prod(light_dir, obj_norm) / norm_vect(light_dir) * norm_vect(obj_norm);
		final = colorscalar(obj->u.cylinder.clr, 0.2);
		if (shadow == 0 && cos_a >= 0.0f && cos_a <= 1.0f)
			final = coloradd(final, colorscalar(obj->u.cylinder.clr, cos_a));
		return (final);
	}
}

t_rgb	checklight(t_obj *obj, t_ray *intersect, t_vect light, int shadow)
{
	t_vect	light_dir;
	t_vect	obj_norm;
	t_rgb	final;
	double	cos_a;

	light_dir = normalize(add_vect(light, invert(intersect->origin)));
	if (obj->type == 1)
	{
		obj_norm = sphere_norm(obj->u.sphere, intersect->origin);
		cos_a = dot_prod(light_dir, obj_norm);
		final = colorscalar(obj->u.sphere.clr, 0.2);
		if (shadow == 0 && cos_a >= 0.0f && cos_a <= 1.0f)
			final = coloradd(final, colorscalar(obj->u.sphere.clr, cos_a));
		return (final);
	}
	else if (obj->type == 2)
	{
		obj_norm = obj->u.plane.norm;
		cos_a = dot_prod(light_dir, obj_norm);
		final = colorscalar(obj->u.plane.clr, 0.2);
		if (shadow == 0 && -cos_a >= 0.0f && -cos_a <= 1.0f)
			final = coloradd(final, colorscalar(obj->u.plane.clr, -cos_a));
		return (final);
	}
	return (checklight2(obj, intersect, light, shadow));
}
