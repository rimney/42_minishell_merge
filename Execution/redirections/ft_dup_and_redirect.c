/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_and_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:35:29 by rimney            #+#    #+#             */
/*   Updated: 2022/07/05 00:57:13 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"




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

int	ft_dup_and_redirect(int fd_in, t_exec *exec, t_pipe *tpipe, int index)
{
	int fd_out;
	int pid;

	// pid = fork();
	// if(pid == 0)
	// {
		if(ft_strcmp(exec->command[index], ">>") == 0)
		{
			exec->append_count += index - 1;
			ft_advanced_append(index, exec, fd_in, fd_out, index - 1);
			return (1);
		}
		if(ft_is_another_flag(exec, index) == REDIROUT)
		{
			exec->redirection_count += index - 1;
			ft_advanced_redirect(index, exec, fd_in, fd_out, index - 1);
			return (1);
		}
		if(ft_is_another_flag(exec, index) == REDIRIN)
		{
			exec->input_count += index - 1;
			ft_advanced_redirect_input(exec, fd_in, index);
			return (1);
		}
		if(ft_strcmp(exec->command[index], "<<") == 0)
		{
			exec->heredoc_count += index - 1;
			ft_execute_heredoc(exec, index);
			return 1;
		}
	// }
	return (exec->redirection_count);
}