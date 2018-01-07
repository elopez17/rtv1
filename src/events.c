#include <rtv1.h>

int		expose_hook(t_rtv1 **rt)
{
	render(*rt);
	return (0);
}

int		key_hook(int key, t_rtv1 **rt)
{
	if (key == KEYESC)
	{
		ft_lstdel((t_list**)&(*rt)->obj, NULL);
		mlx_destroy_image((*rt)->mlx, (*rt)->img);
		mlx_destroy_window((*rt)->mlx, (*rt)->win);
		ft_memdel((void**)rt);
		exit(0);
	}
	return (0);
}

int		close_hook(t_rtv1 **rt)
{
	key_hook(KEYESC, rt);
	return (0);
}
