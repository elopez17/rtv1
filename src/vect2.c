#include <rtv1.h>

t_vect	mult_vect(t_vect v, double scalar)
{
	return ((t_vect){v.x * scalar, v.y * scalar, v.z * scalar});
}

t_vect	diff_vect(t_vect v1, t_vect v2)
{
	return ((t_vect){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

double	sqr_vect(t_vect v)
{
	return (dot_prod(v, v));
}

double	len_vect(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
