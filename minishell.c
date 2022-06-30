/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 13:25:11 by rimney           ###   ########.fr       */
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

char	*ft_simple_strjoin(char *s1, char *s2)
{
	int i;
	char *str;
	int j;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	while(s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = ' ';
	j = 0;
	while(s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
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
			exec->command[i] = strdup(token->value);
			head_flag = 1;
		}
		else if(token->type == WORD && head_flag == 1)
			exec->command[i] = ft_simple_strjoin(exec->command[i], token->value);
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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*temp;
	t_tok_red	*cmd;
	t_exec		exec;
	t_pipe		pipes;

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
		ft_fill_exec(&exec, cmd->lst_token);
		ft_print_exec(&exec);
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