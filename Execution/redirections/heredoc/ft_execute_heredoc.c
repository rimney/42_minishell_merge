/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:10:42 by rimney            #+#    #+#             */
/*   Updated: 2022/07/27 06:33:31 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_apply_heredoc_child(t_exec *exec, int index, int command_location)
{
	if (exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == PIPE)
	{
		ft_basic_heredoc(exec, index);
		return (1);
	}
	else if (ft_strcmp(exec->command[index], "<<") == 0
		&& exec->command[index + 2] == NULL)
	{
		ft_heredoc(exec, command_location, index);
		return (1);
	}
	else
	{
		ft_advanced_heredoc(exec, index, command_location);
		return (1);
	}
	return (0);
}

void	ft_apply_heredoc_parent(int pid, t_exec *exec, int info)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &info, 0);
	if (WIFEXITED(info))
		exec->env.exit_value = WEXITSTATUS(info);
	else if (WIFSIGNALED(info))
	{
		if (WTERMSIG(info) == 2)
			exec->env.exit_value = 2;
	}
	signal(SIGINT, SIG_DFL);
}

int	ft_execute_heredoc(t_exec *exec, int index)
{
	int	command_location;
	int	pid;
	int	info;

	command_location = index - 1;
	info = 0;
	if (ft_is_another_flag(exec, 0) == HEREDOC)
	{
		ft_advanced_heredoc_final_case(exec, 0);
		index += 2;
		return (1);
	}
	else
	{
		index = 1;
		command_location = 0;
		pid = fork();
		if (pid == 0)
			ft_apply_heredoc_child(exec, index, command_location);
		else
		{
			ft_apply_heredoc_parent(pid, exec, info);
		}
	}
	return (1);
}
