/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:26:02 by rimney            #+#    #+#             */
/*   Updated: 2022/07/05 02:39:21 by rimney           ###   ########.fr       */
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
		ft_free(parser);
		return (1);
	}
	if(ft_strncmp(exec->command[0], "exit", 4) == 0)
	{
		ft_exit(exec, 0, parser);
		ft_free(parser);
		return (1);
	}
	if(ft_strncmp(exec->command[0], "unset", 5) == 0)
	{
		printf("FF\n");
		ft_unset(parser[1], exec);
		ft_free(parser);
		return (1);
	}
	if(ft_strncmp(exec->command[0], "pwd", 3) == 0)
	{
		printf("ppp\n");
		ft_pwd(exec->envp);
		 ft_free(parser);
		return (1);
	}
	if(ft_strncmp(exec->command[0], "cd", 2) == 0)
	{
		printf("cdcd\n");
		ft_cd(parser[1], exec);
		ft_free(parser);
		return (1);
	}
	if(ft_strncmp(exec->command[0], "echo", 4) == 0)
	{
		//parser = ft_split(exec->command[0], ' ');
		printf("echooo\n");
		ft_echo(parser, 0);
		ft_free(parser);
		return (1);
	}
	ft_free(parser);
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
		ft_execute_heredoc(exec, 1);
	else if(only_append_flag(exec) > 0)
	{
		//printf("DDD\n");
		ft_append(1, exec, 0); // segfault here !!!!!
	}
	else if(only_input_flag(exec) > 0)
		ft_redirect_input(exec, 0, 0);
	else
		return (0);

	return(1);
}