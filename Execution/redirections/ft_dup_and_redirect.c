/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:35:29 by rimney            #+#    #+#             */
/*   Updated: 2022/07/01 00:35:54 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_dup_and_redirect(int fd_in, t_exec *exec, int index)
{
	int fd_out;
	int pid;

	pid = fork();
	if(pid == 0)
	{
		if(ft_strcmp(exec->command[index], ">>") == 0)
		{
			printf("passed rediappend\n");
			fd_out = open(exec->command[index + 1], O_CREAT | O_APPEND | O_RDWR, 0644);
			dup2(fd_in, 0);
			close(fd_in);
			dup2(fd_out, 1);
			close(fd_out);
		}
		if(ft_is_another_flag(exec, index) == REDIROUT)
		{
			printf("rediiiin\n");
			fd_out = open(exec->command[index + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
			dup2(fd_in, 0);
			close(fd_in);
			dup2(fd_out, 1);
			close(fd_out);
		}
		ft_execute_command(exec, index - 1);
	}
	return (1);
}
