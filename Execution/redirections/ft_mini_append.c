/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:22:41 by rimney            #+#    #+#             */
/*   Updated: 2022/07/18 04:32:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mini_append(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
	fd = -1;

	exec->initial_flag = 1;
	while(exec->command[i + 1] != NULL)
	{
		if(ft_strcmp(exec->command[i], ">>") == 0 && i == 1)
		{
			printf("KKK\n");
			exec->append_count = ft_count_till_other_token(exec, i, ">>");
			ft_append(i, exec, i - 1);
			i += exec->append_count;
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