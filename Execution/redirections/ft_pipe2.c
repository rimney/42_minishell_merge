/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:41:35 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:16:57 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	ft_input_pipe_norm(int fd, int index, t_exec *exec, t_pipe *tpipe)
{
	int	pid;

	fd = open(exec->command[index + exec->input_count + 2], O_RDWR);
	pid = fork();
	if (pid == 0)
		ft_apply_input_redirection_after_pipe(fd, tpipe, exec, index + 2);
	return ;
}

void	execute_pipe_helper(t_pipe *t_pipe, t_exec *exec, int pid, int *in)
{
	if (pid == 0)
	{
		ft_pipe(*in, t_pipe, exec, exec->pipe_index);
		exit(0);
	}
	if (*in != -1)
		close(*in);
	if (t_pipe->fd[1] != -1)
		close(t_pipe->fd[1]);
}

int	execute_helper2(t_exec *exec, t_pipe *tpipe, int index, int in_save)
{
	ft_redirect_after_pipe_flag(exec, tpipe, index - 2, in_save);
	exec->redirecion_flag = 0;
	return (index);
}

int	execute_pipe(t_exec *exec, int index, int in, t_pipe *tpipe)
{
	int	in_save;
	int	fd;
	int	pid;

	fd = -1;
	exec->pipe_index = index;
	if (exec->command[exec->pipe_index + 1] != NULL)
	{
		pipe(tpipe->fd);
		in_save = tpipe->fd[0];
	}
	pid = fork();
	execute_pipe_helper(tpipe, exec, pid, &in);
	if (ft_pipe_condition(index, exec))
		return (execute_helper2(exec, tpipe, index, in_save));
	if (index < tpipe->max)
	{
		if ((exec->pipe_flag) && index == tpipe->max - 2)
			ft_redirect_after_pipe_flag(exec, tpipe, index, in_save);
		execute_pipe(exec, index + 2, in_save, tpipe);
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
	return (index);
}
