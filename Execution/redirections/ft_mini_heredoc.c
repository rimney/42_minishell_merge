/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:54:51 by rimney            #+#    #+#             */
/*   Updated: 2022/07/20 20:59:17 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mini_heredoc(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
	fd = -1;

	exec->initial_flag = 1;
	while(exec->command[i + 1] != NULL)
	{
		if(ft_strcmp(exec->command[i], "<<") == 0 && i <= 1)
		{
			exec->heredoc_count = ft_count_till_other_token(exec, i, "<<");
			ft_execute_heredoc(exec, i);
			i += exec->heredoc_count;
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");;
			if((exec->command[i + 2] && (ft_is_another_flag(exec, i + 2) == PIPE
				|| ft_is_another_flag(exec, i + 2) == APPEND
				|| ft_is_another_flag(exec, i + 2) == REDIROUT || ft_is_another_flag(exec, i + 2) == REDIRIN
				|| ft_is_another_flag(exec, i + 2) == HEREDOC))
				|| exec->command[i + 2] == NULL)
			{
				exec->pipe_count = ft_count_till_other_token(exec, i, "|");
				fd = open(".temp", O_CREAT | O_RDONLY | O_TRUNC, 0644);
				i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
			}
		}
		i++;
	}
	wait(NULL);
	return(i);
}