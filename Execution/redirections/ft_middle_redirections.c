/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:33:36 by rimney            #+#    #+#             */
/*   Updated: 2022/07/17 23:43:59 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_get_next_redirection(t_exec *exec, int index)
{
	if(ft_is_another_flag(exec, index) == REDIROUT)
	{
		exec->redirection_count = ft_count_till_other_token(exec, index, ">");
		return (exec->redirection_count);
	}
	if(ft_is_another_flag(exec, index) == APPEND)
	{
		exec->append_count = ft_count_till_other_token(exec, index, ">>");
		return (exec->append_count);
	}
	if(ft_is_another_flag(exec, index) == REDIRIN)
	{
		exec->input_count = ft_count_till_other_token(exec, index, "<");
		return (exec->input_count);
	}
	if(ft_is_another_flag(exec, index) == HEREDOC)
	{
		exec->heredoc_count = ft_count_till_other_token(exec, index, "<<");
		return (exec->heredoc_count);
	}
	return (0);
}

int ft_apply_pipe_middle(t_exec *exec, t_pipe *tpipe, int i, int fd)
{
	printf("EN\n");
	if((exec->command[i + 2] && ft_is_another_flag(exec, i + 2))
			|| exec->command[i + 2] == NULL)
	{
		if(exec->command[i + 2] && (ft_get_next_redirection(exec, i + 2)))
		{
			printf("HH\n");
			ft_dup_and_redirect(fd, exec, tpipe, i + 2);
			i += ft_get_next_redirection(exec, i + 2);
			return (i - 1);
		}
		else
		{
			ft_mini_pipe(exec, tpipe, fd, i - 1, i);
		i += exec->pipe_count;
		wait(NULL);
		}
	}
    return (i - 1);
}