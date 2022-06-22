/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djedasch <djedasch@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:57:29 by djedasch          #+#    #+#             */
/*   Updated: 2022/06/22 18:00:27 by djedasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char_replace(char *str, char repl, char with)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == repl)
			str[i] = with;
		i++;
	}
}
