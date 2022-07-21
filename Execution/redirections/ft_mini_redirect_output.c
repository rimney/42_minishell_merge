/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_redirect_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:31:43 by rimney            #+#    #+#             */
/*   Updated: 2022/07/21 00:49:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	ft_mini_redirect_output(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
	fd = -1;

	exec->initial_flag = 1;
	while(exec->command[i + 1] != NULL)
	{
		if(ft_strcmp(exec->command[i], ">") == 0 && i == 1)
		{
			printf("asdf\n");
			exec->redirection_count = ft_count_till_other_token(exec, i, ">");
			ft_redirect(i, exec, i - 1);
			i += exec->redirection_count;
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			printf("RRRRR\n");
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");;
			if((exec->command[i + 2] && (ft_is_another_flag(exec, i + 2) == PIPE
				|| ft_is_another_flag(exec, i + 2) == APPEND
				|| ft_is_another_flag(exec, i + 2) == REDIROUT || ft_is_another_flag(exec, i + 2) == REDIRIN
				|| ft_is_another_flag(exec, i + 2) == HEREDOC))
				|| exec->command[i + 2] == NULL)
			{
				exec->pipe_count = ft_count_till_other_token(exec, i, "|");
				fd = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
				if(fd == -1)
					printf("ZZZZZ\n");
				i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
			}
		}
		i++;
	}
	wait(NULL);
	return(i);
}

