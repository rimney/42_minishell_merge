/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_flag2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:30:48 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 01:32:11 by atarchou         ###   ########.fr       */
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
			flag = 0;
		}
		free(line);
	}
}

int	ft_is_a_mini_flag(t_exec *exec, int i)
{
	if((exec->command[i + 2] && (ft_is_another_flag(exec, i + 2) == PIPE
		|| ft_is_another_flag(exec, i + 2) == APPEND
		|| ft_is_another_flag(exec, i + 2) == REDIROUT || ft_is_another_flag(exec, i + 2) == REDIRIN
		|| ft_is_another_flag(exec, i + 2) == HEREDOC))
				|| exec->command[i + 2] == NULL)
		return (1);
	return (0);
}

int	ft_find_next_flag_append(t_exec *exec, int *index, int *fd)
{
	if(ft_is_another_flag(exec, *index) == APPEND && (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
	{
		*fd = ft_open(exec, APPEND, *index + 1);
		*index += 2;
		return (1);
	}
	return (0);
}

int	ft_find_next_flag_rediout(t_exec *exec, int *index, int *fd)
{
	if(ft_is_another_flag(exec, *index) == REDIROUT && !exec->command[*index + 2])
	{
		*fd = ft_open(exec, REDIROUT, *index + 1);
		*index += 2;
		return (1);
	}
	return (0);
}

int	ft_find_next_flag_input(t_exec *exec, int *index, int *in)
{
	if(ft_is_another_flag(exec, *index) == REDIRIN
		&& (!exec->command[*index + 2] || ft_is_another_flag(exec, *index + 2) == PIPE))
	{
		*in = open(exec->command[*index + 1], O_RDONLY);
		if(*in == -1)
		{
			exec->error_flag = 1;
			perror("minishell");
			return (1);
		}
		exec->input_flag = 1;
		*index += 2;
		return (1);
	}
	return (0);
}