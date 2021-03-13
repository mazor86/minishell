/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:16:27 by mazor             #+#    #+#             */
/*   Updated: 2021/03/13 02:44:51 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*i;
	t_list	*j;

	i = *lst;
	while (i)
	{
		j = i->next;
		ft_lstdelone(i, del);
		i = j;
	}
	*lst = NULL;
}
