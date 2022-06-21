/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:50:26 by anruland          #+#    #+#             */
/*   Updated: 2022/06/21 16:51:10 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * destroys one single pointer
 * @param str [void *] pointer to free
 */
void	c3d_single_desctruct(void *str)
{
	if (str)
		free(str);
	str = NULL;
}
