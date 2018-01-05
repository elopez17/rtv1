#include <rtv1.h>

t_rgb	getcolor(const char *line)
{
	t_rgb	color;

	color = (t_rgb){0, 0, 0};
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
			u.sphere.radius = ft_atod(ft_strchr(line, '(') + 1);
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
			rtv1_error(2);
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
			rtv1_error(2);
		ft_strdel(&line);
	}
	return (u);
}

t_union	getcylinder(t_rtv1 *rt)
{
	char	*line;
	t_union	u;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "origin"))
			u.cylinder.pos = getxyz(line);
		else if (ft_strstr(line, "direction"))
			u.cylinder.dir = getxyz(line);
		else if (ft_strstr(line, "color"))
			u.cylinder.clr = getcolor(line);
		else if (ft_strstr(line, "radius"))
			u.cylinder.radius = ft_atod(ft_strchr(line, '(') + 1);
		else if (ft_strstr(line, "height"))
			u.cylinder.h = ft_atod(ft_strchr(line, '(') + 1);
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
			rtv1_error(2);
		ft_strdel(&line);
	}
	return (u);
}

t_union	getcone(t_rtv1 *rt)
{
	char	*line;
	t_union u;

	while (get_next_line(rt->fd, &line) > 0)
	{
		if (ft_strstr(line, "origin"))
			u.cone.pos = getxyz(line);
		else if (ft_strstr(line, "direction"))
			u.cone.dir = normalize(getxyz(line));
		else if (ft_strstr(line, "color"))
			u.cone.clr = getcolor(line);
		else if (ft_strstr(line, "angle"))
			u.cone.a = (M_PI / 180) * ft_atod(ft_strchr(line, '(') + 1);
		else if (ft_strstr(line, "height"))
			u.cone.h = ft_atod(ft_strchr(line, '(') + 1);
		else if (ft_strrchr(line, '}'))
		{
			ft_strdel(&line);
			break ;
		}
		else
			rtv1_error(2);
		ft_strdel(&line);
	}
	return (u);
}
