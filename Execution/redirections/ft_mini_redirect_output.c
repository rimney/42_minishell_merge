/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_redirect_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:31:43 by rimney            #+#    #+#             */
/*   Updated: 2022/07/04 01:17:18 by rimney           ###   ########.fr       */
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
			exec->redirection_count = ft_count_till_other_token(exec, i, ">");
			ft_redirect(i, exec, i - 1);
			i += exec->redirection_count;
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");;
			if((exec->command[i + 2] && (ft_is_another_flag(exec, i + 2) == PIPE || ft_is_another_flag(exec, i + 2) == APPEND || ft_is_another_flag(exec, i + 2) == REDIROUT || ft_is_another_flag(exec, i + 2) == REDIRIN )) || exec->command[i + 2] == NULL)
			{
				exec->pipe_count = ft_count_till_other_token(exec, i, "|");
				fd = open(exec->command[i - 1], O_RDWR);
				i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
			//	i += exec->pipe_count;
			}
		}
		// if(exec->command[i] && ft_is_another_flag(exec, i) == REDIROUT && exec->pipe_count <= 2)
		// {
		// 	exec->redirection_count = ft_count_till_other_token(exec, i, ">");
		// 	ft_middle_rediout(exec, tpipe, i);
		// 	if(exec->command[i + 2])
		// 		i += exec->redirection_count - 1;
		// 	else
		// 		i += exec->redirection_count;
		// }
		// if(exec->command[i] && ft_is_another_flag(exec, i) == REDIRIN)
		// {
		// 	exec->input_count = ft_count_till_other_token(exec, i, "<");
		// 	i = ft_apply_redin_middle(exec, tpipe, i);
		// }
		 if(exec->command[i] && ft_is_another_flag(exec, i) == HEREDOC)
		{
			ft_execute_heredoc(exec, tpipe, i);
			if(exec->command[i + 2])
			 	i += exec->heredoc_count - 1;
			else
				i += exec->heredoc_count;
		}
		i++;
	}
	wait(NULL);
	return(i);
}