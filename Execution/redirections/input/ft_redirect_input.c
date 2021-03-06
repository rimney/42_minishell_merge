/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:25 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:42:50 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_advanced_redirect_input(t_exec *exec, int fd_in, int index)
{
	int	pid;
	int	location;

	location = index - 1;
	pid = fork();
	if (pid == 0)
	{
		while (index < exec->input_count)
		{
			fd_in = open(exec->command[index + 1], O_RDONLY);
			if (fd_in == -1)
			{
				perror("minishell : ");
				exit(0);
			}
			if (index + 1 == exec->input_count)
			{
				if (exec->command[index + 2])
					exit(0);
				ft_input_norm(fd_in, exec, location);
			}
			index += 2;
		}
	}
	wait(NULL);
}

void	ft_redirect_input_norm(t_exec *exec, int in,
	int fd, int command_location)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(in, 0);
		close(in);
		if (fd != -1)
		{
			dup2(fd, 1);
			close(fd);
		}
		ft_execute_command(exec, command_location);
	}
	else
	{
		waitpid(pid, &exec->env.exit_value, 0);
		WIFEXITED(exec->env.exit_value);
	}
	exec->in = in;
}

int	ft_error_exit_norm(t_exec *exec, int in)
{
	if (in == -1)
	{
		perror("minishell : ");
		return (0);
	}
	if (exec->error_flag == 1)
	{
		exec->error_flag = 0;
		return (0);
	}
	return (1);
}

int	ft_norm_condition(t_exec *exec, int index)
{
	if (ft_is_another_flag(exec, index) == REDIRIN
		&& exec->command[index + exec->input_count]
		&& ft_is_another_flag(exec, index + exec->input_count) == PIPE)
		return (1);
	return (0);
}

int	ft_redirect_input(int index, t_exec *exec, int command_location)
{
	int	fd;
	int	in;
	int	s_flag;

	s_flag = 0;
	fd = -1;
	if (ft_is_another_flag(exec, 0) == REDIRIN)
		return (ft_minishell_input_final_case(exec, index));
	if (exec->command[index] && ft_is_another_flag(exec, 1) == REDIRIN)
	{
		in = open(exec->command[index + 1], O_RDONLY);
		while (index < exec->input_count)
		{
			if (ft_norm_condition(exec, index))
				return (index);
			if (ft_find_next_flag(exec, &index, &fd, &exec->in))
				s_flag = 1;
			if (!ft_error_exit_norm(exec, in))
				return (0);
			if ((index + 1 == exec->input_count || s_flag))
				ft_redirect_input_norm(exec, in, fd, command_location);
			index += 2;
		}
	}
	return (index);
}
