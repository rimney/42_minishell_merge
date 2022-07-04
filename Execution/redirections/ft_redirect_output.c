/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:57:27 by rimney            #+#    #+#             */
/*   Updated: 2022/07/04 21:14:31 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_single_redirect(char *argv)
{
	// int fd;

	// fd = open(argv, O_RDWR , 0644);
	printf("%s\n", argv);
}

void	ft_advanced_redirect(int index, t_exec *exec, int fd_out, int fd_in, int location)
{
	int pid;
	int location_save;

	fd_in = open(exec->command[index - 3], O_RDONLY);
	pid = fork();
	if(pid == 0)
	{
		while(index < exec->redirection_count)
		{
			fd_out = open(exec->command[index + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
			if(index + 1 == exec->redirection_count)
			{
				dup2(fd_in, 0);
				close(fd_in);
				dup2(fd_out, 1);
				close(fd_out);
				ft_execute_command(exec, location);
			}
			index += 2;
		}
	}
	wait(NULL);
}

int	ft_redirect(int index, t_exec *exec, int command_location)
{
	int fd;
	int pid;

	while(index < exec->redirection_count)
	{
		fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if(index + 1 == exec->redirection_count)
		{	
			pid = fork();
			if(pid == 0)
			{
				fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
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