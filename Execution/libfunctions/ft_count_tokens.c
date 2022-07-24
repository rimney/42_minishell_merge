/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:07:26 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 18:32:52 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_tokens(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void ft_count_till_last_token(t_exec *exec, t_pipe *pipes)
{
	int i;
	int count;

	i = 0;
	count = 0;
	exec->initial_flag = 0;
	while (exec->command[i])
	{
		if(ft_strcmp(exec->command[i], "|") == 0)
		{
			exec->pipe_count += 2;
			pipes->max = 0;
		}
		else if(ft_strcmp(exec->command[i], ">") == 0)
			exec->redirection_count += 2;
		else if(ft_strcmp(exec->command[i], ">>") == 0)
			exec->append_count += 2;
		else if(ft_strcmp(exec->command[i], "<") == 0)
			exec->input_count += 2;
		else if(ft_strcmp(exec->command[i], "<<") == 0)
			exec->heredoc_count += 2;
		i++;
	}
}

int	ft_count_till_other_token(t_exec *exec, int index, char *token)
{
	int i;
	int count;

	count = 0;
	i = index;
	while(exec->command[i])
	{
		if(ft_strcmp(exec->command[i], token) == 0)
			count += 2;
		else
			return count;
		i += 2;
	}
	return (count);
}
