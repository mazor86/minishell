/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:38:46 by tisabel           #+#    #+#             */
/*   Updated: 2020/11/30 22:56:11 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** name = name of the command
** flag = if there are any flags in the command
** argum = argunents of the command
** tail = if there is something left in the read line
** 
*/

typedef struct		s_var
{
	char			*name;
	char			*value;
}					t_var;

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
