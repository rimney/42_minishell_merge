/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:25 by rimney            #+#    #+#             */
/*   Updated: 2022/07/21 06:48:04 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_advanced_redirect_input(t_exec *exec, int fd_in, int index)
{
    int pid;
    int location;

    location = index - 1;
    pid = fork();
    if(pid == 0)
    {
        while(index < exec->input_count)
        {
            fd_in = open(exec->command[index + 1], O_RDONLY);
            if(index + 1 == exec->input_count)
            {
                if(exec->command[index + 2])
                    exit(0);
                dup2(fd_in, 0);
                close(fd_in);
                ft_execute_command(exec, location);
            }
            index += 2;
        }
    }
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
    return (1);
}

int    ft_minishell_input_final_case(t_exec *exec, int index)
{
    char **parser;
    int in;
    int fd;
    int pid;

    parser = ft_split(exec->command[1], ' ');
    in = open(parser[0], O_RDONLY);
    if(exec->command[2] && ft_is_another_flag(exec, 2) == PIPE)
    {
        ft_free(parser);
        return (index);
    }
    else
    {
    ft_find_next_flag(exec, &index, &fd, &in);
    if(ft_count_elements(parser) == 1)
        return (1);
    exec->in = in;
    pid = fork();
    if(pid == 0)
    {
        in = open(parser[0], O_RDONLY);
        dup2(in, 0);
        close(in);
        dup2(fd, 1);
        close(fd);
        execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
    }
    else
        waitpid(pid, 0, 0);
        ft_free(parser);
    }
    return (index);
}

int	ft_redirect_input(int index, t_exec *exec, int command_location)
{
	int fd;
	int in;
	int pid;
	int s_flag;
    char **parser;

	s_flag = 0;
    fd = -1;
    if(ft_is_another_flag(exec, 0) == REDIRIN)
        return (ft_minishell_input_final_case(exec, index));
    else if(exec->command[index] && ft_is_another_flag(exec, 1) == REDIRIN)
    {
            printf("DDD\n");
        while(index < exec->input_count)
        {
            in = open(exec->command[index + 1], O_RDONLY);
            exec->in = in;
            if(ft_is_another_flag(exec, 1) == REDIRIN && exec->command[index + exec->input_count] && ft_is_another_flag(exec, index + exec->input_count) == PIPE)
                return (index);
            if(ft_find_next_flag(exec, &index, &fd, &in))
                s_flag = 1;
            if(exec->error_flag)
            {
                exec->error_flag = 0;
                return (0);
            }
            if((index + 1 == exec->input_count || s_flag))
            {
                pid = fork();
                if(pid == 0)
                {
                    dup2(in, 0);
                    close(in);
                    if(fd != -1)
                    {
                        dup2(fd, 1);
                        close(fd);
                    }
                    ft_execute_command(exec, command_location);
                }
            }
            index += 2;
        }
    }
    else
        return (printf("ee\n"), index);
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
	return (index);
}