/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 01:24:40 by rimney           ###   ########.fr       */
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


int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*temp;
	t_tok_red	*cmd;

	(void)argv;
	(void)argc;
	line = NULL;
	while (g_flag == 0)
	{
		// signal(SIGINT, handle_signals);
		// signal(SIGQUIT, SIG_IGN);
		line = readline("\e[0;32m BomusShell$>\033[0;37m");
		if (line == NULL)
			exit(0);
		if (line[0] == 0 || ft_isspace(line[0]))
		{
			free(line);
			continue ;
		}
		if (!check_redir_correctness(line))
			handle_error("error in input\n");
		add_history(line);
		cmd = 0;
		if (g_flag == 0)
		{
			temp = line;
			line = fix_line(line);
			free(temp);
			cmd = init_cmd(line);
			cmd = parser(cmd, line);
			if (!cmd)
				g_flag = 1;
		}
		
		if (cmd)
		{
			print_lst(cmd->lst_token);
			if (check_if_redir_exist(line))
				print_redir(cmd->lst_redir);
			if (cmd->lst_redir)
			{
				if (count_redir(cmd->lst_token) == 0)
					cmd->lst_redir = NULL;
				else
					free_lst_redir(cmd->lst_redir);
			}
			if (cmd->lst_token)
				free_lst_token(cmd->lst_token);
			free(cmd);
		}
		g_flag = 0;
		free(line);
	}
	exit (0);
}