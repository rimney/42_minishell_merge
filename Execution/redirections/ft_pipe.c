/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:23 by rimney            #+#    #+#             */
/*   Updated: 2022/07/26 06:46:10 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pipe(int in, t_pipe *tpipe, t_exec *exec, int index)
{
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	if (tpipe->fd[1] != -1)
	{
		dup2(tpipe->fd[1], 1);
		close(tpipe->fd[1]);
	}
	close(tpipe->fd[0]);
	ft_execute_command(exec, index);
}

void	ft_apply_redirection_after_pipe(int out, t_pipe *tpipe,
	t_exec *exec, int index)
{
	if (exec->in != -1)
	{
		dup2(exec->in, 0);
		close(exec->in);
	}
	if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
	close(tpipe->fd[0]);
	ft_execute_command(exec, index);
	tpipe->in = 0;
}

void	ft_apply_input_redirection_after_pipe(int in, t_pipe *tpipe,
	t_exec *exec, int index)
{
	if (exec->command[index + exec->input_count + 1] != NULL)
		exit(0);
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	tpipe->fd[1] = 0;
	ft_execute_command(exec, index);
}

int	ft_flag_after_pipe(t_exec *exec)
{
	if (exec->redirecion_flag == 1
		|| exec->append_flag == 1
		|| exec->input_flag == 1)
		return (1);
	return (0);
}

void	ft_get_next_redi(t_exec *exec, int *fd, int index)
{
	if (exec->pipe_flag == 1)
		*fd = open(exec->command[index + exec->redirection_count + 2],
				O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (exec->redirecion_flag == 1)
		*fd = open(exec->command[index + exec->redirection_count + 2],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (exec->append_flag == 1)
		*fd = open(exec->command[index + exec->append_count + 2],
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (exec->heredoc_flag == 1)
	{
		printf("her     edoc\n");
		*fd = open(exec->command[index + exec->append_count + 2],
				O_RDWR | O_CREAT | O_APPEND, 0644);
	}
}
