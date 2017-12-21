/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:40:22 by eLopez            #+#    #+#             */
/*   Updated: 2017/12/21 12:41:59 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void	straight(t_rtv1 *rt, t_vert a, t_vert b, t_rgb color)
{
	int	route;

	if (a.x == b.x)
	{
		route = a.y > b.y ? -1 : 1;
		while (a.y != b.y)
		{
			putpixel(rt, (int)a.x, (int)a.y, color);
			a.y += route;
		}
	}
	else
	{
		route = a.x > b.x ? -1 : 1;
		while (a.x != b.x)
		{
			putpixel(rt, (int)a.x, (int)a.y, color);
			a.x += route;
		}
	}
}

static void	diagonal_x(t_rtv1 *rt, t_vert a, t_vert b, t_rgb color)
{
	float	slope;
	float	trunc;

	slope = (float)(b.y - a.y) / (float)(b.x - a.x);
	trunc = a.y;
	while (a.x != b.x)
	{
		a.y = trunc;
		trunc += slope;
		++a.x;
		putpixel(rt, (int)a.x, (int)a.y, color);
	}
}

static void	diagonal_y(t_rtv1 *rt, t_vert a, t_vert b, t_rgb color)
{
	float	slope;
	float	trunc;

	slope = (float)(b.x - a.x) / (float)(b.y - a.y);
	trunc = a.x;
	while (a.y != b.y)
	{
		a.x = trunc;
		trunc += slope;
		++a.y;
		putpixel(rt, (int)a.x, (int)a.y, color);
	}
}

void	drawline(t_rtv1 *rt, t_vert *a, t_vert *b, t_rgb color)
{
	if (a->x == b->x || a->y == b->y)
		straight(rt, *a, *b, color);
	else if (fabs(a->x - b->x) >= fabs(a->y - b->y))
	{
		if (a->x < b->x)
			diagonal_x(rt, *a, *b, color);
		else
			diagonal_x(rt, *b, *a, color);
	}
	else
	{
		if (a->y < b->y)
			diagonal_y(rt, *a, *b, color);
		else
			diagonal_y(rt, *b, *a, color);
	}
}
