/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:19:49 by anruland          #+#    #+#             */
/*   Updated: 2022/05/15 11:05:42 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * Checks if the string consists of only digits
 * @param str [char *] string to check for digits
  */
int	ft_isdigit_str(char *str)
{
	int	j;

	j = 0;
	if (str[0] == '-' || str[0] == '+')
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (0);
		j++;
	}
	return (1);
}
