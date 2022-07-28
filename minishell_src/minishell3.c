/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:16:07 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:20:35 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_kill_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
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

int	ft_check_operation(char *str)
{
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|'
		|| str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
	{
		printf("syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	ft_check_operation2(char *str)
{
	char	**parser;
	int		flag;

	flag = 0;
	parser = ft_split(str, ' ');
	if (ft_strncmp(parser[ft_count_elements(parser) - 1], ">", 1) == 0
		|| ft_strncmp(parser[ft_count_elements(parser) - 1], "|", 1) == 0
		|| (ft_strncmp(parser[ft_count_elements(parser) - 1], "<", 1) == 0))
	{
		ft_free(parser);
		printf("syntax error near unexpected token\n");
		return (0);
	}
	ft_free(parser);
	return (1);
}

int	ft_check_errors(char *str)
{
	if (ft_check_operation(str))
		return (1);
	return (0);
}
