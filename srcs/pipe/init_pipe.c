/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 04:10:03 by tisabel           #+#    #+#             */
/*   Updated: 2021/01/21 02:31:31 by tisabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     execve_with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
    char	*fullname;

    fullname = NULL;
    if (!(envp = deconvert_env(all)) ||
        !(argv = convert_argv(cmd)))
        return (free_local(envp, argv, &fullname, -1));
    if (!(fullname = get_full_cmd_name(all, cmd)))
        return (free_local(envp, argv, &fullname, 0));
    if (execve(fullname, argv, envp) == -1)
        exit(ft_error(cmd->name, ": permission denied", 13, all));
    free_local(envp, argv, &fullname, 0);
    exit(0);
}

int     exec_command_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
    pid_t	pid;
    int res_cmd;

    pipe(all->pipe_fd);
    if ((pid = fork()) == -1)
        return (ft_error(cmd->name, ": failed to fork", 13, all));
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (pid == 0)
    {
        open_pipe_fd(all);
        init_signals(all, 'c');
        if ((res_cmd = start_cmd(all, cmd)) > 0)
            exit(all->exit_status);
        if (res_cmd == -1)
            execve_with_pipe(all, cmd, argv, envp);
        exit(0);
    }
    else
    {
        waitpid(pid, &all->res, 0);
    }
    init_signals(all, 'p');
    close_pipe_fd(all);
    return (all->exit_status);
}

int     with_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
    if (cmd->redir[0] != '\0')
    {
        if (init_redirect(all, cmd, argv, envp) != 0)
            return (all->exit_status);
        while (cmd->next->redir[0] != '\0')
            cmd = cmd->next;
    }
    else
        if (exec_command_pipe(all, cmd, argv, envp) != 0)
            return (all->exit_status);
    return (all->exit_status);
}

int     no_pipe(t_all *all, t_cmd *cmd, char **argv, char **envp)
{
    if (cmd->redir[0] != '\0')
    {
        if (init_redirect(all, cmd, argv, envp) != 0)
            return (all->exit_status);
        while (cmd->next->redir[0] != '\0')
            cmd = cmd->next;
    }
    else
    {
        if (exec_command(all, cmd, argv, envp) != 0)
            return (all->exit_status);
    }
    return (all->exit_status);
}
