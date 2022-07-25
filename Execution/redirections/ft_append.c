/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:20 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 02:40:15 by rimney           ###   ########.fr       */
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

void	ft_append_final_case(t_exec *exec, int index, char **parser, int in)
{
	int fd;
	int pid;


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
}


int	ft_append_child(t_exec *exec, int in, int fd, int command_location)
{
	exec->in = fd;
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
	return (1);
}

void	ft_append_norm(t_exec *exec, int index, int command_location, int s_flag)
{
	int in;
	int fd;
	int pid;

	while(index < exec->append_count)
	{
		fd = ft_open(exec, APPEND, index + 1);
		if(ft_find_next_flag(exec, &index, &fd, &in))
			s_flag = 1;
		if(exec->error_flag)
		{
			exec->error_flag = 0;
			return ;
		}
		if((index + 1 == exec->append_count || s_flag == 1))
		{
			pid = fork();
			if(pid == 0)
				ft_append_child(exec, in, fd, command_location);
		}
		index += 2;
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

int	ft_append(int index, t_exec *exec, int command_location)
{
	int fd;
	int s_flag;
	char **parser;
	int in;

	s_flag = 0;
	in = -1;
	fd = -1;
	parser = ft_split(exec->command[1], ' ');
	if(index == 0 && ft_is_another_flag(exec, index) == APPEND)
	{
		ft_append_final_case(exec, index, parser, in);
		index = 2;
		exec->in = fd;
	}
	else
	{
		index = 1;
		command_location = 0;
		ft_append_norm(exec, index, command_location, s_flag);
		index += 2;
	}
	ft_free(parser);
	return (index);
}
