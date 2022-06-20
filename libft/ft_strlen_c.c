/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:03:27 by anruland          #+#    #+#             */
/*   Updated: 2022/05/05 17:39:26 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_c(char *str, char c)
{
	int	str_count;

	str_count = 0;
	while (str[str_count] != c && str[str_count] != '\0')
	{
		str_count++;
	}
	return (str_count);
}
