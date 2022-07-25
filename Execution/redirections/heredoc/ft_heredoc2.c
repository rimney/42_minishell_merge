/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:18:36 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 09:01:53 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_heredoc_write(int fd[2], char *line)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
}

int	ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_loaction)
{
	char	*delimiter;
	char	*line;
	int		out;
	int		flag;

	flag = 0;
	out = -1;
	delimiter = ft_mystrdup(exec->command[index + 1], 0);
	ft_check_next_redi_heredoc_norm(exec, index, &out);
	while (flag == 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) != 0)
			ft_heredoc_write(fd, line);
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_dup_and_close_norm(fd, out);
			ft_execute_command(exec, command_loaction);
			flag = 1;
		}
		free(line);
	}
	free(delimiter);
	return (0);
}

void	ft_heredoc(t_exec *exec, int command_location, int index)
{
	int	fd[2];

	pipe(fd);
	ft_exec_heredoc(exec, index, fd, command_location);
	close(fd[0]);
	close(fd[1]);
}

int	ft_basic_heredoc(t_exec *exec, int index)
{
	int		flag;
	char	*line;
	char	*delimiter;

	delimiter = ft_mystrdup(exec->command[index + 1], 0);
	flag = 0;
	while (flag == 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(delimiter);
			free(line);
			flag = 1;
			return (1);
		}
		free(line);
	}
	return (0);
}
