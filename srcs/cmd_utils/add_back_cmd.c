/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:41:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/06 22:45:46 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*res;

	if (lst && new)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			res = ft_lstlast(*lst);
			res->next = new;
		}
	}
}