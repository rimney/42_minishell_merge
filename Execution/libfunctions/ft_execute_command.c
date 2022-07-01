/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:47:44 by rimney            #+#    #+#             */
/*   Updated: 2022/07/01 20:03:13 by rimney           ###   ########.fr       */
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

int is_a_builtin(char *command, char **command_parser, int index, t_exec *exec)
{
    if(ft_strcmp(command, "echo") == 0)
        printf("ECHO\n");
    if(ft_strcmp(command, "export") == 0)
        ft_export(command_parser, index);
    if(ft_strcmp(command, "cd") == 0)
        printf("cd\n");
    if(ft_strcmp(command, "unset") == 0)
        printf("unset\n");
    if(ft_strcmp(command, "pwd") == 0)
        printf("pwd\n");
    if(ft_strcmp(command, "exit") == 0)
        printf("exit\n");
    if(ft_strcmp(command, "env") == 0)
        ft_env(exec->envp);
    return (1);
}

void    ft_execute_command(t_exec *exec, int index)
{
    char **command_parser;

    command_parser = ft_split(exec->command[index], ' ');
    if(is_a_builtin(command_parser[0], command_parser, index, exec))
    {
        printf("is_a_builtin\n");
        ft_free(command_parser);
        exit(0);
    }
    if(execve(ft_exec_command(exec->envp, command_parser[0]), command_parser, exec->envp) == -1)
    {
        perror(exec->command[index]);
        ft_free(command_parser);
        exit(127);
    }
    else
        ft_free(command_parser);
}