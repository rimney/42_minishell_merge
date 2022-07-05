/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/05 00:54:50 by rimney           ###   ########.fr       */
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


void	ft_print_exec(t_exec *exec)
{
	int i;

	i = 0;
	while(exec->command[i])
	{
		printf("<< %s >> ", exec->command[i]);
		i++;
	}
	printf("\n");
}

void	ft_minishell(t_exec *exec, t_pipe *tpipe)
{
	int i;
	int command_location;

	i = 0;
	command_location = 0;
	exec->initial_flag = 0;

	ft_count_till_last_token(exec, tpipe);
	if(ft_execute_only_flag(exec, tpipe))
		 	return ;
	else
	{
		while(exec->command[i + 1] != NULL)
		{
			if(ft_strcmp(exec->command[i], ">") == 0 && exec->redirecion_flag == 0 && exec->initial_flag == 0)
			{
				exec->redirection_count = ft_count_till_other_token(exec, i, ">");
				exec->initial_flag = 1;
					ft_mini_redirect_output(exec, tpipe, i);
					i += exec->redirection_count;
			}
			if(ft_strcmp(exec->command[i], ">>") == 0 && exec->initial_flag == 0)
			{
				exec->initial_flag = 1;
				ft_mini_append(exec, tpipe, i);
			//	printf("here\n");
				i += exec->append_count;
			}
			if(ft_strcmp(exec->command[i], "<<") == 0 && exec->initial_flag == 0)
			{
				exec->initial_flag = 1;
				ft_mini_heredoc(exec, tpipe, i);
				i += exec->heredoc_count;
			}
			if(ft_strcmp(exec->command[i], "<") == 0 && exec->initial_flag == 0)
			{
				exec->initial_flag = 1;
				ft_mini_redirect_input(exec, tpipe, i);
				i += exec->input_count;
			}
	// 		if(ft_strcmp(exec->command[i], "|") == 0 && exec->initial_flag == 0)
	// 		{
	// 			printf("PASS\n");
	// 			exec->initial_flag = 1;
	// 			ft_mini_pipe_a(exec, tpipe, i);
	// 			i += exec->pipe_count;
			i++;
			}

		}
	wait(NULL);
}

void	ft_test(t_token *token, char **envp)
{
	char *temp;

	while(token)
	{
		if(token->value[0] == '$')
		{
			temp = token->value;
			token->value = ft_expand(token->value, envp);
			free(temp);
		}
		token = token->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*temp;
	t_tok_red	*cmd;
	t_exec		exec;
	t_pipe		pipes;

	(void)argv;
	(void)argc;
	line  = NULL;
	ft_get_env(&exec, envp);
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
		ft_test(cmd->lst_token, exec.envp);
		ft_fill_exec(&exec, cmd->lst_token);
		ft_initialize_exec(&exec, cmd->lst_token);
		//ft_print_exec(&exec);
		ft_minishell(&exec, &pipes);
		if (cmd)
		{
			// if (cmd->lst_token)
			// 	print_lst(cmd->lst_token);
			// if (check_if_redir_exist(line))
			// 	print_redir(cmd->lst_redir);
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
	//	ft_free(exec.command);
		g_flag = 0;
		free(line);
	}
	exit (0);
}
