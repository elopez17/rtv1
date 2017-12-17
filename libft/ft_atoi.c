/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:14:52 by elopez            #+#    #+#             */
/*   Updated: 2017/03/23 00:03:01 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int num;

	i = 0;
	num = 0;
	sign = 1;
	while (*(str + i) == ' ' || *(str + i) == '\n' || *(str + i) == '\t' ||
	*(str + i) == '\v' || *(str + i) == '\r' || *(str + i) == '\f')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
		num = num * 10 + (*(str + i++) - '0');
	return (sign * num);
}
