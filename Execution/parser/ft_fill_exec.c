/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:18:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/01 00:17:17 by rimney           ###   ########.fr       */
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

void	ft_initialize_exec(t_exec *exec, t_token *token)
{
	exec->args = ft_count_tokens(token);
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
	exec->sev_flag = 0;
}


void	ft_fill_exec(t_exec *exec, t_token *token)
{
	int i = 0;
	int head_flag = 0;

	//ft_initialize_exec(exec, token, tpipe);
	exec->command = malloc(sizeof(char *) * ft_count_tokens(token) + 1);
	while(token)
	{
		if(token->type == WORD && head_flag == 0)
		{
			if(token->value[0] == '$' && ft_expand(token->value, exec->envp) != NULL)
				exec->command[i] = ft_expand(token->value, exec->envp);
			else
				exec->command[i] = strdup(token->value);
			head_flag = 1;
		}
		else if(token->type == WORD && head_flag == 1)
		{
			if(token->value[0] == '$' && ft_expand(token->value, exec->envp) != NULL)
				exec->command[i] = ft_expand(token->value, exec->envp);
			else
				exec->command[i] = ft_simple_strjoin(exec->command[i], token->value);
		}
		else if(token->type != WORD && head_flag)
		{
			i++;
			exec->command[i] = strdup(token->value);
			head_flag = 0;
			i++;		
		}
		token = token->next;
	}
	exec->command[i + 1] = 0;
}

// void	ft_check_expand(t_exec *exec)
// {
// 	int i;
// 	char *temp;

// 	i = 0;
// 	while(exec->command[i])
// 	{
// 		if(exec->command[i][0] == '$')
// 		{
// 			temp = exec->command[i];

// 		}
// 		i++;
// 	}
// }