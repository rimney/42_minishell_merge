/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:21 by rimney            #+#    #+#             */
/*   Updated: 2022/07/21 13:05:14 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_get_last_delimiter(t_exec *exec, int index)
{
    int i;
    int delimiter;


    i = index;
    delimiter = 0;
    while(i < exec->args)
    {
        if(ft_strcmp(exec->command[i], "<<") == 0)
            delimiter = i;
        i++;
    }
    return (delimiter);
}


int ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_loaction)
{
    char *delimiter;
    char *line;
    int out;

    out  = -1;
    delimiter = strdup(exec->command[index + 1]);
    if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == REDIROUT)
    {
        exec->redirection_count = ft_count_till_other_token(exec, index + 2, ">");
         out = open(exec->command[index + exec->redirection_count + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
    }
    while((line = readline("heredoc > ")))
    {
        if (ft_strcmp(line, delimiter) != 0)
        {
            write(fd[1],line,strlen(line));
            write(fd[1], "\n", 1);
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            if(out != -1)
            {
                dup2(out, 1);
                close(out);
            }
            close(fd[1]);
            dup2(fd[0], 0);
           close(fd[0]);
           printf("%s << location\n", exec->command[command_loaction]);
            ft_execute_command(exec, command_loaction);
          }
        free(line);
    }
    free(delimiter);
    return(0); 
}


void ft_heredoc(t_exec *exec, int command_location, int index)
{
    int fd[2];
    pipe(fd);
    ft_exec_heredoc(exec, index, fd, command_location);
    close(fd[0]);
    close(fd[1]);
}

int ft_basic_heredoc(t_exec *exec, int index)
{
    char *line;
    char *delimiter;

    delimiter = strdup(exec->command[index + 1]);
    while((line = readline("heredoc_basic >")))
    {
        if(ft_strcmp(line, delimiter) == 0)
        {
            free(delimiter);
            free(line);
           return (1);
        }
        free(line);
    }
    return (0);
}

void    ft_advanced_heredoc(t_exec *exec, int index, int command_location)
{
    int i;

    i = index;
    printf("%d << location\n", command_location);
    while (i < ft_get_last_delimiter(exec, index) && exec->heredoc_count > 2)
    {
        if (ft_strcmp(exec->command[i], "<<") == 0)
                ft_basic_heredoc(exec, i);
        i += 2;
        index += 2;
    }
    ft_heredoc(exec, command_location, index);    
}


void    ft_heredoc_final_case(t_exec *exec, int index)
{
    char    **parser;
    char    *delimiter;
    char    *line;
    int pid;
    int fd[2];

    parser = ft_split(exec->command[index + 1], ' ');
    delimiter = strdup(parser[0]);
    pipe(fd);
    pid = fork();
    if(pid == 0)
    {
        while((line = readline("final heredoc >")))
        {
            if(ft_strcmp(line, delimiter) != 0)
            {
                write(fd[1], line, ft_strlen(line));
                write(fd[1], "\n", 1);
            }
            if(ft_strcmp(line, delimiter) == 0)
            {
                close(fd[1]);
                dup2(fd[0], 0);
                close(fd[0]);
                execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
            }
            free(line);
        }
    }
    else
    {    
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, 0, 0);
        ft_free(parser);
        free(delimiter);
    }
}

int ft_basic_heredoc_final_case(t_exec *exec, int index)
{
    char *line;
   // char *delimiter;
    char **parser;

    parser = ft_split(exec->command[index + 1], ' ');
    while((line = readline("heredoc_basic >")))
    {
        if(ft_strcmp(line, parser[0]) == 0)
        {
           ft_free(parser);
            free(line);
           return (1);
        }
        free(line);
    }
    return (0);
}

void    ft_advanced_heredoc_final_case(t_exec *exec, int index)
{
    int i;

    i = index;
    while (i < ft_get_last_delimiter(exec, index) && exec->heredoc_count > 2)
    {
        if (ft_strcmp(exec->command[i], "<<") == 0)
                ft_basic_heredoc_final_case(exec, i);
        i += 2;
        index += 2;
    }
    ft_heredoc_final_case(exec, index);    
}

int ft_execute_heredoc(t_exec *exec, int index)
{
    int command_location;
    int pid;
    int info;

    command_location = index - 1;
    if(ft_is_another_flag(exec, 0) == HEREDOC)
    {
        printf("here\n");
        ft_advanced_heredoc_final_case(exec, 0);
        index += 2;
        return (1);
    }
    else
    {
        index = 1;
        command_location = 0;
        pid = fork();
        if(pid == 0)
        {
            if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == PIPE)
            {
                ft_basic_heredoc(exec, index);
                return (1);
            }
            else if(ft_strcmp(exec->command[index], "<<") == 0 && exec->command[index + 2] == NULL)
            { 
                ft_heredoc(exec, command_location, index);
                return (1);
            }
            else
            {
                ft_advanced_heredoc(exec, index, command_location);
                return (1);
            }
        }
        else
        {
            signal(SIGINT, SIG_IGN);
            waitpid(pid, &info, 0);
            if (WIFEXITED(info))
            {
                exec->env.exit_value = WEXITSTATUS(info);
            }
            else if (WIFSIGNALED(info))
            {
                if (WTERMSIG(info) == 2)
                    exec->env.exit_value = 1;
            }
            signal(SIGINT, SIG_DFL);
        }
    }
    return (1);
}