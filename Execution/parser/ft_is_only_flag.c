/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:35:40 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:00:14 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_command_flag(t_exec *exec)
{
	if (exec->pipe_count == 0 && exec->input_count == 0
		&& exec->append_count == 0 && exec->heredoc_count == 0
		&& exec->redirection_count == 0 && exec->args > 0)
		return (1);
	return (-1);
}

int	only_output_redirection_flag(t_exec *exec)
{
	if (exec->pipe_count == 0 && exec->input_count == 0
		&& exec->append_count == 0 && exec->heredoc_count == 0
		&& exec->redirection_count > 0 && exec->args > 0)
		return (1);
	return (-1);
}

int	only_heredoc_flag(t_exec *exec)
{
	if (exec->pipe_count == 0 && exec->input_count == 0
		&& exec->append_count == 0 && exec->heredoc_count > 0
		&& exec->redirection_count == 0 && exec->args > 0)
		return (1);
	return (-1);
}

int	only_append_flag(t_exec *exec)
{
	if (exec->pipe_count == 0 && exec->input_count == 0
		&& exec->append_count > 0 && exec->heredoc_count == 0
		&& exec->redirection_count == 0 && exec->args > 0)
		return (1);
	return (-1);
}

int	only_input_flag(t_exec *exec)
{
	if (exec->pipe_count == 0 && exec->input_count > 0
		&& exec->append_count == 0 && exec->heredoc_count == 0
		&& exec->redirection_count == 0 && exec->args > 0)
		return (1);
	return (-1);
}
