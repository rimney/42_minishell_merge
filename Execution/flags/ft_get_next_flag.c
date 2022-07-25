/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 00:21:04 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 03:27:35 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_find_next_flag_input2(t_exec *exec, int *index, int *in)
{
	*in = open(exec->command[*index + 1], O_RDONLY);
	if (*in == -1)
	{
		exec->error_flag = 1;
		perror("minishell");
		return ;
	}
	exec->input_flag = 1;
}

int	ft_find_next_flag_heredoc1(t_exec *exec, int *index, int *in)
{
	ft_heredoc_middle(in, exec->command[*index + 1]);
	exec->heredoc_flag = 1;
	*index += 2;
	return (1);
}

void	ft_find_next_flag_1stq(t_exec *exec, int *index, int *fd, int *in)
{
	if (ft_is_another_flag(exec, *index) == HEREDOC && exec->command[*index + 2]
		&& ft_is_another_flag(exec, *index + 2) == HEREDOC)
        	ft_basic_heredoc(exec, *index);
	if (ft_is_another_flag(exec, *index) == APPEND && exec->command[*index + 2]
		&& ft_is_another_flag(exec, *index) != PIPE)
			*fd = ft_open(exec, APPEND, *index + 1);
	if (ft_is_another_flag(exec, *index) == REDIROUT && exec->command[*index + 2])
		*fd = ft_open(exec, REDIROUT, *index + 1);
	if (ft_is_another_flag(exec, *index) == HEREDOC && exec->command[*index + 2]
		&& ft_is_another_flag(exec, *index + 2) != HEREDOC)
	{
		ft_heredoc_middle(in, exec->command[*index + 1]);
		exec->heredoc_flag = 1;
	}
}

int	ft_find_next_flag_2ndq(t_exec *exec, int *index, int *fd, int *in)
{
	if (ft_is_another_flag(exec, *index) == REDIRIN && exec->command[*index + 2])
	{
		ft_find_next_flag_input2(exec, index, in);
		if (*in == -1)
			return (1);
	}
	if (ft_find_next_flag_append(exec, index, fd))
		return (1);
	if (ft_find_next_flag_input(exec, index, in))
		return (1);
	if (ft_is_another_flag(exec, *index) == HEREDOC && !exec->command[*index + 2])
	{
		if (ft_find_next_flag_heredoc1(exec, index, in))
		return (1);
	}
	if (ft_find_next_flag_rediout(exec, index, fd))
		return (1);
	return (0);
}

int	ft_find_next_flag(t_exec *exec, int *index, int *fd, int *in)
{
	if (exec->command[*index + 2])
		*index += 2;
	if (exec->command[*index])
    {
		while (exec->command[*index + 2] || ft_is_another_flag(exec, *index) != PIPE)
        {
			ft_find_next_flag_1stq(exec, index, fd, in);
			if (ft_find_next_flag_2ndq(exec, index, fd, in))
				return (1);
			*index += 2;
        }
	}
	return (1);
}