/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_final_case.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:37:54 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:29:56 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_heredoc_final_case_child_1(t_exec *exec, int index, int fd[2], int out)
{
	char	*delimiter;
	char	**parser;
	int		in;

	parser = ft_split(exec->command[index + 1], ' ');
	delimiter = strdup(parser[0]);
	in = fd[0];
	if (exec->heredoc_count > 2)
		ft_find_next_flag(exec, &index, &out, &in);
	exec->in = in;
	close(fd[1]);
	if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
	dup2(in, 0);
	close(in);
	execve(ft_exec_command(exec->envp, parser[1]), parser + 1, exec->envp);
	return (1);
}

void	ft_dup_and_close_norm(int fd[2])
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

int	ft_heredoc_final_case_child_2(t_exec *exec, int index, int fd[2])
{
	char	*line;
	char	*delimiter;
	char	**parser;
	int		flag;

	parser = ft_split(exec->command[index + 1], ' ');
	delimiter = strdup(parser[0]);
	flag = 0;
	while (flag == 0)
	{
		line = readline("> ");
		ft_heredoc_write(fd, line);
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_dup_and_close_norm(fd);
			if (execve(ft_exec_command(exec->envp, parser[1]),
					parser + 1, exec->envp) == -1)
			{
				perror(exec->command[index]);
				ft_free(parser);
				exit(127);
			}
			flag = 1;
		}
		free(line);
	}
	return (1);
}

int	ft_heredoc_final_case_child(t_exec *exec, int index, int fd[2], int out)
{
	char	*delimiter;
	char	**parser;

	parser = ft_split(exec->command[index + 1], ' ');
	delimiter = strdup(parser[0]);
	if (ft_count_elements(parser) <= 2)
		ft_heredoc_final_case_child_2(exec, index, fd);
	else
		ft_heredoc_final_case_child_1(exec, index, fd, out);
	return (1);
}
