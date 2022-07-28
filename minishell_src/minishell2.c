/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:46:18 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:20:29 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_minishell_executor2(t_exec *exec, t_pipe *tpipe, int i, int flag)
{
	if (flag == HEREDOC)
	{
		ft_mini_heredoc(exec, tpipe, i);
		return (i + exec->heredoc_count);
	}
	if (flag == PIPE)
	{
		ft_mini_pipe_a(exec, tpipe, i);
		return (i + exec->pipe_count);
	}
	return (0);
}

int	ft_minishell_executor(t_exec *exec, t_pipe *tpipe, int i, int flag)
{
	exec->initial_flag = 1;
	if (flag == REDIROUT)
	{
		ft_mini_redirect_output(exec, tpipe, i);
		return (i + exec->redirection_count);
	}
	if (flag == APPEND)
	{
		ft_mini_append(exec, tpipe, i);
		return (i + exec->append_count);
	}
	if (flag == REDIRIN)
	{
		ft_mini_redirect_input(exec, tpipe, i);
		return (i + exec->input_count);
	}
	else
		ft_minishell_executor2(exec, tpipe, i, flag);
	return (0);
}

void	ft_minishell_norm(t_exec *exec, t_pipe *tpipe, int *i)
{
	if (ft_strcmp(exec->command[*i], ">") == 0
		&& exec->initial_flag == 0)
		*i = ft_minishell_executor(exec, tpipe, *i, REDIROUT);
	if (ft_strcmp(exec->command[*i], ">>") == 0
		&& exec->initial_flag == 0)
		*i = ft_minishell_executor(exec, tpipe, *i, APPEND);
	if (ft_strcmp(exec->command[*i], "<<") == 0
		&& exec->initial_flag == 0)
		*i = ft_minishell_executor(exec, tpipe, *i, HEREDOC);
	if (ft_strcmp(exec->command[*i], "<") == 0
		&& exec->initial_flag == 0)
		*i = ft_minishell_executor(exec, tpipe, *i, REDIRIN);
	if (ft_strcmp(exec->command[*i], "|") == 0
		&& exec->initial_flag == 0)
		*i = ft_minishell_executor(exec, tpipe, *i, PIPE);
}

void	ft_minishell(t_exec *exec, t_pipe *tpipe, int index)
{
	int	i;

	i = index;
	exec->initial_flag = 0;
	ft_count_till_last_token(exec, tpipe);
	if (ft_execute_only_flag(exec, tpipe))
		return ;
	else
	{
		while (exec->command[i + 1] != NULL)
		{
			ft_minishell_norm(exec, tpipe, &i);
			i++;
		}
	}
	wait(NULL);
}

void	ft_launch_expand(t_token *token, char **envp, int exit_value)
{
	char	*temp;

	while (token)
	{
		if (ft_strcmp(token->value, "$?") == 0 && token->value)
		{
			temp = token->value;
			token->value = ft_itoa(exit_value % 255);
			free(temp);
		}
		if (token->value[0] == '$' && token->value[1] != '?' && token->value)
		{
			temp = token->value;
			token->value = ft_expand(token->value, envp);
			free(temp);
		}
		token = token->next;
	}
}
