/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:21 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 01:14:00 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_advanced_heredoc(t_exec *exec, int index, int command_location)
{
	int	i;

	i = index;
	while (i < ft_get_last_delimiter(exec, index) && exec->heredoc_count > 2)
	{
		if (ft_strcmp(exec->command[i], "<<") == 0)
			ft_basic_heredoc(exec, i);
		i += 2;
		index += 2;
	}
	ft_heredoc(exec, command_location, index);
}

void	ft_heredoc_final_case(t_exec *exec, int index)
{
	int	pid;
	int	fd[2];
	int	out;
	int	info;

	out = -1;
	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_heredoc_final_case_child(exec, index, fd, out);
	else
	{
		close(fd[0]);
		close(fd[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &info, 0);
		if (WIFEXITED(info))
			exec->env.exit_value = WEXITSTATUS(info);
		else if (WIFSIGNALED(info))
		{
			if (WTERMSIG(info) == 2)
			exec->env.exit_value = 2;
		}
		signal(SIGINT, SIG_DFL);
	}
}

int	ft_basic_heredoc_final_case(t_exec *exec, int index)
{
	char	*line;
	char	**parser;
	int		flag;

	flag = 0;
	parser = ft_split(exec->command[index + 1], 1);
	while (flag == 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, parser[0]) == 0)
		{
			ft_free(parser);
			free(line);
			flag = 1;
			return (1);
		}
		free(line);
	}
	return (0);
}

void	ft_advanced_heredoc_final_case(t_exec *exec, int index)
{
	int	i;

	i = index;
	while (i < ft_get_last_delimiter(exec, index) && exec->heredoc_count > 2)
	{
		if (ft_strcmp(exec->command[i], "<<") == 0)
			ft_basic_heredoc_final_case(exec, i);
		i += 2;
		index += 2;
	}
	ft_heredoc_final_case(exec, index);
}
