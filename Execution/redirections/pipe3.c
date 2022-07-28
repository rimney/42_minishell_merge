/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:35:35 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:18:15 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pipe_condition(int index, t_exec *exec)
{
	if (exec->command[index + 1]
		&& (ft_strcmp(exec->command[index + 1], ">") == 0
			|| ft_strcmp(exec->command[index + 1], ">>") == 0
			|| ft_strcmp(exec->command[index + 1], "<") == 0
			|| ft_strcmp(exec->command[index + 1], "<<") == 0
			|| ft_strcmp(exec->command[index + 1], "<") == 0)
		&& exec->pipe_count > 2)
		return (1);
	return (0);
}

int	ft_flag_after_pipe(t_exec *exec)
{
	if (exec->redirecion_flag == 1
		|| exec->append_flag == 1
		|| exec->input_flag == 1)
		return (1);
	return (0);
}

void	ft_pipe_heredoc(t_exec *exec, int *fd, int index, int hfd[2])
{
	char	*line;
	char	**parser;
	char	*delimiter;
	int		flag;

	flag = 0;
	parser = ft_split_special(exec->command[index + 2], 1);
	delimiter = ft_mystrdup(parser[0], 0);
	pipe(hfd);
	while (flag == 0)
	{
		line = readline("heredoc pipe > ");
		if (ft_strcmp(line, delimiter) != 0)
			ft_heredoc_write(hfd, line);
		else
		{
			close(hfd[1]);
			*fd = hfd[0];
			flag = 1;
		}
		free(line);
	}
	ft_free(parser);
	free(delimiter);
}

void	ft_redirect_after_pipe_flag(t_exec *exec, t_pipe *tpipe,
	int index, int in_save)
{
	int	pid;
	int	fd;

	fd = -1;
	ft_get_next_redi(exec, &fd, index);
	if (exec->input_flag == 1)
	{
		ft_input_pipe_norm(fd, index, exec, tpipe);
		return ;
	}
	else if (exec->heredoc_flag == 1)
	{
		pid = fork();
		if (pid == 0)
			ft_apply_heredoc_redirection_after_pipe(fd, tpipe, exec, index + 2);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		exec->in = in_save;
		ft_apply_redirection_after_pipe(fd, tpipe, exec, index + 2);
	}
	waitpid(pid, &exec->env.exit_value, 0);
	WIFEXITED(exec->env.exit_value);
}

void	ft_get_next_redi(t_exec *exec, int *fd, int index)
{
	int	hfd[2];

	if (exec->pipe_flag == 1)
		*fd = open(exec->command[index + exec->redirection_count + 2],
				O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (exec->redirecion_flag == 1)
		*fd = open(exec->command[index + exec->redirection_count + 2],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (exec->append_flag == 1)
		*fd = open(exec->command[index + exec->append_count + 2],
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (exec->heredoc_flag == 1)
	{
		*fd = open(exec->command[index + exec->append_count + 2], O_RDONLY);
		ft_pipe_heredoc(exec, fd, index + 2, hfd);
	}
}
