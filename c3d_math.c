/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:07:08 by anruland          #+#    #+#             */
/*   Updated: 2022/06/28 12:51:08 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	c3d_abs(double nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}

double	c3d_div(double num, double denom)
{
	if (denom == 0)
		return (pow(10, 30));
	return (num / denom);
}
