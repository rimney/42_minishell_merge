/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:47:44 by rimney            #+#    #+#             */
/*   Updated: 2022/07/05 23:04:28 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while(str[i])
        write(fd, &str[i++], 1);
}

int ft_path_exists(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (1);
        i++;
    }
    return (0);
}

void    ft_execute_command(t_exec *exec, int index)
{
    char **command_parser;


    command_parser = ft_split(exec->command[index], ' ');

    if(ft_is_a_builtin(command_parser[0]))
    {
        ft_execute_builtin(command_parser, exec, index);
        ft_free(command_parser);
        exit(0);
    }
    else
    {
        if(execve(ft_exec_command(exec->envp, command_parser[0]), command_parser, exec->envp) == -1)
        {
            perror(exec->command[index]);
            ft_free(command_parser);
            exit(127);
        }
    }
    ft_free(command_parser);
}