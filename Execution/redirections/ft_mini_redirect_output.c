/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_redirect_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:31:43 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 05:36:27 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mini_redirect_output(t_exec *exec, t_pipe *tpipe, int i)
{
	int	fd;

	fd = -1;
	while (exec->command[i + 1] != NULL)
	{
		if (ft_strcmp(exec->command[i], ">") == 0 && i == 1)
		{
			exec->redirection_count = ft_count_till_other_token(exec, i, ">");
			ft_redirect(i, exec, i - 1);
			i += exec->redirection_count;
		}
		if (exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			if (ft_is_a_mini_flag(exec, i))
			{
				exec->pipe_count = ft_count_till_other_token(exec, i, "|");
				fd = open(".temp", O_CREAT | O_RDONLY | O_TRUNC, 0644);
				i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
			}
		}
		i++;
	}
	wait(NULL);
	return (i);
}
