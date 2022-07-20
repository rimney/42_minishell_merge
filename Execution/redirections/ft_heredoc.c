/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:21 by rimney            #+#    #+#             */
/*   Updated: 2022/07/20 01:46:24 by rimney           ###   ########.fr       */
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

// int ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_loaction)
// {
//     char *delimiter;
//     char *line;
//     int out;
//     int in;

//     in = -1;
    
//     out  = -1;
//     delimiter = strdup(exec->command[index + 1]);
//     if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == REDIROUT)
//     {
//         exec->redirection_count = ft_count_till_other_token(exec, index + 2, ">");
//          out = open(exec->command[index + exec->redirection_count + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
//     }
//     if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == APPEND)
//     {
//         exec->append_count = ft_count_till_other_token(exec, index + 2, ">>");
//          out = open(exec->command[index + exec->append_count + 1], O_APPEND | O_APPEND | O_RDWR, 0644);
//     }
//     if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == REDIRIN)
//     {
//         exec->input_count = ft_count_till_other_token(exec, index + 2, "<");
//         in = open(exec->command[index + exec->input_count + 1], O_RDONLY);
//     }
//     while((line = readline("heredoc > ")))
//     {
//         if (ft_strcmp(line, delimiter) != 0 && in != -1)
//         {
//             write(fd[1],line,strlen(line));
//             write(fd[1], "\n", 1);
//         }
//         if (ft_strcmp(line, delimiter) == 0)
//         {
//             // if(in != -1)
//             // {
//             //     dup2(in, 0);
//             //     close(in);
//             // }
//             if(out != -1)
//             {
//                 dup2(out, 1);
//                 close(out);
//             }
//             close(fd[1]);
//             // if(in == -1)
//             // {
//                 dup2(fd[0], 0);
//                 close(fd[0]);
//             ft_execute_command(exec, command_loaction);
//             return (1);
//         }
//         free(line);
//     }
//     free(delimiter);
//     return(0); 
// }

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
            ft_execute_command(exec, command_loaction);
            return (1);
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
    while (i < ft_get_last_delimiter(exec, index) && exec->heredoc_count > 2)
    {
        if (ft_strcmp(exec->command[i], "<<") == 0)
                ft_basic_heredoc(exec, i);
        i += 2;
        index += 2;
    }
    ft_heredoc(exec, command_location, index);    
}



int ft_execute_heredoc(t_exec *exec, int index)
{
    int command_location;
    int pid;
    int info;

    command_location = index - 1;
    pid = fork();
    if(pid == 0)
    {
        if(index == 0 && ft_is_another_flag(exec, index) == HEREDOC)
        {
            printf("here\n");
            index += 2;
        }
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
    return (0);
}