#include <rtv1.h>

void	render(t_rtv1 *rt)
{
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	mlx_destroy_image(rt->mlx, rt->img);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bpp), &(rt->len), &(rt->endian));
}
