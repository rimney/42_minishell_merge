/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:20 by rimney            #+#    #+#             */
/*   Updated: 2022/07/23 22:03:23 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void	ft_advanced_append(int index, t_exec *exec, int fd_out, int fd_in, int location)
{
	int pid;
	int location_save;

	fd_in = open(exec->command[index - 3], O_RDONLY);
	location_save = -1;
	pid = fork();
	if(pid == 0)
	{
		while(index < exec->append_count)
		{
			fd_out = open(exec->command[index + 1], O_CREAT | O_APPEND | O_RDWR, 0644);
			if(index + 1 == exec->append_count)
			{
				dup2(fd_in, 0);
				close(fd_in);
				dup2(fd_out, 1);
				close(fd_out);
				ft_execute_command(exec, location);
			}
			index += 2;
		}
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}



int	ft_append(int index, t_exec *exec, int command_location)
{
	int fd;
	int in;
	int pid;
	int s_flag;
	char **parser;

	s_flag = 0;
	parser = ft_split(exec->command[1], ' ');
	if(index == 0 && ft_is_another_flag(exec, index) == APPEND)
	{
		fd = open(parser[0], O_CREAT | O_RDWR | O_APPEND, 0644);
		ft_find_next_flag(exec, &index, &fd, &in);
		pid = fork();
		if(pid == 0)
		{
			dup2(fd, 1);
			close(fd);
			execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
		}
		else
			waitpid(pid, 0, 0);
		index = 2;
		exec->in = fd;
	}
	else
	{
		index = 1;
		command_location = 0;
	while(index < exec->append_count)
	{
		fd = ft_open(exec, APPEND, index + 1);
		if(ft_find_next_flag(exec, &index, &fd, &in))
			s_flag = 1;
		if(exec->error_flag)
		{
			exec->error_flag = 0;
			return (0);
		}
		if((index + 1 == exec->append_count || s_flag == 1))
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
		index += 2;
	}

	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
	exec->in = fd;
	}
	ft_free(parser);
	return (index);
}
