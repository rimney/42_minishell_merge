/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:26:02 by rimney            #+#    #+#             */
/*   Updated: 2022/06/30 22:17:43 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe)
{
	int pid;

	if(only_command_flag(exec) > 0)
	{
		pid = fork();
		if(pid == 0)
			ft_execute_command(exec, 0);
		wait(0);
    }
	else if(only_pipe_flag(exec) > 0 && exec->args > 2)
	{
		ft_assign_tpipe(tpipe, exec->pipe_count);
		execute_pipe(exec, 0, -1, tpipe);
		wait(NULL);
	}
	else if(only_output_redirection_flag(exec) > 0)
		ft_redirect(1, exec, 0);
	else if(only_heredoc_flag(exec) > 0)
		ft_execute_heredoc(exec, tpipe, 1);
	else if(only_append_flag(exec) > 0)
	{
		//printf("DDD\n");
		ft_append(1, exec, tpipe, 0); // segfault here !!!!!
	}
	else if(only_input_flag(exec) > 0)
		ft_redirect_input(exec, tpipe, 0, 0);
	else
		return (0);
	return(1);
}