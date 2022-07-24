/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:21 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 19:47:39 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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


int	ft_find_next_flag_heredoc(t_exec *exec, int *index, int *fd, int *in)
{
	if(exec->command[*index + 2])
		*index += 2;
	if(exec->command[*index])
	{
		printf("%s <<<<<<\n", exec->command[*index]);
		while(exec->command[*index + 2] || ft_is_another_flag(exec, *index) != PIPE)
		{
			if(ft_is_another_flag(exec, *index) == APPEND && exec->command[*index + 2] && ft_is_another_flag(exec, *index) != PIPE)
				*fd = ft_open(exec, APPEND, *index + 1);
			if(ft_is_another_flag(exec, *index) == APPEND && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
			{
                printf("EEEEEE\n");
				*fd = ft_open(exec, APPEND, *index + 1);
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == REDIRIN && exec->command[*index + 2])
			{
				*in = open(exec->command[*index + 1], O_RDONLY);
				if(*in == -1)
				{
					exec->error_flag = 1;
					perror("minishell");
					return (0);
				}
				exec->input_flag = 1;
			}
			if(ft_is_another_flag(exec, *index) == REDIRIN && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
			{
				*in = open(exec->command[*index + 1], O_RDONLY);
				if(*in == -1)
				{
					exec->error_flag = 1;
					perror("minishell");
					return (0);
				}
				exec->input_flag = 1;
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == HEREDOC && exec->command[*index + 2] && ft_is_another_flag(exec, *index + 2) == HEREDOC)
				ft_basic_heredoc(exec, *index); 
			if(ft_is_another_flag(exec, *index) == REDIROUT && exec->command[*index + 2])
				*fd = ft_open(exec, REDIROUT, *index + 1);
			if(ft_is_another_flag(exec, *index) == REDIROUT && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
			{
				*fd = ft_open(exec, REDIROUT, *index + 1);
				*index += 2;
				return (1);
			}
			*index += 2;
		}
	}
	return (1);
}

void    ft_heredoc_final_case(t_exec *exec, int index)
{
    int pid;
    int fd[2];
    int out;


    out = -1;
    pipe(fd);
    pid = fork();
    if(pid == 0)
        ft_heredoc_final_case_child(exec, index, fd, out);
    else
    {    
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, 0, 0);
    }
}

int ft_basic_heredoc_final_case(t_exec *exec, int index)
{
    char *line;
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

