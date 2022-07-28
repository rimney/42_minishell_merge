/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_final_case.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:37:54 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 09:19:07 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_dup_and_close_child2_norm(t_exec *exec, int index, int fd[2])
{
	int	out;

	out = -1;
	close(fd[1]);
	ft_find_next_flag_heredoc(exec, &index, &out, &exec->in);
	if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
	dup2(exec->in, 0);
	close(exec->in);
}

int	ft_heredoc_final_case_child_1(t_exec *exec, int index,
		int fd[2], char **parser)
{
	char	*line;
	int		flag;

	flag = 0;
	while (flag == 0)
	{
		line = readline(">> ");
		if (ft_strcmp(line, parser[0]))
			ft_heredoc_write(fd, line);
		else
		{
			exec->in = fd[0];
			close(fd[1]);
			ft_dup_and_close_child2_norm(exec, index, fd);
			execve(ft_exec_command(exec->envp, parser[1]),
				parser + 1, exec->envp);
			flag = 1;
		}
		free(line);
	}
	return (1);
}

void	ft_dup_and_close_norm(int fd[2], int out)
{
	close(fd[1]);
	if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
	dup2(fd[0], 0);
	close(fd[0]);
}

int	ft_heredoc_final_case_child_2(t_exec *exec, int index, int fd[2], int flag)
{
	char	*line;
	char	*delimiter;
	char	**parser;

	parser = ft_split(exec->command[index + 1], 1);
	delimiter = ft_mystrdup(parser[0], 0);
	while (flag == 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter))
			ft_heredoc_write(fd, line);
		else
		{
			ft_dup_and_close_norm(fd, -1);
			execve(ft_exec_command(exec->envp, parser[1]),
				parser + 1, exec->envp);
		}
		free(line);
	}
	free(delimiter);
	ft_free(parser);
	return (1);
}

int	ft_heredoc_final_case_child(t_exec *exec, int index, int fd[2], int out)
{
	char	*delimiter;
	char	**parser;

	out--;
	parser = ft_split(exec->command[index + 1], 1);
	delimiter = ft_mystrdup(parser[0], 0);
	if (exec->args == 2)
		ft_heredoc_final_case_child_2(exec, index, fd, 0);
	else
		ft_heredoc_final_case_child_1(exec, index, fd, parser);
	return (1);
}
