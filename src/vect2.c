#include <rtv1.h>

t_vert	mult_vert(t_vert v, double scalar)
{
	return ((t_vert){v.x * scalar, v.y * scalar, v.z * scalar});
}

t_vert	diff_vert(t_vert v1, t_vert v2)
{
	return ((t_vert){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

double	sqr_vert(t_vert v)
{
	return (dot_prod(v, v));
}

double	len_vert(t_vert v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
