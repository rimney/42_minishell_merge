/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_final_case.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:37:54 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 19:52:59 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int ft_heredoc_final_case_child_1(t_exec *exec, int index, int fd[2], int out)
{
    char *delimiter;
    char **parser;
    int in;


    parser = ft_split(exec->command[index + 1], ' ');
    delimiter = strdup(parser[0]);
    in = fd[0];
    if(exec->heredoc_count > 2)
        ft_find_next_flag(exec, &index, &out, &in);
    exec->in = in;
        close(fd[1]);
        if(out != -1)
        {
            dup2(out, 1);
            close(out);
        }
        dup2(in, 0);
        close(in);
        execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
    return (1);
}

int ft_heredoc_final_case_child_2(t_exec *exec, int index, int fd[2], int out)
{
     char *line;
    char *delimiter;
    char **parser;
    int in;


    parser = ft_split(exec->command[index + 1], ' ');
    delimiter = strdup(parser[0]);
    while((line = readline("final heredoc >")))
    {
        exec->heredoc_flag = 1;
        in = fd[0];
        if(ft_strcmp(line, delimiter) != 0)
        {
            write(fd[1], line, ft_strlen(line));
            write(fd[1], "\n", 1);
        }
        if(ft_strcmp(line, delimiter) == 0)
        {
            out = fd[1];
            // if(exec->args > 2)
            //     ft_find_next_flag_heredoc(exec, &index, &out, &in);
            dup2(in, 0);
            close(in);
            close(fd[1]);
            if(out != -1)
            {
                dup2(out, 1);
                close(out);
            }
            printf("%s ||||<\n", parser[1]);
            if(execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp) == -1)
            {
                perror(exec->command[index]);
                ft_free(parser);
                exit(127);
            }
        }
       free(line);
    }
    return (1);
}

int ft_heredoc_final_case_child(t_exec *exec, int index, int fd[2], int out)
{
    // char *line;
    char *delimiter;
    char **parser;


    parser = ft_split(exec->command[index + 1], ' ');
    delimiter = strdup(parser[0]);
    if(ft_count_elements(parser) <= 2)
        ft_heredoc_final_case_child_2(exec, index, fd, out);
    else
        ft_heredoc_final_case_child_1(exec, index, fd, out);
    return (1);
    
}
