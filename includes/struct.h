/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:38:46 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/08 18:55:28 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** name = name of the variable
** value = value of the variable
** standard = is it a standard envp variable or added via export (takes values
** 0 if it was added by simply writing in the string, 1 if it is a standart and 2 if it was added via export)
*/

typedef struct		s_env
{
	char			*name;
	char			*value;
	short			standard;
}					t_env;

typedef struct		s_cmd
{
	char			*name;
	char			**argv;
	char			pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_all
{
	t_env			*my_env;
	t_cmd			*cmd;
	char			*line;
	int				pos;
	int				res;
	int				exit_status;
}					t_all;

#endif
