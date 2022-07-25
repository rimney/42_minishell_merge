/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:18:36 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 04:28:56 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_heredoc_write(int fd[2], char *line)
{
	write(fd[1], line, strlen(line));
	write(fd[1], "\n", 1);
}

int	ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_loaction)
{
	char	*delimiter;
	char	*line;
	int		out;

	out = -1;
	delimiter = strdup(exec->command[index + 1]);
	ft_check_next_redi_heredoc_norm(exec, index, &out);
	while ((line = readline(">")))
	{
		if (ft_strcmp(line, delimiter) != 0)
			ft_heredoc_write(fd, line);
		if (ft_strcmp(line, delimiter) == 0)
		{
			if (out != -1)
			{
				dup2(out, 1);
				close(out);
			}
			ft_dup_and_close_norm(fd);
			ft_execute_command(exec, command_loaction);
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
	char	*line;
	char	*delimiter;

	delimiter = strdup(exec->command[index + 1]);
	while ((line = readline(">")))
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(delimiter);
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}
