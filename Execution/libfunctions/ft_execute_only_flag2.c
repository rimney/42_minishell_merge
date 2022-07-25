/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_only_flag2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:43:44 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 01:44:16 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_a_builtin(char *command)
{
	if(ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "PWD") == 0)
		return (1);
	if(ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "ECHO") == 0)
		return (1);
	if(ft_strcmp(command, "export") == 0 || ft_strcmp(command, "EXPORT") == 0)
		return (1);
	if(ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "CD") == 0)
		return (1);
	if(ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "UNSET") == 0)
		return (1);
	if(ft_strcmp(command, "env") == 0 || ft_strcmp(command, "ENV") == 0)
		return (1);
	if(ft_strcmp(command, "exit") == 0 || ft_strcmp(command, "EXIT") == 0)
		return (1);
	return (0);
}

int		ft_execute_builtin(char **parser, t_exec *exec, int index)
{
	char	**parser2;

	parser2 = ft_split(exec->command[index], ' ');
	if(ft_strcmp(parser2[0], "export") == 0)
		ft_export(exec, parser);
	if(ft_strcmp(parser2[0], "env") == 0)
		ft_env(exec);
	if(ft_strcmp(parser2[0], "exit") == 0)
		ft_exit(exec, index, parser2);
	if(ft_strcmp(parser2[0], "unset") == 0)
		ft_unset(parser, exec);
	if(ft_strcmp(parser2[0], "pwd") == 0)
		ft_pwd();
	if(ft_strcmp(parser2[0], "cd") == 0)
		ft_cd(parser[1], exec);
	if(ft_strcmp(parser2[0], "echo") == 0)
		ft_echo(parser, exec);
	else
		return (0);
	return (1);
}


int		ft_execute_builtin_parent(t_exec *exec, int index)
{
	char **parser;

	parser = ft_split_special(exec->command[0], ' ');
	ft_filter_command_double_quotes_2d_array(parser);
	if(ft_strcmp(parser[0], "export") == 0)
		ft_export(exec, parser);
	else if(ft_strcmp(parser[0], "env") == 0)
		ft_env(exec);
	else if(ft_strcmp(parser[0], "exit") == 0)
		ft_exit(exec, index, parser);
	else if(ft_strcmp(parser[0], "unset") == 0)
		ft_unset(parser, exec);
	else if(ft_strcmp(parser[0], "pwd") == 0)
		ft_pwd();
	else if(ft_strcmp(parser[0], "cd") == 0)
		ft_cd(parser[1], exec);
	else if(ft_strcmp(parser[0], "echo") == 0)
		ft_echo(parser, exec);
	else
	{
		ft_free(parser);
		return (0);
	}
	ft_free(parser);
	return (1);
}