#include <rtv1.h>

t_rgb	getcolor(const char *line)
{
	t_rgb	color;

	color = (t_rgb){255, 255, 255};
	if ((line = ft_strrchr(line, '(')) == NULL)
		rtv1_error(2);
	color.red = ft_atoi(++line);
	if ((line = ft_strchr(line, ',')) == NULL)
		rtv1_error(2);
	color.green = ft_atoi(++line);
	if ((line = ft_strchr(line, ',')) == NULL)
		rtv1_error(2);
	color.blue = ft_atoi(++line);
	return (color);
}

t_union	getsphere(t_rtv1 *rt)
{
	char	*line;
	t_union	u;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "origin"))
			u.sphere.pos = getxyz(line);
		else if (ft_strstr(line, "color"))
			u.sphere.clr = getcolor(line);
		else if (ft_strstr(line, "radius"))
			u.sphere.radius = ft_atoi(ft_strchr(line, '(') + 1);
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
		{
			ft_strdel(&line);
			rtv1_error(2);
		}
		ft_strdel(&line);
	}
	return (u);
}

t_union	getplane(t_rtv1 *rt)
{
	char	*line;
	t_union	u;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "origin"))
			u.plane.norm = getxyz(line);
		else if (ft_strstr(line, "color"))
			u.plane.clr = getcolor(line);
		else if (ft_strstr(line, "distance"))
			u.plane.dist = ft_atod(ft_strchr(line, '(') + 1);
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
		{
			ft_strdel(&line);
			rtv1_error(2);
		}
		ft_strdel(&line);
	}
	return (u);
}

void	getcylinder(t_rtv1 *rt)
{
	char	*line;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "origin"))
			;//rt-> = getxyz(line);
		else if (ft_strstr(line, "color"))
			;
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
		{
			ft_strdel(&line);
			rtv1_error(2);
		}
		ft_strdel(&line);
	}
}

void	getcone(t_rtv1 *rt)
{
	char	*line;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "origin"))
			;//rt-> = getxyz(line);
		else if (ft_strstr(line, "color"))
			;
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
		{
			ft_strdel(&line);
			rtv1_error(2);
		}
		ft_strdel(&line);
	}
}
