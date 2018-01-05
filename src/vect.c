#include <rtv1.h>

t_vect	normalize(t_vect v)
{
	double	magnitude;

	magnitude = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	if (magnitude == 0)
		magnitude = 1;
	return ((t_vect){v.x / magnitude, v.y / magnitude, v.z / magnitude});
}

t_vect	invert(t_vect v)
{
	return ((t_vect){-v.x, -v.y, -v.z});
}

double	dot_prod(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vect	cross_prod(t_vect v1, t_vect v2)
{
	return ((t_vect){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, 
			v1.x * v2.y - v1.y * v2.x});
}

t_vect	add_vect(t_vect v1, t_vect v2)
{
	return ((t_vect){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}
