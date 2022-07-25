/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:27:40 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 04:28:29 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_get_last_delimiter(t_exec *exec, int index)
{
	int	i;
	int	delimiter;

	i = index;
	delimiter = 0;
	while (i < exec->args)
	{
		if (ft_strcmp(exec->command[i], "<<") == 0)
			delimiter = i;
		i++;
	}
	return (delimiter);
}

int	ft_check_next_redi_heredoc_norm(t_exec *exec, int index, int *out)
{
	if (exec->command[index + 2]
		&& ft_is_another_flag(exec, index + 2) == REDIROUT)
	{
		exec->redirection_count
			= ft_count_till_other_token(exec, index + 2, ">");
		*out = open(exec->command[index + exec->redirection_count + 1],
				O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	else if (exec->command[index + 2]
		&& ft_is_another_flag(exec, index + 2) == APPEND)
	{
		exec->append_count = ft_count_till_other_token(exec, index + 2, ">>");
		*out = open(exec->command[index + exec->append_count + 1],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	return (1);
}
