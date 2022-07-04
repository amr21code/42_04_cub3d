/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:07:08 by anruland          #+#    #+#             */
/*   Updated: 2022/07/04 14:15:26 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief returns the absolute value of nbr
 * 
 * @param nbr 
 * @return double 
 */
double	c3d_abs(double nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}

/**
 * @brief devides num by denom, if denom = 0 returns 10^30
 * 
 * @param num 
 * @param denom 
 * @return double 
 */
double	c3d_div(double num, double denom)
{
	if (denom == 0)
		return (pow(10, 30));
	return (num / denom);
}
