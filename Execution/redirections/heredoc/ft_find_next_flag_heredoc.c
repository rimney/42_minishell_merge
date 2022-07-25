/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_flag_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 07:16:44 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 07:56:38 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_find_next_flag_heredoc_1stq(t_exec *exec, int *fd, int *index)
{
	if (ft_is_another_flag(exec, *index) == APPEND
		&& exec->command[*index + 2]
		&& ft_is_another_flag(exec, *index) != PIPE)
		*fd = ft_open(exec, APPEND, *index + 1);
	if (ft_is_another_flag(exec, *index) == HEREDOC
		&& exec->command[*index + 2]
		&& ft_is_another_flag(exec, *index + 2) == HEREDOC)
		ft_basic_heredoc(exec, *index);
	if (ft_is_another_flag(exec, *index) == REDIROUT
		&& exec->command[*index + 2])
		*fd = ft_open(exec, REDIROUT, *index + 1);
}

int	ft_find_next_flag_heredoc_2ndq(t_exec *exec, int *index, int *in, int *fd)
{
	if (ft_is_another_flag(exec, *index) == APPEND
		&& (!exec->command[*index + 2]
			|| ft_is_another_flag(exec, *index + 2) == PIPE))
	{
		*fd = ft_open(exec, APPEND, *index + 1);
		*index += 2;
		return (1);
	}
	if (ft_is_another_flag(exec, *index) == REDIRIN
		&& exec->command[*index + 2])
	{
		*in = open(exec->command[*index + 1], O_RDONLY);
		if (*in == -1)
		{
			exec->error_flag = 1;
			perror("minishell");
			return (1);
		}
		exec->input_flag = 1;
	}
	return (0);
}

int	ft_find_next_flag_3rdq(t_exec *exec, int *in, int *index, int *fd)
{
	if (ft_is_another_flag(exec, *index) == REDIRIN
		&& (!exec->command[*index + 2]
			|| ft_is_another_flag(exec, *index + 2) == PIPE))
	{
		*in = open(exec->command[*index + 1], O_RDONLY);
		if (*in == -1)
		{
			exec->error_flag = 1;
			perror("minishell");
			return (1);
		}
		exec->input_flag = 1;
		*index += 2;
		return (1);
	}
	if (ft_is_another_flag(exec, *index) == REDIROUT
		&& (!exec->command[*index + 2]
			|| ft_is_another_flag(exec, *index + 2) == PIPE))
	{
		*fd = ft_open(exec, REDIROUT, *index + 1);
		*index += 2;
		return (1);
	}
	return (0);
}

int	ft_find_next_flag_heredoc(t_exec *exec, int *index, int *fd, int *in)
{
	if (exec->command[*index + 2])
		*index += 2;
	if (exec->command[*index])
	{
		while (exec->command[*index + 2]
			|| ft_is_another_flag(exec, *index) != PIPE)
		{
			ft_find_next_flag_heredoc_1stq(exec, fd, index);
			if (ft_find_next_flag_heredoc_2ndq(exec, index, in, fd))
				return (0);
			if (ft_find_next_flag_3rdq(exec, in, index, fd))
				return (1);
			*index += 2;
		}
	}
	return (1);
}
