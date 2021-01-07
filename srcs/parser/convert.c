/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:00:31 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/08 00:06:13 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** gets command name from full path
**
** @param *lst command pointer
** @return pointer to the command name, otherwise NULL
*/

static char	*get_filename(t_list *lst)
{
	char	*res;

	if (!(res = ft_strrchr(((t_cmd*)lst->content)->name, '/')))
		return (ft_strdup(((t_cmd*)lst->content)->name));
	return (ft_strdup(++res));
}

/*
** clears strings
**
** @param **split array of strings
** @param **name pointer to string
** @return NULL
*/

static void	*free_argv_local(char **split, char **name)
{
	free_split(split);
	if (name && *name)
		free(*name);
	return (NULL);
}

/*
** converts a list of environment variables to an array of strings
**
** @param *all general structure
** @return pointer to an array of strings, otherwise NULL
*/
/*
char		**convert_env(t_all *all)
{
	t_env	*lst;
	char	**res;
	int		i;

	lst = all->my_env;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	if (!(res = ft_calloc(i + 1, sizeof(char*))))
		return (NULL);
	i = 0;
	lst = all->my_env;
	while (lst)
	{
		if (!(res[i] = ft_strdup(lst->name)) ||
			join_char(&res[i], '=') == -1 ||
			join_str(&res[i], lst->par) == -1)
			return (free_split(res));
		i++;
		lst = lst->next;
	}
	return (res);
}
*/

/*
** converts command arguments to an array of strings
**
** @param *lst argument list
** @return pointer to an array of strings, otherwise NULL
*/

char		**convert_argv(t_cmd *lst)
{
	char	**res;
	char	*name;
	int		i;

	i = 0;
	while (lst->argv[i] &&
		ft_strncmp(lst->argv[i], "", 1))
		i++;
	if (!(res = ft_calloc(i + 2, sizeof(char*))))
		return (NULL);
	if (!(name = get_filename(lst)))
		return (free_split(res));
	if (!(res[0] = ft_strdup(name)))
		return (free_argv_local(res, &name));
	i = -1;
	while (lst->argv[++i])
	{
		if (ft_strncmp(lst->argv[i], "", 1))
		{
			if (!(res[i + 1] = ft_strdup(lst->argv[i])))
				return (free_argv_local(res, &name));
		}
	}
	return (res);
}
