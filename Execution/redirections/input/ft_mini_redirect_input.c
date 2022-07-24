/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_redirect_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:29:57 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 20:48:57 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"



int	ft_mini_redirect_input(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
	fd = -1;

	exec->initial_flag = 1;
	while(exec->command[i + 1] != NULL)
	{		
		if(ft_strcmp(exec->command[i], "<") == 0 && i <= 1)
		{
			exec->input_count = ft_count_till_other_token(exec, i, "<");
			ft_redirect_input(1, exec, 0);
			i += exec->input_count;
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");;
			if(ft_is_a_mini_flag(exec, i))
			{
				exec->pipe_count = ft_count_till_other_token(exec, i, "|");
				if(exec->in == -1)
					exec->in = open(".temp", O_CREAT | O_RDONLY | O_RDWR, 0644);
				i = ft_apply_pipe_middle(exec, tpipe, i, exec->in) - 1;
			}
		}
		i++;
	}
	wait(NULL);
	return(i);
}