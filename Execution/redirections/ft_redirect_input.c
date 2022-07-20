/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:25 by rimney            #+#    #+#             */
/*   Updated: 2022/07/20 23:06:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void    redirect(t_exec *exec, )
// {
//     index = open(exec->command[index], O_RDONLY);
//     dup2(in, 0);
//     close(in);
//     ft_execute_command(exec, command_location);
    
// }

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

// int    ft_redirect_input(t_exec *exec, int index, int command_location)
// {
//     int pid;
//     char **parser;
//     int in;

//     in = -1;

//     if(ft_strcmp(exec->command[index], "<") == 0 && i == 0)
//     {
//         parser = ft_split(exec->command[index + 1], ' ');
//         printf("blaaaaaaan");
//         redirect(exec, index + 2, index + 1);
//     }
//     if(ft_strcmp(exec->command[index], "<") == 0)
//     {
//             pid = fork();
//             if (pid == 0)
//                 redirect(exec, command_location, index + 1);
           
//     }
// 	waitpid(pid, &exec->env.exit_value, 0);
// 	WIFEXITED(exec->env.exit_value);
//     return (i - 1);
// }

int    ft_minishell_input_final_case(t_exec *exec, int index)
{
    char **parser;
    int in;
    int fd;
    int pid;


    parser = ft_split(exec->command[1], ' ');
    if(ft_count_elements(parser) == 1)
        return (1);
    in = open(parser[0], O_RDONLY);
    exec->in = in;
    ft_find_next_flag(exec, &index, &fd, &in);
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
            index += 1;
        }
    }
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
	return (index);
}
// }