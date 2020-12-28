/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:49:31 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/28 09:15:18 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name_env(char *env)
{
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

char	*get_param_env(char *env)
{
	int		i;
	int		size;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i])
		i++;
	size = 0;
	while (env[i + size])
		size++;
	if (!size)
		return (NULL);
	return (ft_substr(env, i, size));
}

t_env	*get_env(t_all *all, char *name)
{
	t_list	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env*)tmp->content)->name, name,
			ft_strlen(name) + 1))
			return ((t_env*)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int		add_env(t_all *all, char *name, char *par)
{
	t_env	*tmp;
	t_list	*lst;

	lst = NULL;
	if (!(tmp = malloc(sizeof(t_env))) ||
		!(tmp->name = name))
	{
		if (name)
			free(name);
		return (free_env(&tmp, &lst));
	}
	tmp->par = par;
	if (!(lst = ft_lstnew(tmp)))
	{
		free(name);
		return (free_env(&tmp, &lst));
	}
	ft_lstadd_back(&all->env, lst);
	return (0);
}

int		parser_env(t_all *all, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (add_env(all, get_name_env(env[i]), get_param_env(env[i])) == -1)
			return (-1);
	}
	return (0);
}
