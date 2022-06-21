/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:04:04 by anruland          #+#    #+#             */
/*   Updated: 2022/06/21 17:05:03 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(char c)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (c == 32)
			return (1);
		i++;
	}
	return (0);
}

char	*skip_whitespaces(char *str)
{
	while (*str != '\0' && is_whitespace(*str))
		str++;
	return (str);
}
