/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:38:46 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/31 02:46:07 by tisabel          ###   ########.fr       */
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

typedef struct		s_var
{
	char			*name;
	char			*value;
	short			standard;
}					t_var;

/*
** name = name of the command
** flag = if there are any flags in the command
** argum = argunents of the command
** tail = if there is something left in the read line
** 
*/

typedef struct		s_data
{
	char			**argum;
	char			*name;
	char			*tail;
	int				pipe;
	int				semicolon;
}					t_data;


typedef struct		s_list
{
	t_data			*content;
	struct s_list	*next;
}					t_list;

#endif
