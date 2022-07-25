/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 11:58:03 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell_execution(t_exec *exec, t_pipe *pipes, t_tok_red *cmd)
{
	ft_launch_expand(cmd->lst_token, exec->envp, exec->env.exit_value);
	ft_fill_exec(exec, cmd->lst_token);
	ft_initialize_exec(exec);
	ft_minishell(exec, pipes, 0);
}

void	ft_minishell_line(char *line, int *err_flag)
{
	if (!check_redir_correctness(line))
	{
		*err_flag = 1;
		handle_error("error in input\n");
	}
}

void	ft_reset_minishell(t_exec *exec,
	t_tok_red *cmd, char *line, int err_flag)
{
	if (cmd)
		free_and_free(cmd);
	if (!err_flag && !g_flag)
		ft_free(exec->command);
	g_flag = 0;
	free(line);
	err_flag = 0;
}

void	ft_kill_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	ft_mini_pipe_a(t_exec *exec, t_pipe *tpipe, int i)
{
	int	fd;

	fd = -1;
	exec->initial_flag = 1;
	while (exec->command[i + 1] != NULL)
	{
		if (ft_strcmp(exec->command[i], "|") == 0 && i == 1)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			ft_mini_pipe(exec, tpipe, -1, i);
			i += exec->pipe_count;
		}
		if (exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			fd = open(exec->command[i + 1], O_RDWR);
			i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
		}
		i++;
	}
	wait(NULL);
	return (i);
}
