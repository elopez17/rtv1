/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 18:33:42 by eLopez            #+#    #+#             */
/*   Updated: 2017/12/13 16:31:59 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	putpixel(t_rtv1 *rt, int x, int y, int color)
{
	int i;

	if (x < 0 || x >= rt->w.width || y < 0 || y >= rt->w.height)
		return ;
	i = (rt->bpp / 8) * x + rt->len * y;
	if (rt->endian == 0)
	{
		rt->addr[i++] = (0x000000ff & color);
		rt->addr[i++] = (0x0000ff00 & color) >> 8;
		rt->addr[i++] = (0x00ff0000 & color) >> 16;
		rt->addr[i++] = (0xff000000 & color) >> 24;
	}
}
