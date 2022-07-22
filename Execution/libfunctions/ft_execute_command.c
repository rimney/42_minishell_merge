/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:47:44 by rimney            #+#    #+#             */
/*   Updated: 2022/07/22 05:48:17 by rimney           ###   ########.fr       */
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

char    *ft_filter_command_single_quote(char *temp)
{
    int i;
    int count;
    char *str;
    int j;

    i = 0;
    count = 0;
    j = 0;
    if(temp[0] != '\'')
        return(temp);
    while(temp[i] == '\'')
            i++;
    count = i;
    while(temp[count] != '\'')
        count++;
    str = malloc(sizeof(char) * (count - i) + 1);
    while(temp[i] != '\'')
    {
        str[j] = temp[i];
        j++;
        i++;
    }
    str[i] = 0;
    return (str);
}

void    ft_filter_command_single_quote_2d_array(char **argv)
{
    int i;
    char    *temp;
    i = 0;
    while(argv[i])
    {
        if(argv[i][0] == '\'')
        {
            temp = argv[i];
            argv[i] = ft_filter_command_single_quote(argv[i]);
            free(temp);   
        }
        i++;
    }
}

void    ft_execute_command(t_exec *exec, int index)
{
    char **command_parser;

    command_parser = ft_split(exec->command[index], ' ');
    ft_filter_command_single_quote_2d_array(command_parser);
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