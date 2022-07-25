/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:41:35 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 07:14:57 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pipe_condition(int index, t_exec *exec)
{
	if (exec->command[index + 1]
		&& (ft_strcmp(exec->command[index + 1], ">") == 0
			|| ft_strcmp(exec->command[index + 1], ">>") == 0
			|| ft_strcmp(exec->command[index + 1], "<") == 0)
		&& exec->pipe_count > 2)
		return (1);
	return (0);
}

void	ft_pipe_norm(t_exec *exec, int *in, t_pipe *tpipe, int *in_save)
{
	int	pid;

	if (exec->command[exec->pipe_index + 1] != NULL)
	{
		pipe(tpipe->fd);
		*in_save = tpipe->fd[0];
	}
	pid = fork();
	if (pid == 0)
	{
		ft_pipe(*in, tpipe, exec, exec->pipe_index);
		exit(0);
	}
	if (*in != -1)
		close(*in);
	if (tpipe->fd[1] != -1)
		close(tpipe->fd[1]);
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

void	ft_redirect_after_pipe_flag(t_exec *exec, t_pipe *tpipe,
	int index, int in_save)
{
	int	pid;
	int	fd;

	fd = -1;
	ft_get_next_redi(exec, &fd, index);
	if (exec->input_flag == 1)
	{
		fd = open(exec->command[index + exec->input_count + 2], O_RDWR);
		pid = fork();
		if (pid == 0)
			ft_apply_input_redirection_after_pipe(fd, tpipe, exec, index + 2);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		exec->in = in_save;
		ft_apply_redirection_after_pipe(fd, tpipe, exec, index + 2);
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

int	execute_pipe(t_exec *exec, int index, int in, t_pipe *tpipe)
{
	int	in_save;
	int	fd;

	fd = -1;
	exec->pipe_index = index;
	ft_pipe_norm(exec, &in, tpipe, &in_save);
	if (ft_pipe_condition(index, exec))
	{
		ft_redirect_after_pipe_flag(exec, tpipe, index - 2, in_save);
		exec->redirecion_flag = 0;
		return (index);
	}
	if (index < tpipe->max)
	{
		if ((exec->pipe_flag) && index == tpipe->max - 2)
			ft_redirect_after_pipe_flag(exec, tpipe, index, in_save);
		execute_pipe(exec, index + 2, in_save, tpipe);
	}
	return (index);
}
