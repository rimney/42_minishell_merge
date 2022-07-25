/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:26:02 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:22:34 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_only_flag_norm(t_exec *exec, t_pipe *tpipe)
{
	if (only_output_redirection_flag(exec) > 0)
		ft_redirect(0, exec, 0);
	else if (only_heredoc_flag(exec) > 0)
		ft_execute_heredoc(exec, 0);
	else if (only_append_flag(exec) > 0)
		ft_append(0, exec, 0);
	else if (only_input_flag(exec) > 0)
		ft_redirect_input(1, exec, 0);
	else if (only_pipe_flag(exec) > 0 && exec->args > 2)
	{
		ft_assign_tpipe(tpipe, exec->pipe_count);
		execute_pipe(exec, 0, -1, tpipe);
		wait(NULL);
	}
	else
		return (0);
	return (1);
}

int	ft_check_quotes_final_case(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '\"' && str[ft_strlen(str) - 1] != '\"')
		|| (str[0] != '\"' && str[ft_strlen(str) - 1] == '\"'))
	{
		printf("missing quotes\n");
		return (0);
	}
	return (1);
}

int	quote_loop(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			return (1);
		i++;
	}
	printf("minishell : command not found\n");
	return (0);
}

int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe)
{
	int	pid;

	if (exec->command[0][0] == '\"'
		&& (!ft_check_quotes_final_case(exec->command[0])
		|| !quote_loop(exec->command[0])))
		return (0);
	if (exec->args <= 2 && ft_execute_builtin_parent(exec, 0))
		return (1);
	if (only_command_flag(exec) > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			ft_execute_command(exec, 0);
		}
		waitpid(pid, &exec->env.exit_value, 0);
		WIFEXITED(exec->env.exit_value);
	}
	else if (!ft_execute_only_flag_norm(exec, tpipe))
		return (0);
	return (1);
}
