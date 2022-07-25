/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 03:51:04 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo_single_quote(char *str)
{
	size_t	i;

	i = 1;
	while (i < ft_strlen(str) - 1)
		printf("%c", str[i++]);
}

void	ft_echo_double_quotes(char *str)
{
	char	*temp;

	temp = str;
	str = ft_filter_command_double_quotes(str);
	free(temp);
	printf("%s", str);
}

int	ft_find_expand(char **envp, char *arg)
{
	int		i;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(arg + 1, envp[i],
				ft_find_variable_index(envp[i], '=')) == 0)
		{
			temp = strdup(envp[i]);
			printf("%s", temp + ft_find_variable_index(envp[i], '=') + 1);
			free(temp);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_echo_norm(char **str, int i, t_exec *exec)
{
	while (str[i])
	{
		if (str[i][0] == '$')
		{
			ft_find_expand(exec->envp, str[i]);
			i++;
		}
		else if (str[i][0] == '\'')
		{
			ft_echo_single_quote(str[i]);
			i++;
		}
		else if (str[i][0] == '\"')
		{
			ft_echo_double_quotes(str[i]);
			i++;
		}
		if (!str[i])
			break ;
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
}

int	ft_echo(char **str, t_exec *exec)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_echo_edge_case(str[i]))
	{
		flag = 1;
		while (ft_echo_edge_case(str[i]))
			i++;
	}
	ft_echo_norm(str, i, exec);
	if (!flag)
		printf("\n");
	exec->env.exit_value = 0;
	return (1);
}
