/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:20 by rimney            #+#    #+#             */
/*   Updated: 2022/06/30 22:05:44 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_single_append(int argc, char **argv)
{
	int fd;
	char *line;
	if(argc == 3 && ft_strcmp(argv[1], ">>") == 0)
	{
		fd = open(argv[2], O_CREAT | O_RDWR, 0644);
		while(1)
		{
			fd = open(argv[2], O_RDWR | O_APPEND, 0644);
			line = readline("");
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

int	ft_append(int index, t_exec *exec, t_pipe *tpipe, int command_location)
{
	int pid;
	int fd;

	tpipe->fd[0] = 0;
	while(index < exec->append_count)
	{
		fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if(index + 1 == exec->append_count)
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(fd, 1);
				close(fd);
				ft_execute_command(exec, command_location);
			}
		}
		index += 2;
	}
	wait(NULL);
	return (index);
}