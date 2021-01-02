/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2020/12/22 10:35:39 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/29 16:49:19 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** displays a complete list of all environment variables
**
** @param *all general structure
*/

static void	show_all_env(t_all *all)
{
	t_list	*lst;

	lst = all->env;
	while (lst)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_env*)lst->content)->name, 1);
		if (((t_env*)lst->content)->par)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_env*)lst->content)->par, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
}

/*
** re-updates the value of an environment variable
**
** @param *all general structure
** @param *text export command argument
** @return 0 if good, otherwise -1
*/

static int	update_env_local(t_all *all, char *text)
{
	char	*name;
	char	*par;
	t_env	*tmp;

	name = get_name_env(text);
	par = get_param_env(text);
	if (!(tmp = get_env(all, name)))
	{
		if (add_env(all, name, par) == -1)
			return (-1);
	}
	else
	{
		if (tmp->par)
			free(tmp->par);
		tmp->par = par;
	}
	return (0);
}

/*
** makes a check that the name of the environment variable is valid
**
** @param *text export command argument
** @return 1 is valid, otherwise 0
*/

static int	is_valid_argv(char *text)
{
	if ((text[0] >= 'a' && text[0] <= 'z') || (text[0] >= 'A' && text[0] <= 'Z')
		|| text[0] == '_')
		return (1);
	ft_putstr_fd("export: \"", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\" this is an invalid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

/*
** executes the export command
**
** @param *all general structure
** @param *cmd command structure
** @return 0 if good, otherwise -1
*/

int			ft_export(t_all *all, t_cmd *cmd)
{
	int		i;

	i = -1;
	all->res = 0;
	if (!ft_strncmp(cmd->argv[0], "", 1))
		show_all_env(all);
	else
	{
		while (cmd->argv[++i])
		{
			if (is_valid_argv(cmd->argv[i]))
			{
				if (update_env_local(all, cmd->argv[i]) == -1)
					return (-1);
				all->env = sort_env(all->env);
			}
			else
				all->res = 1;
		}
	}
=======
/*   Created: 2020/11/08 19:46:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/01/01 15:43:39 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Функиця экспорт выводит переменные которым не быбло присвоено значение,
//а функция env нет. Но через export они присваиваются

#include "minishell.h"

int		check_arg(char *argum)
{
	int i;
	int n;

	i = 0;
	while (argum[i] != '\0')
	{
		if (ft_isalpha(argum[i]) == 0 && argum[i] != '_')
			return (-1); // вывод что неправильный аргумент.
		
	}
	return (0);
}

void	add_arg(char *argum, t_var **my_env)
{
	int n;

	(*my_env)->name = ft_strcut(argum, '=');
	if ((n = ft_strfind(argum, "=")) != 0)
		(*my_env)->value = ft_strdup(&argum[n]);
	else
		(*my_env)->value = ft_strdup("");
	(*my_env)->standard = 2;
}

t_var	*copy_env(t_var *my_env)
{
	t_var	*copy;
	int		len;
	int		i;

	len = 0;
	while (my_env[len].name != NULL)
		len++;
	i = 0;
	if (!(copy = (t_var*)malloc(sizeof(t_var) * (len + 1))))
			exit (2);
	while (i < len)
	{
		copy[i].name = ft_strdup(my_env[i].name);
		copy[i].value = ft_strdup(my_env[i].value);
		copy[i].standard = my_env[i].standard;
		i++;
	}
	copy[i].name = NULL;
}

int		count_var(t_var *var)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (var[i].name != NULL)
		len++;
	return (len);
}

void	sort_env(t_var *var)
{
	t_var	tmp;
	int		j;
	int		i;
	int 	s;
	int		num;

	j = 0;
	num = count_var(var);
	while (j < num)
	{
		i = 0;
		while (i < num - j)
		{
			if (var[i].name[0] < var[i + 1].name[0] && var[i + 1].name != NULL
			&& var[i].name != NULL)
			{
				tmp = var[i];
				var[i] = var[i + 1];
				var[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

void	write_var(t_var var_i)
{
	write(1, "declare -x ", 11);
	write(1, var_i.name, ft_strlen(var_i.name));
	write(1, "=", 1);
	write(1, var_i.value, ft_strlen(var_i.value));
	write(1, "\n", 1);
}

int		ft_export(t_data *data, t_var **my_env)
{
	int i;
	t_var *sorted_env;
	int len;

	i = 0;
	if(data->argum[0] == NULL)
	{
		sorted_env = copy_env(*my_env);
		sort_env(&sorted_env);
		while (sorted_env[i].name != NULL)
			if (sorted_env[i].standard != 0)
			{
				write_var(sorted_env[i]);
				i++;
			}
	}
	else
		while (data->argum[i] != NULL)
		{
			check_arg(data->argum[i]);
			add_arg(data->argum[i], my_env);
		}
	free_t_var(&sorted_env);
>>>>>>> tisabel
	return (0);
}
