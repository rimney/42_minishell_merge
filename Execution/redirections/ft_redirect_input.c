/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:25 by rimney            #+#    #+#             */
/*   Updated: 2022/07/19 16:32:52 by rimney           ###   ########.fr       */
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
            if(fd_in <= 0)
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

int	ft_redirect_input(int index, t_exec *exec, int command_location, t_pipe *tpipe)
{
	int fd;
	int in;
	int pid;
	int s_flag;
    char **parser;

	s_flag = 0;
    if(index == 0 && ft_is_another_flag(exec, index) == REDIRIN)
    {
        exec->input_flag = 1;
        parser = ft_split(exec->command[1], ' ');
        in = open(parser[0], O_RDONLY);
        if(!exec->command[index + 2])
        {
            pid = fork();
            if(pid == 0)
            {
                dup2(in, 0);
                close(in);
                execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
            }
            else
            {
                waitpid(pid, 0, 0);
                ft_free(parser);
            }
        }
        index += 2;
		if(exec->command[index] && ft_is_another_flag(exec, index) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, index, "|");;
			if((exec->command[index + 2] && (ft_is_another_flag(exec, index + 2) == PIPE
				|| ft_is_another_flag(exec, index + 2) == APPEND
				|| ft_is_another_flag(exec, index + 2) == REDIROUT || ft_is_another_flag(exec, index + 2) == REDIRIN
				|| ft_is_another_flag(exec, index + 2) == HEREDOC))
				|| exec->command[index + 2] == NULL)
			{
				exec->pipe_count = ft_count_till_other_token(exec, index, "|");
				fd = in;
				index = ft_apply_pipe_middle(exec, tpipe, index, fd) - 1;
			}
		}
        return (index);
    }
	while(index < exec->input_count)
	{
            command_location = index;
            printf("%s << c\n", exec->command[command_location]);
		    fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		    if(exec->command[index + 2] && ft_find_next_flag(exec, &index, &fd, &in))
			    s_flag = 1;
		    if((index + 1 == exec->redirection_count || s_flag))
		    {
			    pid = fork();
			    if(pid == 0)
			    {
				    if(exec->input_flag || exec->heredoc_flag)
				    {
					    dup2(in, 0);
					    close(in);
					    exec->input_flag = 0;
					    exec->heredoc_flag = 0;
				    }
				    dup2(fd, 1);
				    close(fd);
				    ft_execute_command(exec, command_location);
			    }
		    }
		    index += 1;
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
	return (index);
}