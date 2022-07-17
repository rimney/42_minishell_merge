/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 00:21:04 by rimney            #+#    #+#             */
/*   Updated: 2022/07/17 16:12:06 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_find_next_flag(t_exec *exec, int *index, int *fd)
{
	*index += 2;
	if(exec->command[*index])
	{
		while(exec->command[*index + 2] || ft_is_another_flag(exec, *index) != PIPE)
		{
			if(ft_is_another_flag(exec, *index) == APPEND && exec->command[*index + 2])
			{
				*fd = open(exec->command[*index + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
				*index += 2;
			}
			if(ft_is_another_flag(exec, *index) == APPEND && !exec->command[*index + 2])
			{
				*fd = open(exec->command[*index + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == REDIROUT && exec->command[*index + 2])
			{
				*fd = open(exec->command[*index + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
				*index += 2;
			}
			if(ft_is_another_flag(exec, *index) == REDIROUT && !exec->command[*index + 2])
			{
				*fd = open(exec->command[*index + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == REDIRIN && exec->command[*index + 2])
				*index += 2;
			if(ft_is_another_flag(exec, *index) == REDIRIN && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) != PIPE))
			{
				*fd = open(exec->command[*index + 1], O_RDONLY);
				exec->input_flag = 1;
				*index += 2;
				return (1);
			}
		}
	}
		return (0);
}