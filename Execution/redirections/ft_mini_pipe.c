/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:50:18 by rimney            #+#    #+#             */
/*   Updated: 2022/07/23 05:30:34 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mini_pipe(t_exec *exec, t_pipe *pipes, int in, int count, int index)
{

	int i;

	i = index;
	count = -1;
		// if(ft_strcmp(exec->command[i + exec->pipe_count], ">") == 0)
		// {
		// 	printf("FOUNDED");
		// 	exec->redirection_count = ft_count_till_other_token(exec, i + exec->pipe_count, ">");
		// 	printf("%d << red\n", exec->redirection_count);
		// }
	if(exec->pipe_count == 2 && exec->command[index + 2])
	{
		// printf("%d << count\n", exec->pipe_count);
		if(ft_strcmp(exec->command[index + 2], ">") == 0)
		{
			exec->pipe_flag = 1;
			exec->redirection_count = ft_count_till_other_token(exec, i + 2, ">");
			// printf("%d << here\n", exec->pipe_flag);
		}
	}
	if(exec->command[i + exec->pipe_count] && ft_strcmp(exec->command[i + exec->pipe_count], ">") == 0 && exec->pipe_count > 2)
	{
		// printf("REDIFFF\n");
		printf("sss\n");
		exec->redirecion_flag = 1;
		exec->redirection_count = ft_count_till_other_token(exec, i + exec->pipe_count, ">");
		// printf("%d << \n", exec->redirection_count);
	}
	if(exec->command[i + exec->pipe_count] && ft_strcmp(exec->command[i + exec->pipe_count], ">>") == 0 && exec->pipe_count > 2)
	{
		// printf("aPPeIFFF\n");
		exec->append_flag = 1;
		exec->append_count = ft_count_till_other_token(exec, i + exec->pipe_count, ">>");
		// printf("%d << \n", exec->append_count);
	}
	if(exec->command[i + exec->pipe_count] && ft_strcmp(exec->command[i + exec->pipe_count], "<") == 0 && exec->pipe_count > 2)
	{
		// printf("REDDDIIIIN\n");
		exec->input_flag = 1;
		exec->input_count = ft_count_till_other_token(exec, i + exec->pipe_count, "<");
		// printf("%d << \n", exec->input_count);
	}
	ft_assign_tpipe(pipes, index + exec->pipe_count - 1);
	printf("%d <<<<\n", exec->pipe_flag);
	 if(exec->pipe_flag)
	 {
		execute_pipe(exec, i - 1, in, pipes); ////////// SHOULD START FROM HERE !!!
		exec->pipe_flag = 0;
		//exec->redirecion_flag = 0;
		i++;
		return (i + exec->pipe_count);
	 }
	 if(i == 1)
	 		execute_pipe(exec, 0, in, pipes);
	else
		execute_pipe(exec, i + 1, in, pipes);
	exec->pipe_flag = 0;
	exec->input_count = 0;

	return (i + exec->pipe_count);
}
