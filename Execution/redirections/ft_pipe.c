/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:23 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 08:36:20 by atarchou         ###   ########.fr       */
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

void	ft_apply_heredoc_redirection_after_pipe(int in, t_pipe *tpipe,
	t_exec *exec, int index)
{
	if (exec->command[index + exec->heredoc_count + 1] != NULL)
		exit(0);
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	tpipe->fd[1] = 0;
	ft_execute_command(exec, index);
}
