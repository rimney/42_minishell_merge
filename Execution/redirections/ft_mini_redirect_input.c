/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_redirect_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:29:57 by rimney            #+#    #+#             */
/*   Updated: 2022/07/16 18:16:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_find_next_flag(t_exec *exec, int *index, int *fd)
{
	if(ft_is_another_flag(exec, *index + 2) == APPEND && (exec->command[*index + 4] == NULL || ft_is_another_flag(exec, *index + 4) == PIPE))
	{
		*fd = open(exec->command[*index + 3], O_CREAT | O_APPEND | O_RDWR, 0644);
		*index += 2;
		return (1);
	}
	return (0);
}

int	ft_mini_redirect_input(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
	fd = -1;

	exec->initial_flag = 1;
	while(exec->command[i + 1] != NULL)
	{
		if(ft_strcmp(exec->command[i], ">") == 0 && i == 1)
		{
			exec->input_count = ft_count_till_other_token(exec, i, ">");
			ft_redirect_input(exec, i, i - 1);
			i += exec->input_count;
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
				fd = open(exec->command[i - 1], O_RDWR);
				i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
			}
		}
		i++;
	}
	wait(NULL);
	return(i);
}