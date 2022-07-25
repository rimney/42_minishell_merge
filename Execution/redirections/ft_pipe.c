/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:23 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 06:25:05 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pipe(int in, t_pipe *tpipe, t_exec *exec, int index)
{

    if  (in != -1)
    {
        dup2(in , 0);    
        close(in);
    }
    if (tpipe->fd[1] != -1)
    {
        dup2(tpipe->fd[1] , 1);
        close(tpipe->fd[1]);
    }

    close(tpipe->fd[0]);
        ft_execute_command(exec, index);
}

 void    ft_apply_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index)
 {

    if (in != -1)
    {
        dup2(in, 0);
        close(in);
    }
    if(out != -1)
    {
        dup2(out, 1);
        close(out);
    }
    close(tpipe->fd[0]);
        ft_execute_command(exec, index);
    tpipe->in = 0;
 }

 void   ft_apply_input_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index)
 {
    if(exec->command[index + exec->input_count + 1] != NULL)
        exit(0);
    if(in != -1)
    {
        dup2(in, 0);
        close(in);
    }
    if(out != -1)
    {
        dup2(out, 1);
        close(out);
    }
    tpipe->fd[1] = 0;
    ft_execute_command(exec, index);
 }

int ft_flag_after_pipe(t_exec *exec)
{
    if(exec->redirecion_flag == 1 || exec->append_flag == 1 || exec->input_flag == 1)
        return (1);
    return (0);
}

void    ft_redirect_after_pipe_flag(t_exec *exec, t_pipe *tpipe, int fd, int index, int in_save)
{
    int pid;    

    if(exec->pipe_flag == 1)
        fd = open(exec->command[index + exec->redirection_count + 2], O_CREAT | O_TRUNC | O_RDWR, 0644);
    if(exec->redirecion_flag == 1)
        fd = open(exec->command[index + exec->redirection_count + 2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(exec->append_flag == 1)
        fd = open(exec->command[index + exec->append_count + 2], O_RDWR | O_CREAT | O_APPEND, 0644);
    if(exec->input_flag == 1)
    {
        fd = open(exec->command[index + exec->input_count + 2], O_RDWR);
        pid = fork();
        if(pid == 0)
            ft_apply_input_redirection_after_pipe(fd, -1, tpipe, exec, index + 2);
        return ;
    }
    pid = fork();
    if(pid == 0)
        ft_apply_redirection_after_pipe(in_save, fd, tpipe, exec, index + 2);
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

// int execute_pipe(t_exec *exec, int index, int in,  t_pipe *tpipe)
// {
// 	int in_save;
// 	int pid;
//     int fd;

//     fd = -1;
//     if (exec->command[index + 1] != NULL)
//     {
//         pipe(tpipe->fd);
//         in_save =  tpipe->fd[0];
//     }
//     pid = fork();
//     if (pid == 0)
//     {
// 		ft_pipe(in, tpipe, exec, index);
// 		exit(0);
//     }
//     if (in != -1)
//         close(in);
//     if (tpipe->fd[1] !=  -1)
//         close(tpipe->fd[1]);
//     if(exec->command[index + 1] && (ft_strcmp(exec->command[index + 1], ">") == 0 
//         || ft_strcmp(exec->command[index + 1], ">>") == 0
//             || ft_strcmp(exec->command[index + 1], "<") == 0) && exec->pipe_count > 2)
//     {
//         ft_redirect_after_pipe_flag(exec, tpipe, fd, index - 2, in_save);
//         exec->redirecion_flag = 0;
//         return (index);
//     }
//     if (index < tpipe->max)
//     {
//         if((exec->pipe_flag) && index == tpipe->max - 2)
//             ft_redirect_after_pipe_flag(exec, tpipe, fd, index , in_save);
//         execute_pipe(exec, index + 2, in_save , tpipe);
//     }
// 	waitpid(pid, &exec->env.exit_value, 0);
// 	WIFEXITED(exec->env.exit_value);
//     return index;
// }
