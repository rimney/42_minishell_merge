/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:59:48 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 05:55:29 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_red	*init_cmd(char *line)
{
	t_tok_red	*cmd;

	cmd = (t_tok_red *)malloc(sizeof(t_tok_red));
	cmd->lst_token = (t_token *)malloc(sizeof(t_token));
	if (check_if_redir_exist(line))
		cmd->lst_redir = (t_redir *)malloc(sizeof(t_redir));
	return (cmd);
}

char	*handle_line_error(void)
{
	char	*line;

	line = readline("\e[0;32m BomusShell$>\033[0;37m");
	if (line == NULL)
		exit(0);
	return (line);
}

void	handle_cmd_props(char **line, t_tok_red **cmd)
{
	char	*temp;

	temp = *line;
	*line = fix_line(*line);
	free(temp);
	*cmd = init_cmd(*line);
	*cmd = parser(*cmd, *line);
	if (!(*cmd))
		g_flag = 1;
}

void	free_and_free(t_tok_red *cmd)
{
	if (cmd->lst_redir)
	{
		if (count_redir(cmd->lst_token) == 0)
			cmd->lst_redir = NULL;
		else
			free_lst_redir(cmd->lst_redir);
	}
	free_lst_token(cmd->lst_token);
	free(cmd);
}

int	ft_mini_pipe_a(t_exec *exec, t_pipe *tpipe, int i)
{
	int	fd;

	fd = -1;
	exec->initial_flag = 1;
	while (exec->command[i + 1] != NULL)
	{
		if (ft_strcmp(exec->command[i], "|") == 0 && i == 1)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			ft_mini_pipe(exec, tpipe, -1, i);
			i += exec->pipe_count;
		}
		if (exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			fd = open(exec->command[i + 1], O_RDWR);
			i = ft_apply_pipe_middle(exec, tpipe, i, fd) - 1;
		}
		i++;
	}
	wait(NULL);
	return (i);
}
