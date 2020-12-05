/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:32:51 by tisabel           #+#    #+#             */
/*   Updated: 2020/12/05 20:13:47 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

int				parce_command(t_data *data, char *line, char ***my_env);
void			parce_line(t_data *data, char *line, char ***my_env);
void			check_name(t_data *data, char ***my_env);
int				parce_s_quotes(char *line, t_data *data, char ***my_env);
int				parce_d_quotes(char *line, t_data *data, char ***my_env);
int             set_var(char *line, t_data *data, char ***my_env);
int             get_var(char *line, t_data *data, char ***my_env);
int             get_ecran(char *line, t_data *data, char ***my_env);
int             get_arg(char *line, t_data *data, char ***my_env);
int             exec_pipe(char *line, t_data *data, char ***my_env);
int             exec_semicolon(char *line, t_data *data, char ***my_env);

#endif