/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:21:22 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:24:25 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok_red	*init_cmd(char *line)
{
	t_tok_red	*cmd;

	cmd = (t_tok_red *)malloc(sizeof(t_tok_red));
	cmd->lst_token = (t_token *)malloc(sizeof(t_token));
	if (check_if_redir_exist(line))
		cmd->lst_redir = (t_redir *)malloc(sizeof(t_redir));
	return (cmd);
}

int	ft_check_tokens(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->command[i + 1])
	{
		if (ft_is_another_flag(exec, i) == ft_is_another_flag(exec, i + 1))
		{
			printf("syntax error near unexpected token\n");
			return (0);
		}
		i++;
	}
	return (1);
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

void	ft_norm(char **line)
{
	ft_signals();
	*line = handle_line_error();
	add_history(*line);
}

int	ft_check_line(char *line)
{
	if (line[0] == 0 || ft_isspace(line[0]) || !ft_check_operation2(line))
	{
		free(line);
		return (0);
	}
	return (1);
}
