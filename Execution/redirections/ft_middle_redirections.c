/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:33:36 by rimney            #+#    #+#             */
/*   Updated: 2022/07/04 19:59:41 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_get_next_redirection(t_exec *exec, int index)
{
	if(ft_is_another_flag(exec, index) == REDIROUT)
	{
		exec->redirection_count = ft_count_till_other_token(exec, index, ">");
		return (exec->redirection_count);
	}
	if(ft_is_another_flag(exec, index) == APPEND)
	{
		exec->append_count = ft_count_till_other_token(exec, index, ">>");
		return (exec->append_count);
	}
	if(ft_is_another_flag(exec, index) == REDIRIN)
	{
		exec->input_count = ft_count_till_other_token(exec, index, "<");
		return (exec->input_count);
	}
	if(ft_is_another_flag(exec, index) == HEREDOC)
	{
		exec->heredoc_count = ft_count_till_other_token(exec, index, "<<");
		return (exec->heredoc_count);
	}
	return (0);
}

int ft_apply_pipe_middle(t_exec *exec, t_pipe *tpipe, int i, int fd)
{
	printf("EN\n");
	if((exec->command[i + 2] && ft_is_another_flag(exec, i + 2))
			|| exec->command[i + 2] == NULL)
	{
		if(exec->command[i + 2] && (ft_get_next_redirection(exec, i + 2)))
		{
			printf("HH\n");
			ft_dup_and_redirect(fd, exec, tpipe, i + 2);
			i += ft_get_next_redirection(exec, i + 2);
			return (i - 1);
		}
		else
		{
			ft_mini_pipe(exec, tpipe, fd, i - 1, i);
		i += exec->pipe_count;
		wait(NULL);
		}
	}
    return (i - 1);
}

int ft_apply_redin_middle(t_exec *exec, t_pipe *tpipe, int i)
{
	if(exec->command[i] && ft_is_another_flag(exec, i) == REDIRIN && exec->pipe_count == 2)
	{
		if(exec->command[i + 2] && exec->command[i + 4])
		{
			if(ft_strcmp(exec->command[i + 2], "|") && ft_strcmp(exec->command[i + 4], "<") == 0)
			{
				while(ft_strcmp(exec->command[i], "<") == 0)
					i += 4;
			}
		}
		if(exec->command[i + 2] == NULL)
		{
			exec->input_count = ft_count_till_other_token(exec, i, "<");
			ft_redirect_input(exec, tpipe, i, i - 1);
		
		}
		if(exec->command[i + 2])
			i += exec->input_count - 1;
		else	
			i += exec->input_count;
	}
	return i;	
}

// int	ft_middle_rediout(t_exec *exec, t_pipe *tpipe, int i)
// {
// 	int fd;

// 	if(exec->command[i] && ft_is_another_flag(exec, i) == REDIROUT && exec->pipe_count == 2)
// 	{
// 		tpipe->in = 0;
// 	//	printf("%s <<<<<<< herehre\n", exec->command[i - exec->pipe_count - 1]);
// 		fd = open(exec->command[i - exec->pipe_count - 1], O_RDWR);
// 		printf("%s << fd\n", exec->command[i - exec->pipe_count - 1]);
// 		ft_dup_and_redirect(fd, exec, i);
// 		if(exec->command[i + 2])
// 			i += exec->redirection_count - 1;
// 		else
// 		 i += exec->redirection_count - 1;
// 	}
// 	return (i);
// }