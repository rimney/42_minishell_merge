/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 04:59:48 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:22:03 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_line_error(void)
{
	char	*line;

	line = readline("BomusShell$> ");
	if (line == NULL)
		exit(0);
	return (line);
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
	while (1)
	{
		ft_norm(&line);
		if (!ft_check_line(line))
			continue ;
		ft_minishell_line(line, &exec.err_flag);
		if (g_flag == 0 && exec.err_flag == 0)
		{
			handle_cmd_props(&line, &cmd);
			ft_clean_lst_token(cmd->lst_token);
		}
		if (!exec.err_flag && !g_flag)
			ft_minishell_execution(&exec, &pipes, cmd);
		ft_reset_minishell(&exec, cmd, line, exec.err_flag);
	}
}
