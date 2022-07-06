/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:25 by rimney            #+#    #+#             */
/*   Updated: 2022/07/06 00:30:15 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    redirect(t_exec *exec, int command_location, int index)
{
    printf("%s <DDD<\n", exec->command[index]);
    index = open(exec->command[index], O_RDONLY);
    //printf()
    dup2(index, 0);
    close(index);
    ft_execute_command(exec, command_location);
    
}

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

int    ft_redirect_input(t_exec *exec, int index, int command_location)
{
    int i;
    int input_file = 0;
    int pid;

    i = index;
    if(input_file == -1)
    {
        perror("minishell error");
        return 0;
    }
    if(ft_strcmp(exec->command[i], "<") == 0)
    {
        input_file = exec->input_count + i - 1;
            pid = fork();
            if (pid == 0)
                redirect(exec, command_location, index + 1);
           
    }
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
    return (i - 1);
}