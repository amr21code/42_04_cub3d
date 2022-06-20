/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruland <anruland@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:40:56 by anruland          #+#    #+#             */
/*   Updated: 2022/03/30 16:45:11 by anruland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc) and returns a new element. The variable 'content'
	is initialized with the value of the parameter 'content'.
	The variable 'next' is initialized to NULL */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	if (content == NULL)
		list->content = 0;
	else
		list->content = content;
	list->next = 0;
	return (list);
}
