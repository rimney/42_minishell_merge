/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 00:21:04 by rimney            #+#    #+#             */
/*   Updated: 2022/07/22 05:37:15 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_heredoc_middle(int *in, char *delimiter)
{
	int fd[2];
	int flag;
	char *line;

	flag = 1;
	pipe(fd);
	while(flag)
	{
		line = readline("heredoc middle > ");
		if(ft_strcmp(line, delimiter) != 0)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		else
		{
			close(fd[1]);
			*in = fd[0];
			//close(fd[0]);
			flag = 0;
		}
		free(line);
	}
}

int	ft_find_next_flag(t_exec *exec, int *index, int *fd, int *in)
{
	if(exec->command[*index + 2])
		*index += 2;
	if(exec->command[*index])
	{
		// if(ft_is_another_flag(exec, *index) == PIPE)
		// 	return (1);
		while(exec->command[*index + 2] || ft_is_another_flag(exec, *index) != PIPE)
		{
			if(ft_is_another_flag(exec, *index) == APPEND && exec->command[*index + 2] && ft_is_another_flag(exec, *index) != PIPE)
				*fd = ft_open(exec, APPEND, *index + 1);
			if(ft_is_another_flag(exec, *index) == APPEND && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
			{
				*fd = ft_open(exec, APPEND, *index + 1);
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == REDIRIN && exec->command[*index + 2])
			{
				*in = open(exec->command[*index + 1], O_RDONLY);
				if(*in == -1)
				{
					exec->error_flag = 1;
					perror("minishell");
					return (0);
				}
				exec->input_flag = 1;
			}
			if(ft_is_another_flag(exec, *index) == REDIRIN && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
			{
				*in = open(exec->command[*index + 1], O_RDONLY);
				if(*in == -1)
				{
					exec->error_flag = 1;
					perror("minishell");
					return (0);
				}
				exec->input_flag = 1;
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == HEREDOC && exec->command[*index + 2] && ft_is_another_flag(exec, *index + 2) == HEREDOC)
				ft_basic_heredoc(exec, *index); 
			if(ft_is_another_flag(exec, *index) == HEREDOC && exec->command[*index + 2] && ft_is_another_flag(exec, *index + 2) != HEREDOC)
			{
				ft_heredoc_middle(in, exec->command[*index + 1]);
				exec->heredoc_flag = 1;
			}

			if(ft_is_another_flag(exec, *index) == HEREDOC && !exec->command[*index + 2])
			{
				ft_heredoc_middle(in, exec->command[*index + 1]);
				exec->heredoc_flag = 1;
				*index += 2;
				return (1);
			}
			if(ft_is_another_flag(exec, *index) == REDIROUT && exec->command[*index + 2])
				*fd = ft_open(exec, REDIROUT, *index + 1);
			if(ft_is_another_flag(exec, *index) == REDIROUT && !exec->command[*index + 2])
			{
				*fd = ft_open(exec, REDIROUT, *index + 1);
				*index += 2;
				return (1);
			}
			*index += 2;
		}
	}
	return (1);
}