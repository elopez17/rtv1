#include <rtv1.h>

void	render(t_rtv1 *rt)
{
	mlx_clear_window(rt->mlx, rt->win);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
}
