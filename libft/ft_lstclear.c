/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:     mazor <mazor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:01:33 by mazor             #+#    #+#             */
/*   Updated: 2020/12/03 21:22:28 by mazor            ###   ########.fr       */
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
