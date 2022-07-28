/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:18:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 09:01:41 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_assign_tpipe(t_pipe *pipe, int argc)
{
	pipe->fd[0] = -1;
	pipe->fd[1] = -1;
	pipe->in_save = -1;
	pipe->in = -1;
	pipe->max = argc;
}

void	ft_initialize_exec(t_exec *exec)
{
	exec->args = ft_count_elements(exec->command);
	exec->append_count = 0;
	exec->heredoc_count = 0;
	exec->input_count = 0;
	exec->redirection_count = 0;
	exec->append_flag = 0;
	exec->input_flag = 0;
	exec->heredoc_flag = 0;
	exec->redirecion_flag = 0;
	exec->pipe_count = 0;
	exec->pipe_flag = 0;
	exec->error_flag = 0;
}

void	ft_fill_exec_norm(t_exec *exec, t_token *token, int *head_flag, int *i)
{
	char	*temp;

	if (token->type != WORD && *head_flag == 0)
	{
		exec->command[*i] = ft_mystrdup(token->value, 0);
		*i += 1;
	}
	if (token->type == WORD && *head_flag == 0)
	{
		exec->command[*i] = ft_mystrdup(token->value, 0);
		*head_flag = 1;
	}
	else if (token->type == WORD && *head_flag == 1)
	{
		temp = exec->command[*i];
		exec->command[*i] = ft_simple_strjoin(exec->command[*i], token->value);
		free(temp);
	}
	else if (token->type != WORD && *head_flag)
	{
		*i += 1;
		exec->command[*i] = ft_mystrdup(token->value, 0);
		*head_flag = 0;
		*i += 1;
	}
}

void	ft_fill_exec(t_exec *exec, t_token *token)
{
	int	i;
	int	head_flag;

	i = 0;
	head_flag = 0;
	exec->command = malloc(sizeof(char *) * (ft_count_tokens(token) + 1));
	while (token)
	{
		ft_fill_exec_norm(exec, token, &head_flag, &i);
		token = token->next;
	}
	exec->command[i + 1] = 0;
}
