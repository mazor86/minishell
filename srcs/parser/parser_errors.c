/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:57:19 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 19:41:41 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** displays an error
**
** @param *all general structure
** @param *text error text
** @return 1
*/

static int	ret_err(t_all *all, char *text)
{
	all->res = 2;
	return (ft_error(NULL, text, 1, all));
}

/*
** Handles syntax errors
**
** @param *all general structure
** @param *lst command pointer
** @return 0 if no error was found, 1 error was found
*/

static int	parser_syntax_errors2(t_all *all, t_cmd *lst)
{
	if (!ft_strncmp(lst->name, "", 1))
	{
		if (lst->next && !ft_strncmp((lst->next)->name, "", 1))
		{
			if (lst->pipe &&
				(lst->next)->pipe)
				return (ret_err(all, "syntax error \"||\""));
			else
				return (ret_err(all, "syntax error \";;\""));
		}
		if (lst->pipe)
			return (ret_err(all, "syntax error \"|\""));
		else
			return (ret_err(all, "syntax error \";\""));
	}
	return (0);
}

/*
** Handles syntax errors
**
** @param *all general structure
** @return 0 if no error was found, 1 error was found
*/

int			parser_syntax_errors(t_all *all)
{
	t_cmd	*lst;
	int		check;

	check = 1;
	lst = all->cmd;
	while (lst)
	{
		//if (lst == all->cmd && !ft_strncmp(lst->name,
		if (check == 1 && !ft_strncmp(lst->name,
			"", 1) && lst->pipe)
		{
			check = 0;
			if (lst->next && !ft_strncmp((lst->next)->name,
				"", 1) && (lst->next)->pipe)
				return (ret_err(all, "syntax error \"||\""));
			else
				return (ret_err(all, "syntax error \"|\""));
		}
		if (parser_syntax_errors2(all, lst) == 1)
			return (1);
		lst = lst->next;
	}
	return (0);
}
