/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 08:45:40 by atarchou         ###   ########.fr       */
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

int	ft_count_elemets(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	ft_echo_norm(char **str, int i, t_exec *exec)
{
	while (str[i])
	{
		if (str[i][0] == '$' && !ft_contain(str[i], ' '))
		{
			ft_find_expand(exec->envp, str[i]);
			i++;
		}
		else if (str[i][0] == '\'')
		{
			ft_echo_single_quote(str[i]);
			i++;
		}
		else if (str[i][0] == '\"' || ft_contain(str[i], '$'))
		{
			ft_echo_double_quotes(str[i], exec);
			i++;
			continue ;
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
