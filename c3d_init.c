/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:11:05 by anruland          #+#    #+#             */
/*   Updated: 2022/06/23 16:29:25 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_init_preerr(t_preerr *check)
{
		check->no = 0;
		check->ea = 0;
		check->so = 0;
		check->we = 0;
		check->door = 0;
		check->f = 0;
		check->c = 0;
		check->invalid = 0;
		check->valid = 0;
		check->start_line = 0;
}
