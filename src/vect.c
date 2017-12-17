#include <rtv1.h>

t_vert	normalize(t_vert v)
{
	double	magnitude;

	magnitude = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return ((t_vert){v.x / magnitude, v.y / magnitude, v.z / magnitude});
}

t_vert	invert(t_vert v)
{
	return ((t_vert){-v.x, -v.y, -v.z});
}

double	dot_prod(t_vert v1, t_vert v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vert	cross_prod(t_vert v1, t_vert v2)
{
	return ((t_vert){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, 
			v1.x * v2.y - v1.y * v2.x});
}

t_vert	add_vert(t_vert v1, t_vert v2)
{
	return ((t_vert){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}
