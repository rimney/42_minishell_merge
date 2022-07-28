/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:50:18 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 09:16:10 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_get_next_flag2(t_exec *exec, int i)
{
	if (exec->command[i + exec->pipe_count]
		&& ft_strcmp(exec->command[i + exec->pipe_count], ">>") == 0
		&& exec->pipe_count > 2)
	{
		exec->append_flag = 1;
		exec->append_count
			= ft_count_till_other_token(exec, i + exec->pipe_count, ">>");
	}
	if (exec->command[i + exec->pipe_count]
		&& ft_strcmp(exec->command[i + exec->pipe_count], "<") == 0
		&& exec->pipe_count > 2)
	{
		exec->input_flag = 1;
		exec->input_count
			= ft_count_till_other_token(exec, i + exec->pipe_count, "<");
	}
}

int	ft_heredoc_norm_condi(t_exec *exec, int i)
{
	if (exec->command[i + exec->pipe_count]
		&& ft_strcmp(exec->command[i + exec->pipe_count], "<<") == 0
		&& exec->pipe_count > 2)
		return (1);
	return (0);
}

void	ft_get_next_flag_pipe(t_exec *exec, int index, int i)
{
	if (exec->pipe_count == 2 && exec->command[index + 2])
	{
		if (ft_strcmp(exec->command[index + 2], ">") == 0)
		{
			exec->pipe_flag = 1;
			exec->redirection_count
				= ft_count_till_other_token(exec, i + 2, ">");
		}
	}
	if (exec->command[i + exec->pipe_count]
		&& ft_strcmp(exec->command[i + exec->pipe_count], ">") == 0
		&& exec->pipe_count > 2)
	{
		exec->redirecion_flag = 1;
		exec->redirection_count
			= ft_count_till_other_token(exec, i + exec->pipe_count, ">");
	}
	if (ft_heredoc_norm_condi(exec, i))
	{
		exec->heredoc_count = ft_count_till_other_token(exec,
				i + exec->pipe_count, "<<");
		exec->heredoc_flag = 1;
	}
	else
		ft_get_next_flag2(exec, i);
}

int	ft_mini_pipe(t_exec *exec, t_pipe *pipes, int in, int index)
{
	int	i;

	i = index;
	ft_get_next_flag_pipe(exec, index, i);
	ft_assign_tpipe(pipes, index + exec->pipe_count - 1);
	if (exec->pipe_flag)
	{
		execute_pipe(exec, i - 1, in, pipes);
		exec->pipe_flag = 0;
		i++;
		return (i + exec->pipe_count);
	}
	if (i == 1)
		execute_pipe(exec, 0, in, pipes);
	else
		execute_pipe(exec, i + 1, in, pipes);
	exec->pipe_flag = 0;
	exec->input_count = 0;
	return (i + exec->pipe_count);
}
