/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:00:54 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/27 21:46:10 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_cd_local(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*item;

	if (!(dir = opendir(path)))
		return (0);
	while ((item = readdir(dir)))
	{
		if (!ft_strncmp(item->d_name, name, ft_strlen(name) + 1))
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static char	*parse_split_local(char **split, t_all *all, t_list *lst)
{
	int		i;
	char	*res;

	i = -1;
	res = NULL;
	while (split[++i])
	{
		if (get_cd_local(split[i], ((t_cmd*)lst->content)->name) == 1)
		{
			if (!(res = ft_strjoin_char(split[i], '/')) ||
				join_str(&res, ((t_cmd*)lst->content)->name) == -1)
			{
				if (res)
					free(res);
				return (NULL);
			}
			return (res);
		}
	}
	ft_error(((t_cmd*)lst->content)->name, ": command not found", 0);
	all->res = 127;
	return (NULL);
}

char		*get_full_cmd_name(t_all *all, t_list *lst)
{
	char	**split;
	t_env	*env;
	char	*res;

	if (ft_strchr(((t_cmd*)lst->content)->name, '/'))
		return (ft_strdup(((t_cmd*)lst->content)->name));
	if (!(env = get_env(all, "PATH")))
		return (NULL);
	if (!(split = ft_split(env->par, ':')))
		return (NULL);
	if (!(res = parse_split_local(split, all, lst)))
		return (free_split(split));
	free_split(split);
	return (res);
}
