/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazor <mazor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:17:52 by mazor             #+#    #+#             */
/*   Updated: 2021/03/12 23:53:30 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*i;

	if (!lst || !f || !del)
		return (NULL);
	if (!(i = ft_lstnew(f(lst->content))))
		return (NULL);
	res = i;
	lst = lst->next;
	while (lst)
	{
		if (!(i = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, i);
		lst = lst->next;
	}
	return (res);
}
