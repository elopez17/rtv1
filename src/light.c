#include <rtv1.h>

t_rgb	checklight2(t_obj *obj, t_ray *intersect, t_light light, int shadow)
{
	t_vect	light_dir;
	t_vect	obj_norm;
	t_rgb	final;
	double	cos_a;

	light_dir = normalize(add_vect(light.pos, invert(intersect->origin)));
	if (obj->type == 3)
	{
		obj_norm = cone_norm(obj->u.cone, intersect->origin);
		cos_a = dot_prod(light_dir, obj_norm) / norm_vect(light_dir) * norm_vect(obj_norm);
		final = colorscalar(obj->u.cone.clr, 0.2);
		if (shadow == 0 && cos_a >= 0.0f && cos_a <= 1.0f)
			final = coloradd(final, colorscalar(colormult(obj->u.cone.clr, light.clr), cos_a));
		return (final);
	}
	else
	{
		obj_norm = cylinder_norm(obj->u.cylinder, intersect->origin);
		cos_a = dot_prod(light_dir, obj_norm) / norm_vect(light_dir) * norm_vect(obj_norm);
		final = colorscalar(obj->u.cylinder.clr, 0.2);
		if (shadow == 0 && cos_a >= 0.0f && cos_a <= 1.0f)
			final = coloradd(final, colorscalar(colormult(obj->u.cylinder.clr, light.clr), cos_a));
		return (final);
	}
}

t_rgb	checklight(t_obj *obj, t_ray *intersect, t_light light, int shadow)
{
	t_vect	light_dir;
	t_vect	obj_norm;
	t_rgb	final;
	double	cos_a;

	light_dir = normalize(add_vect(light.pos, invert(intersect->origin)));
	if (obj->type == 1)
	{
		obj_norm = sphere_norm(obj->u.sphere, intersect->origin);
		cos_a = dot_prod(light_dir, obj_norm);
		final = colorscalar(obj->u.sphere.clr, 0.2);
		if (shadow == 0 && cos_a >= 0.0f && cos_a <= 1.0f)
			final = coloradd(final, colorscalar(colormult(obj->u.plane.clr, light.clr), cos_a));
		return (final);
	}
	else if (obj->type == 2)
	{
		obj_norm = obj->u.plane.norm;
		cos_a = dot_prod(light_dir, obj_norm);
		final = colorscalar(obj->u.plane.clr, 0.2);
		if (shadow == 0)
			final = coloradd(final, colorscalar(colormult(obj->u.plane.clr, light.clr), cos_a));
		return (final);
	}
	return (checklight2(obj, intersect, light, shadow));
}
