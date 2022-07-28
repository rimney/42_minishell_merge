/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:23 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 07:09:22 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pipe(int in, t_pipe *tpipe, t_exec *exec, int index)
{
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	if (tpipe->fd[1] != -1)
	{
		dup2(tpipe->fd[1], 1);
		close(tpipe->fd[1]);
	}
	close(tpipe->fd[0]);
	ft_execute_command(exec, index);
}

void	ft_apply_redirection_after_pipe(int out, t_pipe *tpipe,
	t_exec *exec, int index)
{
	if (exec->in != -1)
	{
		dup2(exec->in, 0);
		close(exec->in);
	}
	if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
	close(tpipe->fd[0]);
	ft_execute_command(exec, index);
	tpipe->in = 0;
}

void	ft_apply_input_redirection_after_pipe(int in, t_pipe *tpipe,
	t_exec *exec, int index)
{
	if (exec->command[index + exec->input_count + 1] != NULL)
		exit(0);
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	tpipe->fd[1] = 0;
	ft_execute_command(exec, index);
}

void	ft_apply_heredoc_redirection_after_pipe(int in, t_pipe *tpipe,
	t_exec *exec, int index)
{
	if (exec->command[index + exec->heredoc_count + 1] != NULL)
		exit(0);
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	tpipe->fd[1] = 0;
	ft_execute_command(exec, index);
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
	parser  = ft_split_special(exec->command[index + 2], 1);
	delimiter = ft_mystrdup(parser[0], 0);
	pipe(hfd);
	while(flag == 0)
	{
		line = readline("heredoc pipe > ");
		if(ft_strcmp(line, delimiter) != 0)
		{
			write(hfd[1], line, ft_strlen(line));
			write(hfd[1], "\n", 1);
		}
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
	printf("%s <<\n", exec->command[index]);
}

void	ft_get_next_redi(t_exec *exec, int *fd, int index)
{
	int hfd[2];

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
