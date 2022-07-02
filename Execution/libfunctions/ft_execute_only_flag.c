/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:26:02 by rimney            #+#    #+#             */
/*   Updated: 2022/07/02 01:29:31 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_execute_builtin(t_exec *exec, char **parser, int index)
{
	ft_export(exec, parser, 0);
}


int		is_a_builtin(t_exec *exec, int index)
{
	char **parser;

	parser = ft_split(exec->command[0], ' ');
	if(ft_strncmp(exec->command[0], "export", 6) == 0)
	{
		ft_execute_builtin(exec, parser, index);
		ft_free(parser);
		return (1);
	}
	if(ft_strncmp(exec->command[0], "env", 3) == 0)
	{
		ft_env(exec);
		return (1);
	}
	
	return (0);
}

int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe)
{
	int pid;

	if(only_command_flag(exec) && is_a_builtin(exec, 0))
	{
		return (1);
	}
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