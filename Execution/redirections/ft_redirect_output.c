/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:27 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 07:15:52 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_advanced_redirect(int index, t_exec *exec, int fd_out, int fd_in)
{
	int	pid;
	int	location;

	location = index - 1;
	fd_in = ft_open(exec, REDIRIN, index - 3);
	fd_out = ft_open(exec, REDIROUT, index + 1);
	while (index < exec->redirection_count)
	{
		if (index + 1 == exec->redirection_count)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
				dup2(fd_out, 1);
				close(fd_out);
				ft_execute_command(exec, location);
			}
		}
		index += 2;
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

void	ft_redirect_final_case(t_exec *exec, int index, char **parser, int in)
{
	int	fd;
	int	pid;

	fd = open(parser[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_find_next_flag(exec, &index, &fd, &in);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		close(fd);
		execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
	}
	else
		waitpid(pid, 0, 0);
}

int	ft_redirect_child(t_exec *exec, int in, int fd, int command_location)
{
	exec->in = fd;
	if (exec->input_flag || exec->heredoc_flag)
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

void	ft_redirect_norm(t_exec *exec, int index,
	int command_location, int s_flag)
{
	int	in;
	int	fd;
	int	pid;

	while (index < exec->redirection_count)
	{
		fd = ft_open(exec, REDIROUT, index + 1);
		if (ft_find_next_flag(exec, &index, &fd, &in))
			s_flag = 1;
		if (exec->error_flag)
		{
			exec->error_flag = 0;
			return ;
		}
		if ((index + 1 == exec->redirection_count || s_flag == 1))
		{
			pid = fork();
			if (pid == 0)
				ft_redirect_child(exec, in, fd, command_location);
		}
		index += 2;
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

int	ft_redirect(int index, t_exec *exec, int command_location)
{
	int		fd;
	int		s_flag;
	char	**parser;
	int		in;

	s_flag = 0;
	in = -1;
	fd = -1;
	parser = ft_split(exec->command[1], ' ');
	if (index == 0 && ft_is_another_flag(exec, index) == REDIROUT)
	{
		ft_redirect_final_case(exec, index, parser, in);
		index = 2;
		exec->in = fd;
	}
	else
	{
		index = 1;
		command_location = 0;
		ft_redirect_norm(exec, index, command_location, s_flag);
		index += 2;
	}
	ft_free(parser);
	return (index);
}
