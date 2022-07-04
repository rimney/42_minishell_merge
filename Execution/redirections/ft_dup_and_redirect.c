/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:35:29 by rimney            #+#    #+#             */
/*   Updated: 2022/07/04 16:46:37 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_do_append(t_exec *exec, int fd_in, int fd_out, int index)
{
	printf("passed rediappend\n");
	if(ft_is_another_flag(exec, index + 2) == REDIROUT)
		printf("FFF\n");
	fd_out = open(exec->command[index + 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(fd_out, 1);
	close(fd_out);
	ft_execute_command(exec, index - 1);
}

void	ft_do_rediout(t_exec *exec, int fd_in, int fd_out, int index)
{
	printf("rediiiin\n");

	fd_out = open(exec->command[index + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(fd_out, 1);
	close(fd_out);
	ft_execute_command(exec, index - 1);
}

void	ft_do_input(t_exec *exec, int fd_in, int index)
{
	if(exec->command[index + 2])
		return ;
	fd_in = open(exec->command[index + 1], O_RDONLY);
	if(fd_in == -1)
	{
		perror("minishell : ");
		return ;
	}
	dup2(fd_in, 0);
	close(fd_in);
	ft_execute_command(exec, index - 1);
	
}

int	ft_dup_and_redirect(int fd_in, t_exec *exec, int index)
{
	int fd_out;
	int pid;

	pid = fork();
	if(pid == 0)
	{
		if(ft_strcmp(exec->command[index], ">>") == 0)
		{
			ft_do_append(exec, fd_in, fd_out, index);
			return (1);
		}
		if(ft_is_another_flag(exec, index) == REDIROUT)
		{
			fd_in = open(exec->command[index - 1], O_RDONLY);
			exec->redirection_count += index - 1;
			ft_advanced_redirect(index, exec, fd_in, fd_out, index - 1);
			return (1);
		}
		if(ft_is_another_flag(exec, index) == REDIRIN)
		{
			ft_do_input(exec, fd_in, index);
			return (1);
		}
	}
	return (1);
}
