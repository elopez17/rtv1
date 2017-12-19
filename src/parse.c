#include <rtv1.h>

void	parsefile(t_rtv1 *rt)
{
	char	*line;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "camera") != NULL)
			;//getcam(rt);
		else if (ft_strstr(line, "sphere") != NULL)
			;//getsphere(rt);
		else if (ft_strstr(line, "plane") != NULL)
			;//getplane(rt);
		else if (ft_strstr(line, "cone") != NULL)
			;//getcone(rt);
		else if (ft_strstr(line, "cylinder") != NULL)
			;//getcylinder(rt);
		ft_strdel(&line);
	}
}
