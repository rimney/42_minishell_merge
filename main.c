/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:59:48 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 12:00:52 by atarchou         ###   ########.fr       */
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
		{
			if (ft_check_leaks(cmd->lst_token))
				free(cmd->lst_redir);
			cmd->lst_redir = NULL;
		}
		else
			free_lst_redir(cmd->lst_redir);
	}
	free_lst_token(cmd->lst_token);
	free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_tok_red	*cmd;
	t_exec		exec;
	t_pipe		pipes;

	ft_kill_args(argc, argv);
	line = NULL;
	ft_get_env(&exec, envp);
	while (g_flag == 0)
	{
		ft_signals();
		line = handle_line_error();
		add_history(line);
		if (line[0] == 0 || ft_isspace(line[0]))
		{
			free(line);
			continue ;
		}
		ft_minishell_line(line, &exec.err_flag);
		if (g_flag == 0)
			handle_cmd_props(&line, &cmd);
		if (!exec.err_flag && !g_flag)
			ft_minishell_execution(&exec, &pipes, cmd);
		ft_reset_minishell(&exec, cmd, line, exec.err_flag);
	}
}
