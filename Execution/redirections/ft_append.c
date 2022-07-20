/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:20 by rimney            #+#    #+#             */
/*   Updated: 2022/07/19 23:36:56 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_single_append(int argc, char **argv)
{
	int fd;
	char *line;
	if(argc == 3 && ft_strcmp(argv[1], ">>") == 0)
	{
		fd = open(argv[2], O_CREAT | O_RDWR, 0644);
		while(1)
		{
			fd = open(argv[2], O_RDWR | O_APPEND, 0644);
			line = readline("");
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

void	ft_advanced_append(int index, t_exec *exec, int fd_out, int fd_in, int location)
{
	int pid;
	int location_save;

	fd_in = open(exec->command[index - 3], O_RDONLY);
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
	int pid;
	int fd;
	int s_flag;
	int in;

	s_flag = 0;
	while(index < exec->append_count)
	{
		printf("%s << \n", exec->command[index + 1]);
		fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if(ft_find_next_flag(exec, &index, &fd, &in))
			s_flag = 1;
		if(exec->error_flag)
		{
			exec->error_flag = 0;
			return(0);
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
	return (index);
}